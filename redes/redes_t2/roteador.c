#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <semaphore.h>
#include <sys/socket.h>
#include "structs_e_defines.h"
#include "ler_e_imprimir_estruturas.h"
#include "interface.h"

pthread_mutex_t mutex_fila_pacotes = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_fila_tratamento = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_sequencia_interna_final = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_att_tabela = PTHREAD_MUTEX_INITIALIZER;

int id_proprio;
Roteador roteadores[MAX_ROTEADORES];
TabelaVetores tab_vetores;
int tab_roteamento[MAX_ROTEADORES], tab_custos[MAX_ROTEADORES];
int porcentagem_perda = 0;

int sequencia_interna_inicio[MAX_ROTEADORES], sequencia_interna_final[MAX_ROTEADORES];
sem_t semaforos[MAX_ROTEADORES];
int sequencia[MAX_ROTEADORES], sequencia_ACK[MAX_ROTEADORES];
int conta_roteadores[MAX_ROTEADORES];

typedef struct Nodo_Fila_Pacote {
	char conteudo[TAMANHO_PACOTE];
	int sequencia_interna, confiavel;
	struct Nodo_Fila_Pacote *proximo;
} NodoFilaPacote;

typedef struct Fila_Pacotes {
	struct Nodo_Fila_Pacote *inicio, *final;
} FilaPacotes;

FilaPacotes fila_pacotes;

void montar_pacote_dados(char *pacote, int id_destino, char *mensagem){
	memset(pacote, '\0', TAMANHO_PACOTE);
	sprintf(pacote, "%d %d %d %d %s", id_proprio, id_destino, sequencia[id_destino], ID_PACOTE_DADOS, mensagem);
}

void montar_pacote_controle(char *pacote, int id_destino, int sequencia, char *mensagem){
	memset(pacote, '\0', TAMANHO_PACOTE);
	sprintf(pacote, "%d %d %d %d %s", id_proprio, id_destino, sequencia, ID_PACOTE_CONTROLE, mensagem);
}

void enfileirar_pacote(int confiavel, char *pacote, int sequencia_interna){
	NodoFilaPacote *nodo_pacote = malloc(sizeof(NodoFilaPacote));
	int id_destino;
	strcpy(nodo_pacote->conteudo, pacote);

	sscanf(pacote, "%*d %d", &id_destino);
	pthread_mutex_lock(&mutex_sequencia_interna_final);
	nodo_pacote->sequencia_interna = sequencia_interna;

	if(sequencia_interna == GERAR_SEQUENCIA_INTERNA){
		nodo_pacote->sequencia_interna = sequencia_interna_final[id_destino];
		sequencia_interna_final[id_destino] += 1;
	}

	pthread_mutex_unlock(&mutex_sequencia_interna_final);

	nodo_pacote->confiavel = confiavel;
	nodo_pacote->proximo = NULL;

	pthread_mutex_lock(&mutex_fila_pacotes);
	if(fila_pacotes.inicio == NULL){
		fila_pacotes.inicio = nodo_pacote;
	} else {
		fila_pacotes.final->proximo = nodo_pacote;
	}
	fila_pacotes.final = nodo_pacote;
	pthread_mutex_unlock(&mutex_fila_pacotes);
}

typedef struct Nodo_Fila_Tratamento {
	int roteador;
	int vetores[MAX_ROTEADORES];
	struct Nodo_Fila_Tratamento *proximo;
} NodoFilaTratamento;

typedef struct Fila_Tratamento {
	struct Nodo_Fila_Tratamento *inicio, *final;
} FilaTratamento;

FilaTratamento fila_tratamento;

void enfileirar_tratamento(NodoFilaTratamento nodo_tratamento_estatico){
	NodoFilaTratamento *nodo_tratamento = malloc(sizeof(NodoFilaTratamento));

	nodo_tratamento->roteador = nodo_tratamento_estatico.roteador;
	memcpy(nodo_tratamento->vetores, nodo_tratamento_estatico.vetores, MAX_ROTEADORES * sizeof(int));
	nodo_tratamento->proximo = NULL;

	pthread_mutex_lock(&mutex_fila_tratamento);
	if(fila_tratamento.inicio == NULL){
		fila_tratamento.inicio = nodo_tratamento;
	} else {
		fila_tratamento.final->proximo = nodo_tratamento;
	}
	fila_tratamento.final = nodo_tratamento;
	pthread_mutex_unlock(&mutex_fila_tratamento);
}

