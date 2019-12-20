#include<stdio.h>
#include<stdlib.h>

typedef struct lista {
	int info;
	struct lista * prox;
}TpLista;

TpLista* inicializa();
TpLista* insereIni(TpLista* l, int e);
TpLista* insereMeio(TpLista* l, int e);
void imprime(TpLista* l);

int main(){
	TpLista* l;
	l = inicializa();
	l = insereIni(l, 20);
	l = insereIni(l, 10);
     	l = insereMeio(l, 12);
	imprime(l);
	return(0);
}

TpLista* inicializa(){
	return NULL;
}
TpLista* insereIni(TpLista* l, int e){
	TpLista* novo = (TpLista *) malloc(sizeof(TpLista));
	novo->info = e;
	novo->prox = l;
	return novo;
}

TpLista* insereMeio(TpLista* l, int e){
    TpLista* anterior = NULL;
    TpLista* p = l;
    TpLista* bloco = (TpLista *) malloc(sizeof(TpLista));
    while(p != NULL && p->info < e){
        anterior = p; 
        p = p->prox;
    }
    if(anterior == NULL){
	     	
    bloco->info = e;
    bloco->prox = p;
    anterior->prox = bloco;

    return l;
}

void imprime(TpLista* l){
	TpLista* p;
	for(p=l; p != NULL; p = p->prox){
		printf("Informacao = %d\n", p->info);
	}
}
