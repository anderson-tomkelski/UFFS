#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <time.h>
#include <stdarg.h>

#define QTD_LINHAS_MENU 10

void die(char *str){
    perror(str);
    exit(1);
}

char getch(){
	char buf = 0;
	struct termios old = {0};
	fflush(stdout);
	if(tcgetattr(0, &old) < 0)
		perror("tcsetattr()");
	old.c_lflag &= ~ICANON;
	old.c_lflag &= ~ECHO;
	old.c_cc[VMIN] = 1;
	old.c_cc[VTIME] = 0;
	if(tcsetattr(0, TCSANOW, &old) < 0)
		perror("tcsetattr ICANON");
	if(read(0, &buf, 1) < 0)
		perror("read()");
	old.c_lflag |= ICANON;
	old.c_lflag |= ECHO;
	if(tcsetattr(0, TCSADRAIN, &old) < 0)
		perror ("tcsetattr ~ICANON");
	return buf;
}

int qtd_caracteres_especiais(char *str){
	int qtd_especiais = 0;
	for(int i = 0; str[i]; i++){
		qtd_especiais += ((int) str[i] == -61) + 2 * ((int) str[i] == -30);
	}
	return qtd_especiais;
}

int strcmp_limite(char *str1, int limite, char *str2){
	char aux[256];

	strcpy(aux, str1);
	aux[limite] = '\0';

	return strcmp(aux, str2);
}

void strcpy_limite_inferior(char *str1, char *str2, int limite_inferior){
	char aux[256];

	strcpy(aux, str2);
	strcpy(str1, aux + limite_inferior);
}

void adicionar_hora(char *str){
	time_t now;
	struct tm *now_tm;
	char aux[256];

	now = time(NULL);
	now_tm = localtime(&now);

	sprintf(aux, "%s", str);
	sprintf(str, "[%02d:%02d:%02d]%s", now_tm->tm_hour, now_tm->tm_min, now_tm->tm_sec, aux);
}

void imprimir_linha(int linha, char *str){
	struct winsize w;
	char str_linha[256];

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	str[w.ws_col] = 0;
	sprintf(str_linha, "\033[%d;1H%%%ds", w.ws_row - linha + 1, -w.ws_col - qtd_caracteres_especiais(str));

	printf(str_linha, str);
}

char buffer[256];
extern int id_proprio;

void imprimir(char *str, ...){
	va_list aptr;
	char aux[512], aux2[128], menu[QTD_LINHAS_MENU][128] = {
		"---------------------------------------------------------------------------------------------------------------------",
		" ROTEADOR %d",
		"---------------------------------------------------------------------------------------------------------------------",
		" r                | Lista todos os roteadores ",
		" g                | Mostra a tabela de vetores de distância",
		" t                | Mostra a tabela de roteamento",
		" p {pprd}         | Define que este roteador perderá {pprd} por cento dos pacotes",
		" m {idr} {msg}    | Manda a mensagem {msg} para o roteador {idr}",
		" c {idr} {c}      | Muda para {c} o custo do enlace para o roteador {idr} (-1 para queda do enlace)",
		"---------------------------------------------------------------------------------------------------------------------"
	};
	sprintf(menu[1], menu[1], id_proprio);

	va_start(aptr, str);
	vsprintf(aux, str, aptr);
	va_end(aptr);

	if(strcmp_limite(aux, 3, "[h]") == 0){
		strcpy_limite_inferior(aux, aux, 3);
		adicionar_hora(aux);
	}

	if(strcmp(aux, "") != 0){
		sprintf(aux2, "\n");
		imprimir_linha(1, aux2);
		imprimir_linha(QTD_LINHAS_MENU + 2, aux);
	}

	memset(aux2, ' ', sizeof(aux2));
	sprintf(aux2, "%s", buffer);

	int pos_cursor = strlen(buffer);
	aux2[pos_cursor] = -30;
	aux2[pos_cursor + 1] = -106;
	aux2[pos_cursor + 2] = -120;

	sprintf(aux, "> %s", aux2);
	imprimir_linha(1, aux);
	fflush(stdout);

	for(int i = 0; i <= QTD_LINHAS_MENU - 1; i++){
		imprimir_linha(QTD_LINHAS_MENU + 1 - i, menu[i]);
		fflush(stdout);
	}
}

void limpar_tela(){
	printf("\033[2J");
}

void analisar_buffer(char *opcao, int *param1, char *mensagem){
	int pos, pos_add;

	sscanf(buffer, "%c%n", opcao, &pos);

	if(*opcao == 'p' || *opcao == 'm' || *opcao == 'c'){
		sscanf(buffer + pos, "%d%n", param1, &pos_add);
		pos += pos_add + 1;
		while(buffer[pos] == ' ' && pos < 110){
			pos += 1;
		}
	}

	if(*opcao == 'c' || (*opcao == 'm' && pos != 110)){
		sscanf(buffer + pos, "%100c", mensagem);
	}
}

void ler(char *opcao, int *param1, char *mensagem){
	int c, pos, ignorar;

	c = pos = ignorar = 0;
	memset(buffer, '\0', sizeof(buffer));
	buffer[sizeof(buffer) - 1] = 0;
	while(c != '\n' || pos == 0){
		if(c != -61){
			imprimir("");
		}

		c = getch();

		if(ignorar > 0){
			// Ignora uma quantidade de caracteres
			ignorar -= 1;
			continue;
		}

		if(c == 27){
			// Ignora setas e outras teclas especiais
			ignorar = 2;
		} else if(c == 127){
			// Backspace
			if(pos > 0){
				buffer[--pos] = '\0';
				if(pos > 0 && buffer[pos - 1] == -61){
					buffer[--pos] = '\0';
				}
			}
		} else if(c != '\n'){
			if(c == -61 && pos >= 103){
				ignorar = 1;
			} else if(pos < 104){
				buffer[pos++] = c;
			}
		} else {
			buffer[pos] = 0;
		}
	}

	memset(mensagem, '\0', 108);
	analisar_buffer(opcao, param1, mensagem);
}
