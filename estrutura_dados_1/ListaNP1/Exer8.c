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
		novo->prox = novo;
		return novo;
	}	
	// Insere no fim se ja existir
	do{
		p=p->prox;
	}while(p->prox != l);
	p->prox = novo;
	novo->prox = l;
	
	return l;
}

void imprimeNormal(Tplista *l){
	Tplista *p = l;
	Tplista *ult = NULL;
	while(p != NULL){
		printf("%d\n", p->info);
		p=p->prox;
	}
	printf("O ultimo aponta pra NULL? %d\n", p == NULL);
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
Tplista *CircPNorm(Tplista *l){
	Tplista *p = l;
	
	do{
		p = p->prox;
	}while(p->prox != l);	
	p->prox = NULL;
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
	imprimeCirc(l);
	printf("Convertendo circular para normal \n");
	l = CircPNorm(l);
	imprimeNormal(l);
	return 0;
}