void *thread_recebimento(){
	struct sockaddr_in si_me, si_other;
	int s, slen = sizeof(si_other), recv_len;
	int id_origem, id_destino, tipo_pacote, sequencia, janela[MAX_ROTEADORES];
	char pacote[TAMANHO_PACOTE], mensagem[100];

	memset(janela, 0, sizeof(janela));

	// Cria socket UDP
	if((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){
		die("socket");
	}

	memset((char *) &si_me, 0, sizeof(si_me));

	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(roteadores[id_proprio].porta);
	si_me.sin_addr.s_addr = htonl(INADDR_ANY);

	// Associa socket e porta
	if(bind(s, (struct sockaddr *) &si_me, sizeof(si_me)) == -1){
		die("bind");
	}

	// Ouve
	while(1){
		fflush(stdout);

		memset(mensagem, '\0', sizeof(mensagem));
		memset(pacote,'\0', sizeof(pacote));

		// Tenta receber a mensagem
		if((recv_len = recvfrom(s, pacote, TAMANHO_PACOTE, 0, (struct sockaddr *) &si_other, (socklen_t *) &slen)) == -1){
			die("recvfrom()");
		}

		if(rand() % 100 < porcentagem_perda){
			continue;
		}

		sscanf(pacote, "%d %d %d %d %100c", &id_origem, &id_destino, &sequencia, &tipo_pacote, mensagem);

		if(id_destino == id_proprio){
			if(tipo_pacote == ID_PACOTE_DADOS){
				if(janela[id_origem] == sequencia){
					// Mostra mensagem se for para ele
					imprimir("[h] <== Mensagem de roteador %d:", id_origem);
					imprimir("%15s%s", "", mensagem);

					janela[id_origem] = !janela[id_origem];
				}

				montar_pacote_controle(pacote, id_origem, sequencia, "ACK");
				enfileirar_pacote(0, pacote, NAO_GERAR_SEQUENCIA_INTERNA);
			} else if(sequencia == -1){
				if(EXIBIR_VETORES_DISTANCIA == 1){
					imprimir("[h] =v= Vetores de distância recebidos de %d:", id_origem);
					imprimir("%15s%s", "", mensagem);
				}

				conta_roteadores[id_origem] = 0;

				NodoFilaTratamento nodo_tratamento;
				nodo_tratamento.roteador = id_origem;
				for(int i = 0; i < MAX_ROTEADORES; i++){
					nodo_tratamento.vetores[i] = -2;
				}

				int roteador, custo;
				int deslocamento, bytes_lidos;
				deslocamento = 0;
				while(mensagem[deslocamento] != 0){
					sscanf(mensagem + deslocamento, "%d %d,%n", &roteador, &custo, &bytes_lidos);
					deslocamento += bytes_lidos;
					nodo_tratamento.vetores[roteador] = custo;
				}

				enfileirar_tratamento(nodo_tratamento);
			} else {
				if(sequencia == sequencia_ACK[id_origem]){
					imprimir("[h] :-) Confirmação de envio para roteador %d recebida.", id_origem);
					sequencia_ACK[id_origem] = -1;
					sem_post(&semaforos[id_origem]);
				}

			}
		} else {
			// Retransmite se não for
			enfileirar_pacote(0, pacote, NAO_GERAR_SEQUENCIA_INTERNA);
		}
	}

	close(s);
	pthread_exit(NULL);
}

void *thread_timeout(void *data){
	int id_destino = *((int *) data);

	usleep(3000000);
	if(sequencia_ACK[id_destino] != -1){
		sem_post(&semaforos[id_destino]);
	}

	pthread_exit(NULL);
}

void *thread_entrega_confiavel(void *data){
	struct sockaddr_in si_other;
	int s, slen = sizeof(si_other);
	int id_destino;
	char pacote[TAMANHO_PACOTE], mensagem[100];
	pthread_t id_thread_timeout;

	NodoFilaPacote *nodo_pacote = (NodoFilaPacote *) data;
	strcpy(pacote, nodo_pacote->conteudo);
	sscanf(pacote, "%*d %d %*d %*d %100c", &id_destino, mensagem);

	if((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){
		die("socket");
	}

	memset((char *) &si_other, 0, slen);
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(roteadores[tab_roteamento[id_destino]].porta);

	if(inet_aton(roteadores[tab_roteamento[id_destino]].ip , &si_other.sin_addr) == 0){
		fprintf(stderr, "Line 237: inet_aton() failed\n");
		exit(1);
	}

	sequencia_ACK[id_destino] = sequencia[id_destino];

	// Envia mensagem
	for(int tentativas = 0; tentativas < 3 && sequencia_ACK[id_destino] != -1; tentativas++){
		if(tentativas == 0){
			imprimir("[h] ==> Enviando mensagem para roteador %d:", id_destino);
			imprimir("%15s%s", "", mensagem);
		}

		if(sendto(s, pacote, strlen(pacote), 0, (struct sockaddr *) &si_other, slen) == -1){
			die("sendto()");
		}

		if(tentativas == 0){
			imprimir("[h] (=) Esperando ACK.");
		} else {
			imprimir("[h] !=> ACK não recebido. Reenviando mensagem para roteador %d. Esperando ACK.", id_destino);
		}

		pthread_create(&id_thread_timeout, NULL, thread_timeout, &id_destino);
		sem_wait(&semaforos[id_destino]);
	}

	if(sequencia_ACK[id_destino] != -1){
		imprimir("[h] :-/ Isso é embaraçoso, mas não pudemos confirmar a entrega da mensagem para o roteador %d.", id_destino);
	} else {
		sequencia[id_destino] = !sequencia[id_destino];
	}

	close(s);
	free(nodo_pacote);
	sequencia_interna_inicio[id_destino] += 1;

	pthread_exit(NULL);
}

void *thread_entrega_udp(void *data){
	struct sockaddr_in si_other;
	int s, slen = sizeof(si_other);
	int id_origem, id_destino, sequencia, tipo_pacote;
	char pacote[TAMANHO_PACOTE], mensagem[100];

	NodoFilaPacote *nodo_pacote = (NodoFilaPacote *) data;
	strcpy(pacote, nodo_pacote->conteudo);
	sscanf(pacote, "%d %d %d %d %100c", &id_origem, &id_destino, &sequencia, &tipo_pacote, mensagem);

	int proximo_salto = tab_roteamento[id_destino];
	if(tipo_pacote == ID_PACOTE_CONTROLE && sequencia == -1){
		proximo_salto = id_destino;
	}

	if((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){
		die("socket");
	}

	memset((char *) &si_other, 0, slen);
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(roteadores[proximo_salto].porta);

	if(inet_aton(roteadores[proximo_salto].ip , &si_other.sin_addr) == 0){
		fprintf(stderr, "Line 296: inet_aton() failed\n");
		exit(1);
	}

	if(id_origem != id_proprio && id_destino != id_proprio){
		if(sequencia == -1){
			if(EXIBIR_VETORES_DISTANCIA == 1){
				imprimir("[h] <-> Retransmitindo vetores de distância de roteador %d para roteador %d.", id_origem, id_destino);
			}
		} else{
			imprimir("[h] <-> Retransmitindo mensagem com sequência %d de roteador %d para roteador %d.", sequencia, id_origem, id_destino);
		}
	} else if(tipo_pacote == ID_PACOTE_CONTROLE && sequencia != -1){
		imprimir("[h] ==> Enviando ACK para roteador %d.", id_destino);
	} else {
		if(EXIBIR_VETORES_DISTANCIA == 1){
			imprimir("[h] ==> Enviando vetores de distância para %d:", id_destino);
			imprimir("%15s%s", "", mensagem);
		}
	}

	if(sendto(s, pacote, strlen(pacote), 0, (struct sockaddr *) &si_other, slen) == -1){
		die("sendto()");
	}

	close(s);
	free(nodo_pacote);
	pthread_exit(NULL);
}

void *thread_envio(){
	pthread_t id_thread_tmp;
	NodoFilaPacote *nodo;
	int id_destino;

	memset(sequencia, 0, sizeof(sequencia));
	memset(sequencia_ACK, -1, sizeof(sequencia_ACK));

	while(1){
		if(fila_pacotes.inicio != NULL){
			pthread_mutex_lock(&mutex_fila_pacotes);
			nodo = fila_pacotes.inicio;
			fila_pacotes.inicio = fila_pacotes.inicio->proximo;
			pthread_mutex_unlock(&mutex_fila_pacotes);

			sscanf(nodo->conteudo, "%*d %d", &id_destino);
			if(tab_roteamento[id_destino] == -1){
				imprimir("[h] !!! Pacote para roteador %d descartado: rota não encontrada", id_destino);
				free(nodo);
				continue;
			}

			if(nodo->confiavel == 0){
				pthread_create(&id_thread_tmp, NULL, thread_entrega_udp, nodo);
			} else {
				if(sequencia_interna_inicio[id_destino] != nodo->sequencia_interna){
					enfileirar_pacote(1, nodo->conteudo, nodo->sequencia_interna);
					free(nodo);
				} else {
					pthread_create(&id_thread_tmp, NULL, thread_entrega_confiavel, nodo);
				}
			}
		}

		usleep(1000);
	}

	pthread_exit(NULL);
}

void atualizar_tab_roteamento(){
	char pacote[TAMANHO_PACOTE];
	char mensagem[100];
	int deslocamento, bytes_escritos;

	memset(mensagem, 0, sizeof(mensagem));
	deslocamento = 0;

	pthread_mutex_lock(&mutex_att_tabela);
	for(int i = 0; i < MAX_ROTEADORES; i++){
		int melhor_saida = 0;

		for(int j = 0; j < MAX_ROTEADORES; j++){
			if(tab_vetores.vetores[j][i] != -1){
				int custo_j = tab_vetores.vetores[j][i] + tab_vetores.custo[j];
				int custo_melhor_saida = tab_vetores.vetores[melhor_saida][i] + tab_vetores.custo[melhor_saida];
				if(tab_vetores.vetores[melhor_saida][i] == -1 || custo_j < custo_melhor_saida){
					melhor_saida = j;
				}
			}
		}

		int custo_melhor_saida = tab_vetores.vetores[melhor_saida][i] + tab_vetores.custo[melhor_saida];
		if(tab_vetores.vetores[melhor_saida][i] == -1){
			custo_melhor_saida = -1;
			melhor_saida = -1;
		}

		if(custo_melhor_saida > MAX_DIAMETRO || custo_melhor_saida == -1){
			custo_melhor_saida = -1;
			melhor_saida = -1;
		}

		if(custo_melhor_saida != tab_custos[i] || melhor_saida != tab_roteamento[i]){
			if(tab_custos[i] == -1){
				imprimir("[h] #v# Rota estabelecida para o roteador %d: roteador %d com custo %d", i, melhor_saida, custo_melhor_saida);
			} else if(custo_melhor_saida == -1){
				imprimir("[h] !v! Rota perdida para o roteador %d", i);
			} else {
				imprimir("[h] <v> Nova rota para o roteador %d: roteador %d com custo %d", i, melhor_saida, custo_melhor_saida);
			}

			tab_roteamento[i] = melhor_saida;
			tab_custos[i] = custo_melhor_saida;
			sprintf(mensagem + deslocamento, "%d %d,%n", i, tab_custos[i], &bytes_escritos);
			deslocamento += bytes_escritos;

			if(EXIBIR_VETORES_DISTANCIA == 1){
				imprimir_tab_roteamento();
			}
		}
	}
	pthread_mutex_unlock(&mutex_att_tabela);

	if(strcmp(mensagem, "") != 0){
		for(int i = 0; i < MAX_ROTEADORES; i++){
			if(tab_vetores.custo[i] != -1 && i != id_proprio){
				montar_pacote_controle(pacote, i, -1, mensagem);
				enfileirar_pacote(0, pacote, NAO_GERAR_SEQUENCIA_INTERNA);
			}
		}
	}
}


void *thread_update_periodico(){
	char pacote[TAMANHO_PACOTE];
	char mensagem[100];
	int deslocamento, bytes_escritos;

	usleep(200000);
	atualizar_tab_roteamento();

	while(1){
		usleep(5000000); // 5 segundos

		memset(mensagem, 0, sizeof(mensagem));
		deslocamento = 0;
		for(int i = 0; i < MAX_ROTEADORES; i++){
			sprintf(mensagem + deslocamento, "%d %d,%n", i, tab_custos[i], &bytes_escritos);
			deslocamento += bytes_escritos;
		}

		atualizar_tab_roteamento();
		for(int i = 0; i < MAX_ROTEADORES; i++){
			if(tab_vetores.custo[i] != -1 && tab_roteamento[i] != -1 && i != id_proprio){
				montar_pacote_controle(pacote, i, -1, mensagem);
				enfileirar_pacote(0, pacote, NAO_GERAR_SEQUENCIA_INTERNA);
			}
		}
	}
}

void *thread_tratamento(){
	NodoFilaTratamento *nodo;

	while(1){
		if(fila_tratamento.inicio != NULL){
			pthread_mutex_lock(&mutex_fila_tratamento);
			nodo = fila_tratamento.inicio;
			fila_tratamento.inicio = fila_tratamento.inicio->proximo;
			pthread_mutex_unlock(&mutex_fila_tratamento);

			for(int i = 0; i < MAX_ROTEADORES; i++){
				if(nodo->vetores[i] != -2){
					tab_vetores.vetores[nodo->roteador][i] = nodo->vetores[i];
				}
			}

			atualizar_tab_roteamento();

			free(nodo);
		}

		usleep(1000);
	}

	pthread_exit(NULL);
}

void desabilitar_enlace(int roteador){
	for(int i = 0; i < MAX_ROTEADORES; i++){
		tab_vetores.vetores[roteador][i] = -1;
	}
}

void *thread_conta_recebimento(){
	while(1){
		for(int i = 0; i < MAX_ROTEADORES; i++){
			if(tab_vetores.custo[i] != -1 && tab_roteamento[i] != -1 && i != id_proprio){
				conta_roteadores[i] += 1;
				if(conta_roteadores[i] > 15){
					desabilitar_enlace(i);
					atualizar_tab_roteamento();
				}
				if(conta_roteadores[i] == 16){
					imprimir("[h] =~= Desabilitou roteador %d", i);
				}
			}
		}
		usleep(1000000);
	}
}

int main(int argc, char **argv){
	id_proprio = atoi(argv[1]);

	srand(time(NULL));

	memset(tab_roteamento, -1, sizeof(tab_roteamento));
	memset(tab_custos, -1, sizeof(tab_custos));
	memset(conta_roteadores, 0, sizeof(conta_roteadores));

	ler_roteadores(ARQUIVO_ROTEADORES);
	ler_enlaces(ARQUIVO_ENLACES);

	pthread_t id_thread_recebimento, id_thread_envio;
	pthread_t id_thread_update_periodico, id_thread_tratamento;
	pthread_t id_thread_conta_recebimento;

	pthread_create(&id_thread_recebimento, NULL, thread_recebimento, NULL);
	pthread_create(&id_thread_envio, NULL, thread_envio, NULL);
	pthread_create(&id_thread_update_periodico, NULL, thread_update_periodico, NULL);
	pthread_create(&id_thread_tratamento, NULL, thread_tratamento, NULL);
	pthread_create(&id_thread_conta_recebimento, NULL, thread_conta_recebimento, NULL);

	char opcao, mensagem[108];
	int param1, custo;
	char pacote[TAMANHO_PACOTE];

	fila_pacotes.inicio = NULL;
	fila_pacotes.final = NULL;
	memset(sequencia_interna_inicio, 0, sizeof(sequencia_interna_inicio));
	memset(sequencia_interna_final, 0, sizeof(sequencia_interna_final));

	for(int i = 0; i < MAX_ROTEADORES; i++){
		sem_init(&semaforos[i], 0, 0);
	}

	limpar_tela();
	while(1){
		ler(&opcao, &param1, mensagem);

		switch(opcao){
			case 'r':
				imprimir_roteadores();
				break;
			case 'g':
				imprimir_tab_vetores();
				break;
			case 't':
				imprimir_tab_roteamento();
				break;
			case 'p':
				porcentagem_perda = param1;
				imprimir_porcentagem_perda();
				break;
			case 'c':
				custo = atoi(mensagem);
				if(tab_vetores.custo[param1] == -1 && custo != -1){
					tab_vetores.vetores[param1][param1] = 0;
				} else if(custo == -1){
					desabilitar_enlace(param1);
				}
				tab_vetores.custo[param1] = custo;

				atualizar_tab_roteamento();
				break;
			case 'm':
				montar_pacote_dados(pacote, param1, mensagem);
				enfileirar_pacote(1, pacote, GERAR_SEQUENCIA_INTERNA);
				break;
			default:
				for(NodoFilaPacote *i = fila_pacotes.inicio; i != NULL; i = i->proximo){
					imprimir("%d|SI%d|%s", i->confiavel, i->sequencia_interna, i->conteudo);
				}
		}
	}

	return 0;
}
