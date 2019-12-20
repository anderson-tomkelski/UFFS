#include <stdio.h>
#include <stdlib.h>

typedef struct lista{
	int info;
	struct lista *prox;
}Tplista;


Tplista *inicializa(){
	return NULL;
}

// Inserir elemento
Tplista* inserir(Tplista *l, int n){
	Tplista *p = l;
	Tplista *novo = (Tplista *)malloc(sizeof(Tplista));
	novo->info = n;
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

void imprimeNormal(Tplista *l){
	Tplista *p = l;
	
	while(p != NULL){
		printf("%d\n", p->info);
		p=p->prox;
	}
}

void imprimeCirc(Tplista *l){
	Tplista *p = l;
	do{
		printf("%d\n", p->info);
		p = p->prox;
	}while(p != l);
	printf("p->prox != NULL %d\n", p->prox != NULL);
}

// Converte a lista de normal para circular
Tplista *normPCirc(Tplista *l){
	Tplista *p = l;

	while(p->prox != NULL){
		p = p->prox;
	}
	p->prox = l;
	return l;
} 

int main(){
	Tplista *l;
	l = inicializa();
	l = inserir(l, 10);
	l = inserir(l, 15);
	l = inserir(l, 24);
	l = inserir(l, 12);
	l = inserir(l, 30);
	l = inserir(l, 33);
	l = inserir(l, 32);
	l = inserir(l, 1);
	imprimeNormal(l);
	printf("Convertendo e imprime 1 se o final aponta para o inicio \n");
	l = normPCirc(l);
	imprimeCirc(l);
	return 0;
}
