#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct lista {
	char info;
	struct lista *prox;
} TpLista;

TpLista* inicializa(){
	return NULL;
}

TpLista* inserir(TpLista *l, char n){
	TpLista *p = l;
	TpLista *novo = (TpLista *)malloc(sizeof(TpLista));
	novo->info = n;
	// Cria no inicio se ainda não existir
	if(p == NULL){
		novo->prox = l;
		return novo;
	}
	// Insere no fim se já existir
	while(p->prox != NULL){
		p = p->prox;
	}
	p->prox = novo;
	novo -> prox = NULL;
	return l;
}

TpLista* exclui(TpLista *l, char val){
	TpLista *anterior = NULL;
	TpLista *p = l;
	
	while(p != NULL && p->info != val){
		anterior = p;
		p = p->prox;
	}
	
	if(anterior == NULL){
		l = p->prox;
	}else{
		anterior->prox = p->prox;
	}
	free(p);
	
	return l;
}

TpLista* retira(TpLista *l, TpLista *tmp){
	TpLista *p = l;
	TpLista *ptmp = tmp;
	TpLista *ant = NULL;
	TpLista *antex = NULL;
	while(ptmp != NULL){
		while(p != NULL){
			if(p->info == ptmp->info){
				l = exclui(l, ptmp->info);
			}
			p = p->prox;
		}
		p = l;
		ptmp = ptmp->prox;
	}
	return l;	 
}

void imprime(TpLista *l){
	TpLista *p = l;
	while(p != NULL){
		printf("%c", p->info);
		p = p->prox;
	}
}

int main(){
	// Cria a lista
	TpLista *l;
	l = inicializa();
	l = inserir(l, 'a');
	l = inserir(l, 'b');
	l = inserir(l, 'c');
	l = inserir(l, 'd');
	printf("Imprime lista l: \n");
	imprime(l);
	printf("\n");
	//Cria a lista tmp
	TpLista *tmp;
	tmp = inicializa();
	tmp = inserir(tmp, 'a');
	tmp = inserir(tmp, 'c');
	printf("Imprime lista tmp: \n");
	imprime(tmp);
	printf("\n");
	l = retira(l, tmp);
	printf("Apos excluir: \n");
	imprime(l);
	printf("\n");
	
	return 0;
}
