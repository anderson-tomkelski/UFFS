#include <stdio.h>
#include <strings.h>

typedef struct _pilha{
	char vlr[100];
	int topo;
} _pilha;

void PUSH(char letra, _pilha * pilha){
	pilha->topo++;
	pilha->vlr[pilha->topo] = letra;
}

char POP(_pilha * pilha){
	return(pilha->vlr[pilha->topo]);
}

int main(){
	_pilha pilha;
	pilha.topo = -1;
	char frase[100];
	int tamanho, i;
	printf("Entre com uma string: ");
	fgets(frase, 100, stdin);
	frase[strlen(frase)-1] = 0;
	for(i=0; i<=strlen(frase); i++){
		if(frase[i] != '\0' && frase[i] != ' '){
			PUSH(frase[i], &pilha);
		}else{
			while(pilha.topo>-1){
				frase[i-1-pilha.topo] = POP(&pilha);
				pilha.topo--;
			}
		}
	}
	printf("%s", frase);
	return(0);
}
