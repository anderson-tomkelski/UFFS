#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _pilha {
	char exp[100];
	int topo;
} _pilha;

void PUSH(char caractere, _pilha *pilha){
	pilha->topo++;
	pilha->exp[pilha->topo] = caractere;
}

char POP(_pilha *pilha){
	return(pilha->exp[pilha->topo]);
}


int validaDois(char ultimoChar, _pilha *pilha){
	if(ultimoChar == '(' && POP(pilha) == ')' && ultimoChar != ')')
		return 1;
	else
		return 0;
}

int main(){
	_pilha pilha;
	pilha.topo = -1;
	char expressao[100], ultimoPop=' ';
	int i, direita=0, esquerda=0;
	printf("Digite a expressao matematica: ");
	fgets(expressao, 100, stdin);
	expressao[strlen(expressao)-1] = 0;
	// Empilha de tras pra frente	
	for(i=strlen(expressao); i>=0; i--){
		if(expressao[i] != '\0'){
			PUSH(expressao[i], &pilha);
		}
	}

	while(pilha.topo>-1){
		if(POP(&pilha) == '(' || POP(&pilha) == ')'){
			if(ultimoPop == ' '){
				ultimoPop = POP(&pilha);
			} else{
				if(!validaDois(ultimoPop, &pilha)){
					printf("Viola condicao 2\n");
					break;
				}
				ultimoPop = ' ';
			}
			// ValidaUm
			if(POP(&pilha) == '(')
				esquerda++;
			else if(POP(&pilha) == ')')
				direita++;
		}
		pilha.topo--;
	}
	if(esquerda != direita && pilha.topo==-1)
		printf("Viola condicao 1\n");
	return 0;
}
