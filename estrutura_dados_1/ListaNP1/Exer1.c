#include <stdio.h>
#include <stdlib.h>

typedef struct lista{
	int info;
	struct lista *prox;
}Tplista;


Tplista *inicializa(){
	return NULL;
}

// Inserir um elemento a esquerda da cabeca da lista
Tplista *insereini(Tplista *l, int e){
	Tplista *p = l;
	Tplista *novo = (Tplista *)malloc(sizeof(Tplista));
	novo->info = e;
	if(l==NULL){
		novo->prox = novo;
	}else{
		novo->prox = l;
		do{				
			p=p->prox;
		}while(p->prox!=l);
		p->prox=novo;
	}
	return novo;
}

void imprime(Tplista *l){
	Tplista *p=l;
	do{
		printf("Informacao: %d\n", p->info);
		p=p->prox;
	}while(p!=l);
}

// Eliminar o elemento de valor x
Tplista *exclui(Tplista *l, int e){
	Tplista *anterior = NULL;
	Tplista *p = l;
	
	if(p->info == e){
		anterior = p;
		do{
			p = p->prox;
		}while(p->prox != l);
		p->prox = anterior->prox;
		free(anterior);
		return p->prox;
	}

	do{
		anterior = p;
		p = p->prox;
	}while(p!=l && p->info != e);
	anterior->prox = p->prox;
	
	free(p);
	return l;
}

Tplista *inseremeio(Tplista *l, int n){
	Tplista *p=l, *anterior = NULL;
	Tplista *novo = (Tplista *)malloc(sizeof(Tplista));
	novo->info = n;

	if(p->info <= n){
		novo->prox = p;
		do{
			p = p->prox;
		}while(p->prox!=l);
		p->prox = novo;
		return novo;
	}else{
		do{
			anterior = p;
			p = p->prox;
		}while(p != l && p->info >= n);
	
		if(anterior != NULL && anterior->prox != NULL){
			anterior->prox = novo;
			novo->prox = p;
			return l;
		}
	}
	return l;
}

Tplista *inserefim(Tplista *l, int e){
	Tplista *p = l;
	Tplista *novo = (Tplista *)malloc(sizeof(Tplista));
	novo->info = e;
	
	do{
		p = p->prox;
	}while(p->prox != l);
	
	p->prox = novo;
	novo->prox = l;
	return l;
}

// Contar o numero de elementos numa lista circular
int countQtd(Tplista *l){
	Tplista *p = l;
	int i=0;
	do{
		p=p->prox;
		i++;
	}while(p!=l);
	return i;
}

// Concatenar duas listas circulares
Tplista *concatLista(Tplista *l1, Tplista *l2){
	Tplista *p = l1;
	Tplista *p2 = l2;
	do{
		p = p->prox;
	}while(p->prox != l1);
	// O ultimo elemento aponta para a cabecao do primeiro elemento da prox lista	
	p->prox = l2;
	do{
		p2 = p2->prox;
	}while(p2->prox != l2);
	// O ultimo elemento da lista dois aponta para o inicio da lista um
	p2->prox = l1;
	return l1;
}

// Fazer uma cópia da lista
Tplista *cpLista(Tplista *l, Tplista *cop){
	Tplista *ini = NULL;
	Tplista *ant = NULL;
	Tplista *p = l;
	do{
		Tplista *novo = (Tplista *)malloc(sizeof(Tplista));
		if(ant!=NULL)
			ant->prox = novo;
		
		novo->info = p->info;

		if(ini == NULL)
			ini = novo;
		ant = novo;
		p = p->prox;
		if(p==l)
			novo->prox = ini;
	}while(p!= l);
	return ini;
}

int main(){
	Tplista *l;
	Tplista *l2;
	Tplista *l3;
	l3 = inicializa();
	l2 = inicializa();
	l2 = insereini(l2, 2);
	l2 = insereini(l2, 5);
	l2 = inseremeio(l2, 3);
	l2 = inserefim(l2, 30);
	l = inicializa();
	l = insereini(l, 10);
	l = insereini(l, 15);
	l = insereini(l, 24);
	l = inseremeio(l, 12);
	l = inserefim(l, 30);
	l = inserefim(l, 33);
	l = inseremeio(l, 32);
	l = insereini(l, 1);
	imprime(l);
	printf("Quantidade de elementos: %d\n", countQtd(l));
	l = exclui(l, 33);
	l = insereini(l, 3);
	l = inseremeio(l, 22);
	l = inserefim(l, 7);
	printf("DEPOIS \n");
	imprime(l);
	printf("Qunatidade de elementos: %d\n", countQtd(l));
	l3 = cpLista(l2, l3);
	printf("IMPRIMINDO L3\n");
	imprime(l3);
	l = concatLista(l, l2);
	printf("Concatenar \n");
	imprime(l);
	return 0;
}

