#include <stdio.h>
#include <stdlib.h>

int main(){
	int tam, i;
	int *vet;
	printf("Digite o tamanho do vetor: ");
	scanf("%d", &tam);
	vet = (int *)calloc(tam, sizeof(int));
	if(vet == NULL){
		printf("Espaco insuficiente\n");
		return(0);
	}
	for(i=0; i<tam; i++){
		printf("Indice [%d]: ", i);
		scanf("%d", vet);
		vet++;
	}
	for(i=0; i<tam; i++){
		vet--;
		printf("Indice [%d]\n", tam-i);
		printf("%d\n", *vet);
	}
	free(vet);
	return(0);
}
