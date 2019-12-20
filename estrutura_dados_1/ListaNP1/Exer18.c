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

// Compara duas listas, retorna 1 se igual e 0 se não
int compara(TpLista *l, TpLista *p){
	TpLista *lp = l;
	TpLista *pp = p;
	if(comprimento(lp) != comprimento(pp))
		return 0;
	while(lp != NULL){
		if(lp->elem != pp->elem)
			return 0;
		lp = lp->prox;
		pp = pp->prox;
	}
	return 1;
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
	TpLista *p;
	l = inicializa();
	p = inicializa();
	l = inserirElem(l, 10);
	l = inserirElem(l, 15);
	l = inserirElem(l, 20);
	l = inserirElem(l, 25);
	p = inserirElem(p, 10);
	p = inserirElem(p, 15);
	p = inserirElem(p, 20);
	p = inserirElem(p, 12);
	if(compara(l, p))
		printf("As listas sao iguais\n");
	else
		printf("As listas sao diferentes\n");
	printf("Lista L\n");
	imprime(l);
	printf("Lista P\n");
	imprime(p);
	return 0;
}
