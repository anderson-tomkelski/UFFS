#include <stdio.h>
#include <stdlib.h>

typedef struct lista{
	int info;
	struct lista *prox;
}Tplista;


Tplista *inicializa(){
	return NULL;
}

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

int main(){
	Tplista *l;
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
	l = exclui(l, 33);
	l = insereini(l, 3);
	l = inseremeio(l, 22);
	l = inserefim(l, 7);
	printf("DEPOIS \n");
	imprime(l);
	return 0;
}

