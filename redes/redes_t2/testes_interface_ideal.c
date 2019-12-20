#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>

char getch(){
	char buf=0;
	struct termios old={0};
	fflush(stdout);
	if(tcgetattr(0, &old)<0)
		perror("tcsetattr()");
	old.c_lflag&=~ICANON;
	old.c_lflag&=~ECHO;
	old.c_cc[VMIN]=1;
	old.c_cc[VTIME]=0;
	if(tcsetattr(0, TCSANOW, &old)<0)
		perror("tcsetattr ICANON");
	if(read(0,&buf,1)<0)
		perror("read()");
	old.c_lflag|=ICANON;
	old.c_lflag|=ECHO;
	if(tcsetattr(0, TCSADRAIN, &old)<0)
		perror ("tcsetattr ~ICANON");
	return buf;
}

int caracteres_especiais(char *str){
	int qtd_especiais = 0;
	for(int i = 0; str[i]; i++){
		qtd_especiais += (int) str[i] == -61;
	}
	return qtd_especiais;
}

void adicionar_hora(char *str){
	time_t now;
	struct tm *now_tm;
	char aux[256];

	now = time(NULL);
	now_tm = localtime(&now);

	sprintf(aux, "%s", str);
	sprintf(str, "[%02d:%02d:%02d] %s", now_tm->tm_hour, now_tm->tm_min, now_tm->tm_sec, aux);
}

void imprimir_linha(int linha, char *str){
	struct winsize w;
	char str_linha[256];

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	str[w.ws_col] = 0;
	sprintf(str_linha, "\033[%d;1H%%%ds", w.ws_row - linha + 1, -w.ws_col - caracteres_especiais(str));

	printf(str_linha, str);
}

int main(){
	int pos = 0;
	char c = 0, aux[512], buffer[256];
	int passar = 0;

	memset(buffer, ' ', sizeof(buffer));

	printf("\033[2J");
	while(1){
		if(c != -61){
			sprintf(aux, "FIXOOOO");
			imprimir_linha(3, aux);
			sprintf(aux, "Noice");
			imprimir_linha(2, aux);
			sprintf(aux, " %s", buffer);
			imprimir_linha(1, aux);
		}

		c = getch();
		if(c == '\n'){
			pos = 0;
			memset(buffer, ' ', sizeof(buffer));
		} else if(c == 127){
			if(pos > 0){
				buffer[--pos] = ' ';
				if(buffer[pos - 1] == -61){
					buffer[--pos] = ' ';
				}
			}
			passar = 0;
		} else {
			printf("\n");
			sprintf(aux, "Apertou %d", c);
			adicionar_hora(aux);
			imprimir_linha(4, aux);
			if(c == -61 && pos >= 99){
				passar = 1;
			} else if(pos < 100 && passar == 0){
				buffer[pos++] = c;
			} else {
				passar = 0;
			}
		}
	}

	return 0;
}
