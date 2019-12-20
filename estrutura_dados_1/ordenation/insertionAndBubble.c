# include<stdio.h>
# include<stdlib.h>
# include<time.h>
# define tamanho 10

typedef struct lista{
	int valor;
	struct lista *prox;
}list;

list * inicializa(){
	return NULL;
}

void PreencheVetor(int * vetor){
	int i;
	for(i=0; i<tamanho; i++)
		vetor[i] = rand() % 100;
}

list * PreencheLista(list* l){
	list *novo = (list *) malloc(sizeof(list));
	if(!novo){
		return NULL;
	}
	novo->valor = rand() % 100;
	novo->prox = l;
	return novo;
}

void ImprimeVetor(int * vetor){
	int i;
	for(i=0; i<tamanho; i++)
		printf("%d - ", vetor[i]);
}

void ImprimeLista(list *l){
	list *p;
	for(p=l; p != NULL; p = p->prox){
		printf("%d - ", p->valor);
	}
}

void InsertionSort(int * vetor){
	int i, chave, j;
	for(j=1; j<tamanho; j++){
		chave = vetor[j];
		i = j - 1;
		while(i >=0 && vetor[i] > chave){
			vetor[i+1] = vetor[i];
			i = i - 1;
		}
		vetor[i + 1] = chave;
	}
}

list * next(list* l, int size){
	int i;
	for(i=0; i<size; i++){
		l = l->prox;
	}
	return l;
}

void InsertionSortList(list *l){
	list *laux = l;
	list *aux = l;
	int j, i, chave;
	for(j=1; j<tamanho; j++){
		aux = next(aux, j);
		chave = aux->valor;
		i = j - 1;
		aux = l;
		aux = next(aux, i);
		while(i >= 0 && aux->valor > chave){
			laux = l;
			aux = l;
			laux = next(laux, i+1);
			aux = next(aux, i);
			laux->valor = aux->valor;
			i = i -1;
		}
		aux = l;
		aux = next(aux, i+1);
		aux->valor = chave;
		aux = l;
	}
}

void trocar(int* maior, int* menor){
	int aux;
	aux = *maior;
	*maior = *menor;
	*menor = aux;
} 

void BubbleSortVetores(int* vetor){
	int i, trocou;	
	do{
		trocou = 0;
		for(i=1; i<tamanho; i++){
			if(vetor[i-1] > vetor[i]){
				trocar(&(vetor[i-1]), &(vetor[i]));
				trocou = 1;
			}
		}
	}while(trocou == 1);
}

void BubbleSortLista(list* l){
	int i, trocou;
	list *laux = l;
	list *aux = l;
	do{
		trocou = 0;
		for(i=1; i<tamanho; i++){
			laux = next(laux, i-1);
			aux = next(aux, i);
			if(laux->valor > aux->valor){
				trocar(&(laux->valor), &(aux->valor));
				trocou = 1;
			}
			laux = l;
			aux = l;
		}
	}while(trocou == 1);
}

int main(){
	clock_t inicio, fim;
	int vetor[tamanho], i=0;
	PreencheVetor(vetor);
	printf("Vetor desordenado\n");
	ImprimeVetor(vetor);
	inicio = clock();
	InsertionSort(vetor);
	fim = clock();
	printf("\nA funcao insertionSort para vetores demora : %ld\n", ((fim-inicio)/CLOCKS_PER_SEC));
	printf("Vetor ordenado\n");
	ImprimeVetor(vetor);

	list *l;
	l = inicializa();
	while(i<tamanho){
		l = PreencheLista(l);
		i++;
	}

	printf("\n\nLista desordenada\n");
	ImprimeLista(l);
	inicio = clock();
	InsertionSortList(l);
	fim = clock();
	printf("\nA funcao insertion para lista demora : %ld\n", ((fim-inicio)/CLOCKS_PER_SEC));
	printf("Lista ordenada\n");
	ImprimeLista(l);
	free(l);	

	printf("\n\n\nBubbleSort Vetores\n\n");
	PreencheVetor(vetor);
	printf("Vetor desordenado\n");
	ImprimeVetor(vetor);
	inicio = clock();
	BubbleSortVetores(vetor);
	fim = clock();
	printf("\nA funcao BubbleSort para vetores demora : %ld\n", ((fim-inicio)/CLOCKS_PER_SEC));
	printf("Vetor ordenado\n");
	ImprimeVetor(vetor);
	
	printf("\n\nBubbleSort Lista\n\n");
	l = inicializa();
	i = 0;
	while(i<tamanho){
		l = PreencheLista(l);
		i++;
	}

	printf("\n\nLista desordenada\n");
	ImprimeLista(l);
	inicio = clock();
	BubbleSortLista(l);
	fim = clock();
	printf("\nA funcao BubbleSort para lista demora : %ld\n", ((fim-inicio)/CLOCKS_PER_SEC));
	printf("Lista ordenada\n");
	ImprimeLista(l);
	printf("\n");
	return 0;
}
