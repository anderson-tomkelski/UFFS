#include<stdio.h>
#include<time.h>

void trocar(int *v, int i, int menor);

void selectionSort(int *v, int n){
	int i, j;
	int menor;
	for(i=0; i<n; i++){
		menor = i;
		for(j=i+1; j<=n; j++){
			if(v[j] < v[menor]){
				menor = j;
			}
		}
		if(i != menor){
			trocar(v, i, menor);
		}
	}
}

void trocar(int *v, int i, int menor){
	int aux;
	aux = v[menor];
	v[menor] = v[i];
	v[i] = aux;
	
}

int main(){
	clock_t inicio, fim;
	int vetor[10], i;

	for(i=0; i<10; i++){
		vetor[i] = rand()%100;
	}
	printf("Vetor nao ordenado\n");
	for(i=0; i<10; i++){
		printf("%d\t", vetor[i]);
	}
	printf("\nVetor ordenado\n");
	inicio = clock();
	selectionSort(vetor, 10);
	fim = clock();
	for(i=0; i<10; i++){
		printf("%d\t", vetor[i]);
	}
	printf("\nTempo para ordenacao: %lf\n", ((float)(fim-inicio)/CLOCKS_PER_SEC));

	return(0);
}
