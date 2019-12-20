#include <stdio.h>
#include <stdlib.h>

typedef struct{
	char nome[50];
	char endereco[100];
	int matricula;
} estudante;

int main(){
	int numEst, i;
	estudante *classe;
	printf("Digite o numero de estudantes: ");
	scanf("%d", &numEst);
	getchar();
	classe = (estudante *)calloc(numEst, sizeof(estudante));
	if(classe == NULL){
		printf("Espaco insuficiente\n");
		return(0);
	}
	for(i=0; i<numEst; i++){
		printf("Digite o nome do aluno: ");
		fgets(classe->nome, 50, stdin);
		printf("Digite o endereco do aluno: ");
		fgets(classe->endereco, 100, stdin);
		printf("Digite o numero da matricula: ");
		scanf("%d", &(classe->matricula));
		getchar();
		classe++;
	}
	classe = classe-numEst;
	free(classe);
	return(0);
}
