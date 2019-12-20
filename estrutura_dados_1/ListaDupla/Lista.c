#include <stdio.h>
#include <stdlib.h>

// Struct do nodo da lista
typedef struct lista{
	int info;
	struct lista *prox;
	struct lista *anterior;
}Tplista;


Tplista *inicializa(){
	return NULL;
}

Tplista *insereini(Tplista *l, int e){
	Tplista *novo = (Tplista *)malloc(sizeof(Tplista));
	// Caso nao for o primeiro nodo aponta para o prox
	if(l!=NULL)
		l->anterior = novo;
	novo->info = e;
	novo->prox = l;
	novo->anterior = NULL;
	return novo;
}

void imprime(Tplista *l){
	Tplista *p;
	for(p = l; p != NULL; p = p->prox){
		printf("Informacao: %d\n", p->info);
	}
}

Tplista *exclui(Tplista *l, int e){
	Tplista *p = l;
	Tplista *proxel = NULL, *nodoExcl = NULL;
	
	while(p != NULL && p->info != e){
		p = p->prox;
	}

	nodoExcl = p;
	proxel = p->prox;
	//Se nao encontrar
	if (p == NULL){
		return l;
	}
	//Se for o primeiro nodo
	if (p->anterior == NULL){
		l = p->prox;
        	l->anterior = NULL;
	// Se for o ultim nodo
	}else if(proxel == NULL){
        	p = p->anterior;
        	p->prox = NULL;
    	}else{
		// Se fr um nodo no meio
		proxel->anterior = p->anterior;
		p = p->anterior;
		p->prox = proxel;
	}
	free(nodoExcl);
	return l;
}

Tplista *inseremeio(Tplista *l, int n){
	Tplista *p=l, *elAnt=NULL;
	Tplista *novo = (Tplista *)malloc(sizeof(Tplista));
	novo->info = n;

	while(p->prox != NULL && p->info > n){
		p = p->prox;
	}
	
    elAnt = p->anterior;
    // SE for menor que o primeir elemento
    if(p->prox == NULL){
        p->prox = novo;
        novo->anterior = p->prox;
        novo->prox = NULL;
    //SE for menor que o ultimo elemento
    }else if(elAnt == NULL){
        novo->prox = p;
        p->anterior = novo;
        novo->anterior = NULL;
        return(novo);
    }else{
    //SE estiver entre dois nodos
        novo->prox = p;
        novo->anterior = elAnt;
        elAnt->prox = novo;
        p->anterior = novo;
    }

	return l;
}

Tplista *inserefim(Tplista *l, int e){
	Tplista *p = l;
	Tplista *novo = (Tplista *)malloc(sizeof(Tplista));
	novo->info = e;
	// Vai ate o ultimo nodo
	while(p->prox != NULL){
		p = p->prox;
	}
	// Faz a troca dos aponteramento
	p->prox = novo;
	novo->prox = NULL;
	novo->anterior = p;
	return l;
}

int main(){
	Tplista *l;
	l = inicializa();
	l = insereini(l, 10);
	l = insereini(l, 15);
	l = insereini(l, 24);
	l = inseremeio(l, 50);
	l = inserefim(l, 30);
	l = inserefim(l, 33);
	l = inseremeio(l, 12);
	l = insereini(l, 1);
	imprime(l);
	l = exclui(l, 24);
    	l = inseremeio(l, 0);
	printf("DEPOIS - EXCLUIU 24 E INSERIU 0 n\n");
	imprime(l);
    	l = exclui(l, 1);
    	l = exclui(l, 33);
    	l = inseremeio(l, 40);
	l = exclui(l, 0);
    	printf("DEPOIS - EXCLUIU 1 E 33 E 0 E INSERIU 40 \n\n");
    	imprime(l);
	return 0;
}

