#include<stdio.h>
#include<stdlib.h>

typedef struct lista {
	int coef, exp;
	struct lista *prox;
}TpLista;

TpLista* inicializa(){
	return NULL;
}

// Inserir polinomio
TpLista* inserirPoli(TpLista *l){
	TpLista *p = l;
	TpLista *novo = (TpLista *)malloc(sizeof(TpLista));
	printf("Digite o coef: ");
	scanf("%d", &novo->coef);
	printf("Digite o exp: ");
	scanf("%d", &novo->exp);
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

//Soma com os de mesmo expoente
TpLista* somaPoli(TpLista *l){
	TpLista *p;
	int coefi, expo;
	printf("Digite o coef para somar: ");
	scanf("%d", &coefi);
	printf("Digite o exp para somar: ");
	scanf("%d", &expo);
	for(p = l; p != NULL; p=p->prox){
		if(p->exp == expo)
			p->coef += coefi;
	}
	return l;
}

// Multiplica em todos
TpLista* multiplicaPoli(TpLista *l){
	TpLista *p;
	int coefi, expo;
	printf("Digite o coef para multiplicar: ");
	scanf("%d", &coefi);
	printf("Digite o exp para multiplicar: ");
	scanf("%d", &expo);
	for(p=l; p!= NULL; p=p->prox){
		p->coef = p->coef * coefi;
		p->exp += expo;
	}
	return l;
}

// Deriva para todos os polinomios
TpLista* derivarPoli(TpLista *l){
	TpLista *p;
	for(p=l; p != NULL; p=p->prox){
		p->coef = p->coef * p->exp;
		p->exp--;
	}
	return l;
}

void imprime(TpLista *l){
	TpLista *p = l;
	while(p != NULL){
		printf("%d ^ %d\n", p->coef, p->exp);
		p=p->prox;
	}
}

int main(){
	TpLista *l;
	l = inicializa();
	l = inserirPoli(l);
	l = inserirPoli(l);
	l = somaPoli(l);
	l = multiplicaPoli(l);
	l = derivarPoli(l);
	imprime(l);
	return 0;
}
