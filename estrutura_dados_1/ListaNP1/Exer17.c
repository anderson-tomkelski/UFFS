#include<stdio.h>
#include<stdlib.h>

typedef struct lista {
	int elem;
	struct lista *prox;
}TpLista;

TpLista* inicializa(){
	return NULL;
}

// Inserir elemento
TpLista* inserirElem(TpLista *l, int n){
	TpLista *p = l;
	TpLista *novo = (TpLista *)malloc(sizeof(TpLista));
	novo->elem = n;
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

// Verifica o comprimento da lista
int comprimento(TpLista *l){
	TpLista *p = l;
	int i=0;
	while(p != NULL){
		i++;
		p = p->prox;
	}
	return i;
}

void imprime(TpLista *l){
	TpLista *p = l;
	while(p != NULL){
		printf("%d\n", p->elem);
		p=p->prox;
	}
}

int main(){
	TpLista *l;
	l = inicializa();
	l = inserirElem(l, 10);
	l = inserirElem(l, 15);
	l = inserirElem(l, 20);
	l = inserirElem(l, 25);
	printf("Comprimento = %d\n", comprimento(l));
	imprime(l);
	return 0;
}
