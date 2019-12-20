#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX 1000

typedef struct lista{
	int num;
	struct lista *prox;
}Lista;

void buble(int *a, int n){
	int i, aux, trocou;
	do{
		trocou = 0;
		for(i=1; i<n; i++){
			if(a[i-1] > a[i]){
				aux = a[i];
				a[i] = a[i-1];
				a[i-1] = aux;
				trocou = 1;
			}
		}
	}while(trocou==1);
}

void bublelista(Lista *l){
	Lista *p = NULL;
	Lista *pAnt = NULL;
	int aux, trocou;
	do{
		p = l->prox;
		pAnt = l;
		trocou = 0;
		while(p != NULL){
			if(pAnt->num > p->num){
				aux = p->num;
				p->num = pAnt->num;
				pAnt->num = aux;
				trocou = 1;
			}
			p = p->prox;
			pAnt = pAnt->prox;
		}
	}while(trocou==1);
}


Lista* inserelista(Lista *l, int valor){
	Lista *novo = (Lista *) malloc(sizeof(Lista));
	novo->num = valor;
	novo->prox = l;
	return novo;
}

Lista* inicializa(){
	return NULL;
}


void imprime(int *a, int n){
	int i;
	for(i=0; i<MAX; i++)
		printf("%d\t", a[i]);
}

void imprimelista(Lista *l){
	Lista *p = l;
	do{
		printf("%d\t", p->num);
		p = p->prox;
	}while(p != NULL);
}

int main(){
	int vet[MAX];
	int i;
	Lista *nodo;
	clock_t inicio, fim;
	for(i=0; i<MAX; i++)
		vet[i] = rand()%100;
	printf("Vetor - Desordenado\n");
	imprime(vet, 30);
	inicio = clock();
	buble(vet, 30);
	fim = clock();
	printf("\nVetor - Ordenado\n");
	printf("Tempo para ordenar vetor: %lf\n", ((float)(fim-inicio)/CLOCKS_PER_SEC));
	imprime(vet, 30);
	printf("\n\n\n");

	printf("-----------------LISTA------------------------");
	nodo = inicializa();
	for(i=0; i<MAX; i++)
		nodo = inserelista(nodo, rand()%100);
	printf("\nLista - Desordenado\n");
	imprimelista(nodo);
	inicio = clock();
	bublelista(nodo);
	fim = clock();
	printf("\nLista - Ordenada\n");
	printf("Tempo para ordenar lista : %lf\n", ((float)(fim-inicio)/CLOCKS_PER_SEC));
	imprimelista(nodo);
	printf("\n");
	return 0;
}
