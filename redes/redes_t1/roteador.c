#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "structs_e_defines.h"
#include "ler_e_imprimir_estruturas.h"
#include "preencher_tab_roteamento.h"
#include "interface.h"

int id_proprio;
Roteador roteadores[MAX_ROTEADORES];
Grafo grafo;
int tab_roteamento[MAX_ROTEADORES];

int origem_ACK, sequencia_ACK, confirmado;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int terminou_timeout;

int porcentagem_perda = 0;

void *thread_recebimento(){
	struct sockaddr_in si_me, si_other;
    int s, slen = sizeof(si_other), recv_len;
	int id_origem, id_destino, ack, sequencia, janela[MAX_ROTEADORES];
	char pacote[128], mensagem[100];

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
        if((recv_len = recvfrom(s, pacote, 128, 0, (struct sockaddr *) &si_other, (socklen_t *) &slen)) == -1){
            die("recvfrom()");
        }

		if(rand() % 100 < porcentagem_perda){
			continue;
		}

		sscanf(pacote, "%d %d %d %d %100c", &id_origem, &id_destino, &sequencia, &ack, mensagem);

		if(id_destino == id_proprio){
			if(ack == -1){
				if(janela[id_origem] == sequencia){
					// Mostra mensagem se for para ele
					imprimir("[h] <== Mensagem de roteador %d:", id_origem);
					imprimir("%15s%s", "", mensagem);

					janela[id_origem] = !janela[id_origem];
				}

				sprintf(pacote, "%d %d %d %d %s", id_proprio, id_origem, sequencia, sequencia, "ACK");

				memset((char *) &si_other, 0, slen);
				si_other.sin_family = AF_INET;
				si_other.sin_port = htons(roteadores[tab_roteamento[id_origem]].porta);

				if (inet_aton(roteadores[tab_roteamento[id_origem]].ip , &si_other.sin_addr) == 0){
					fprintf(stderr, "inet_aton() failed\n");
					exit(1);
				}

				imprimir("[h] ==> Enviando ACK para roteador %d.", id_origem);

				if(sendto(s, pacote, recv_len, 0, (struct sockaddr*) &si_other, slen) == -1){
					die("sendto()");
				}
			} else {
				if(sequencia == sequencia_ACK && id_origem == origem_ACK){
					imprimir("[h] :-) Confirmação de envio recebida.");
					confirmado = 1;
					pthread_mutex_unlock(&mutex);
				}
			}
		} else {
			// Retransmite se não for
			memset((char *) &si_other, 0, slen);
			si_other.sin_family = AF_INET;
			si_other.sin_port = htons(roteadores[tab_roteamento[id_destino]].porta);

			if(inet_aton(roteadores[tab_roteamento[id_destino]].ip , &si_other.sin_addr) == 0){
				fprintf(stderr, "inet_aton() failed\n");
				exit(1);
			}

			imprimir("[h] <-> Retransmitindo mensagem com sequência %d de roteador %d para roteador %d.", sequencia, id_origem, id_destino);

			if(sendto(s, pacote, recv_len, 0, (struct sockaddr*) &si_other, slen) == -1){
				die("sendto()");
			}
		}
    }

    close(s);
	pthread_exit(NULL);
}

void *thread_timeout(){
	usleep(300000);
	pthread_mutex_unlock(&mutex);

	terminou_timeout = 1;
	pthread_exit(NULL);
}

void *thread_envio(){
	struct sockaddr_in si_other;
    int s, slen = sizeof(si_other);
	int id_destino, sequencia[MAX_ROTEADORES];
    char mensagem[108], pacote[128];
    char opcao, param1;
	pthread_t id_thread_timeout;

	memset(sequencia, 0, sizeof(sequencia));

    if((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){
        die("socket");
	}

	limpar_tela();
    while(1){
		ler(&opcao, (int *) &param1, mensagem);

		switch(opcao){
			case 'r':
				imprimir_roteadores();
				continue;
			case 'g':
				imprimir_grafo();
				continue;
			case 't':
				imprimir_tab_roteamento();
				continue;
			case 'p':
				porcentagem_perda = param1;
				imprimir_porcentagem_perda();
				continue;
			case 'm':
				id_destino = param1;
				break;
			default:
				continue;
		}

		memset((char *) &si_other, 0, slen);
		si_other.sin_family = AF_INET;
		si_other.sin_port = htons(roteadores[tab_roteamento[id_destino]].porta);

		if(inet_aton(roteadores[tab_roteamento[id_destino]].ip , &si_other.sin_addr) == 0){
			fprintf(stderr, "inet_aton() failed\n");
			exit(1);
		}

		// Monta pacote
		memset(pacote, '\0', sizeof(pacote));
		sprintf(pacote, "%d %d %d %d %s", id_proprio, id_destino, sequencia[id_destino], -1, mensagem);

		origem_ACK = id_destino;
		sequencia_ACK = sequencia[id_destino];
		confirmado = 0;

		pthread_mutex_unlock(&mutex);
		pthread_mutex_lock(&mutex);
		// Envia mensagem
		for(int tentativas = 0; tentativas < 3 && confirmado == 0; tentativas++){
			if(tentativas == 0){
				imprimir("[h] ==> Enviando mensagem para roteador %d:", id_destino);
				imprimir("%15s%s", "", mensagem);
			}

			if(sendto(s, pacote, strlen(pacote), 0, (struct sockaddr *) &si_other, slen) == -1){
				die("sendto()");
			}

			terminou_timeout = 0;
			pthread_create(&id_thread_timeout, NULL, thread_timeout, NULL);

			if(tentativas == 0){
				imprimir("[h] (=) Esperando ACK.");
			} else {
				imprimir("[h] !=> ACK não recebido. Reenviando mensagem para roteador %d. Esperando ACK.", id_destino);
			}

			// Auto trava
			pthread_mutex_lock(&mutex);

			if(terminou_timeout == 0){
				pthread_cancel(id_thread_timeout);
			}
		}

		if(confirmado == 0){
			imprimir("[h] :-/ Isso é embaraçoso, mas não pudemos confirmar a entrega da mensagem.");
		} else {
			sequencia[id_destino] = !sequencia[id_destino];
		}
    }
    close(s);

	pthread_exit(NULL);
}

int main(int argc, char **argv){
	id_proprio = atoi(argv[1]);

	srand(time(NULL));

	ler_roteadores(ARQUIVO_ROTEADORES);
	ler_enlaces(ARQUIVO_ENLACES);
	preencher_tab_roteamento(id_proprio);

	pthread_t id_thread_recebimento, id_thread_envio;

	pthread_create(&id_thread_recebimento, NULL, thread_recebimento, NULL);
	pthread_create(&id_thread_envio, NULL, thread_envio, NULL);

	pthread_join(id_thread_recebimento, NULL);
	pthread_join(id_thread_envio, NULL);

	return 0;
}
