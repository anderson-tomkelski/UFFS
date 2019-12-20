#include<stdio.h>
#include<stdlib.h>

typedef struct _pilha{
	char elem[80];
	int topo;
} _pilha;

void PUSH(char letra, _pilha *pilha){
	pilha->topo++;
	pilha->elem[pilha->topo] = letra;
}

char POP(_pilha * pilha){
	return(pilha->elem[pilha->topo]);
}

int main(){
	_pilha pilha;
	pilha.topo = -1;
	int i;
	// Empilha
	for(i=0; i<80; i++){
		PUSH('a', &pilha);
	}
	// Desempilha
	while(pilha.topo>-1){
		printf("%c[%d]\n", POP(&pilha), pilha.topo);
		pilha.topo--;
	}	
	return 0;
}
