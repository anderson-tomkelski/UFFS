#include <stdio.h>
#include <stdlib.h>

int main(){
	char ent[100];
	int count=0;
	int *vet, *memAux;
	vet = (int *)calloc(5, sizeof(int));
	do{
		printf("Digite um numero, letra para sair: ");
		fgets(ent, 100, stdin);
		if(count>=5){
			memAux = (int *)realloc(vet, 5 * sizeof(int));
			if(memAux){
				vet = memAux;
			}else{
				printf("Mem. Insuficiente\n");
				return(0);
			}
		}
		count++;
	}while(47 < *ent && *ent < 58);
	return(0);
	free(vet);
}
