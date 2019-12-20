#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct lista {
	char letra;
	struct lista *prox;
} TpLista;

TpLista* inicializa(){
	return NULL;
}

TpLista* inserir(TpLista *l, char let){
	TpLista *p = l;
	TpLista *novo = (TpLista *)malloc(sizeof(TpLista));
	novo->letra = let;
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

TpLista* GravaIni(TpLista *l, char let){	
	TpLista *novo = (TpLista *)malloc(sizeof(TpLista));
	novo->letra = let;
	novo->prox = l;

	return novo;
}

// Retorna a lista invertida
TpLista* inverter(TpLista *l){
	// Lista invertida
	TpLista *inv;
	inv = inicializa();
	// Grava a lista
	TpLista *p = l;
	
	// Copia o elemento posicionando o ultimo lido sempre no inicio
	while(p->prox != NULL){
		inv = GravaIni(inv, p->letra); 
		p = p->prox;
	}
	return inv;
}

//Checar se eh sequencia
int ehSeq(char let1, char let2){
	switch(let1){
		case 'A':
		case 'E':
		case 'I':
		case 'O':
		case 'U':
		case 'a':
		case 'e':
		case 'i':
		case 'o':
		case 'u':
			return 0;
		break;
	}
	switch(let2){
		case 'A':
		case 'E':
		case 'I':
		case 'O':
		case 'U':
		case 'a':
		case 'e':
		case 'i':
		case 'o':
		case 'u':
			return 0;
		break;
		default:
			return 1;
	}
			
}


TpLista* inverteSeq(TpLista *l){
	TpLista *varre = l;
	TpLista *p = NULL;
	TpLista *ant = NULL;
	TpLista *temp = l;
	while(varre->prox != NULL){
		temp = l;
		ant = varre;
		p = varre->prox;
		// Checa se as letras são seq de consoantes
		if(ehSeq(ant->letra, p->letra)){
			//Caso sim troca as letras de lugar
			while(temp->prox != ant)
				temp = temp->prox;
			
			temp->prox = p;
			ant->prox = p->prox;
			p->prox = ant;
			ant = p;
			p = ant;
		}
		varre = varre->prox;
	}
	return l;
}

void imprime(TpLista *l){
	TpLista *p = l;
	while(p != NULL){
		printf("%c", p->letra);
		p = p->prox;
	}
}

int main(){
	// Cria a lista
	TpLista *l;
	l = inicializa();
	// Lê a mensagem que o usuário que descriptografar
	char frase[100];
	int i;
	printf("Digite a mensagem encriptada: ");
	fgets(frase, 100, stdin);
	frase[strlen(frase)-1] = 0;
	// Grava na lista
	for(i = 0; i<=strlen(frase); i++){
		l = inserir(l, frase[i]);
	}
	imprime(l);
	printf("\n");
	l = inverteSeq(l);
	imprime(l);
	printf("\n");
	l = inverter(l);
	printf("Mensagem original: \n");
	imprime(l);
	printf("\n");
}
