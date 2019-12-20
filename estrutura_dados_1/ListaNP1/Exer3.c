#include<stdio.h>
#include<stdlib.h>

typedef struct lista {
	char letra;
	struct lista *prox;
} TpLista;

TpLista* inicializa(){
	return NULL;
}


// Troca a incidencia da palavra pela palavra escolhida
TpLista* trocaPalavra(TpLista *l, char P, char Q){
	TpLista *end;
	for(end=l; end != NULL; end = end->prox){
		if(end->letra == P)
			end->letra = Q;
	}
	return l;
}


// Inserir letra
TpLista* inserirLetra(TpLista *l, char alpha){
	TpLista *p = l;
	TpLista *novo = (TpLista *)malloc(sizeof(TpLista));
	novo->letra = alpha;
	// Insere no inicio se ainda nao existir nenhum
	if(p == NULL){
		novo->prox = l;
		return novo;
	}	
	// Insere no fim se ja existir
	while(p->prox != NULL)
		p=p->prox;
	p->prox = novo;
	novo->prox = NULL;
	
	return l;
}

void imprimir(TpLista *l){
	TpLista *p = l;
	for(p=l; p != NULL; p=p->prox){
		printf("%c\n", p->letra);
	}
}

int main(){
	TpLista *l;
	l = inicializa();
	l = inserirLetra(l, 'A');
	l = inserirLetra(l, 'B');
	l = inserirLetra(l, 'C');
	l = inserirLetra(l, 'D');
	l = inserirLetra(l, 'D');
	l = inserirLetra(l, 'D');
	l = inserirLetra(l, 'E');
	imprimir(l);
	printf("Troca D por A\n");
	l = trocaPalavra(l, 'D', 'A');
	imprimir(l);
	return 0;
}
