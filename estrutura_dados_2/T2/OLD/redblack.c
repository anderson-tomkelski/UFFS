#include<stdio.h>
#include<stdlib.h>

#define clear() printf("\033[H\033[J")

typedef struct _nodo{
	int chave;
	int nivel;
	int cor;
	struct _nodo *esq;
	struct _nodo *dir;
	struct _nodo *pai;
} TpNodo;

typedef struct _arvore{
	TpNodo *raiz;
	TpNodo *sentinela;
	int nivelMax;
} TpArvore;

TpArvore *inicializa(){//aloca memoria para inicializar a arvore
	TpArvore *arvore=(TpArvore *)malloc(sizeof(TpArvore));
	TpNodo *sentinela=(TpNodo *)malloc(sizeof(TpNodo));
	arvore->raiz = NULL;
	arvore->nivelMax = 0;

	arvore->sentinela = sentinela;
	arvore->sentinela->chave = -1;
	arvore->sentinela->cor = 0;
	arvore->sentinela->pai = NULL;
	arvore->sentinela->esq = NULL;
	arvore->sentinela->dir = NULL;

	return arvore;
}

void imprimirMenu();
TpNodo *insereNormal(TpNodo *pai, TpNodo *sentinela ,int valor, int nivel);
void imprimeArvore(TpNodo *raiz);
TpNodo * procuraInserirElemento(TpNodo *raiz, TpNodo *sentinela, int valor);

int main(){
	TpArvore *arvore=(TpArvore*)malloc(sizeof(TpArvore));
	arvore=inicializa();

	int valor;
	int opcao=-1;
	do{
		imprimirMenu();
		scanf("%d", &opcao);
		switch(opcao){
			case 0:
				exit(0);
			case 1:
				clear();
				printf("\nDigite o valor a inserir: ");
				scanf("%d", &valor);
				if(arvore->raiz == NULL)
					arvore->raiz = insereNormal(arvore->raiz, arvore->sentinela, valor, 0);
				else
					arvore->raiz = procuraInserirElemento(arvore->raiz, arvore->sentinela, valor);
				
				//VerificaInvariantes
				break;
			case 2:
				clear();
				printf ("\nElementos da Arvore:\n");
				imprimeArvore(arvore->raiz);
				getchar();
				getchar();
				break;
			default:
				clear();
				printf("Opcao invalida\n");
		}
	}while(1);
}

void imprimirMenu(){
	printf("\nArvore RedBlack\n");
	printf("Escolha a opcao\n");
	printf("0 - Fechar o programa\n");
	printf("1 - Inserir Elemento\n");
	printf("2 - Listar Elementos da arvore\n");
	printf("\nOpção: ");
}

TpNodo *insereNormal(TpNodo *pai, TpNodo *sentinela ,int valor, int nivel){
	TpNodo *novoNodo = (TpNodo*)malloc(sizeof(TpNodo));
	novoNodo->esq = sentinela;
	novoNodo->dir = sentinela;
	novoNodo->pai = pai;
	novoNodo->chave = valor;
	novoNodo->nivel = nivel;
	novoNodo->cor = 1;
	sentinela->pai = novoNodo;

	return novoNodo;
}


TpNodo * procuraInserirElemento(TpNodo *raiz, TpNodo *sentinela, int valor){
	if(raiz == NULL)
		return raiz;
	
	if(valor > raiz->chave){
		if(raiz->dir == sentinela){
			raiz->dir = insereNormal(raiz, sentinela, valor, 0);
			//novaAlturaDaArvore(raiz->dir);
			//raiz = checaBalanceamento(raiz->dir);
		}else
			raiz = procuraInserirElemento(raiz->dir, sentinela, valor);

	}else if(valor < raiz->chave){
		if(raiz->esq == sentinela){
			raiz->esq = insereNormal(raiz, sentinela, valor, 0);
			//novaAlturaDaArvore(raiz->esq);
			//raiz = checaBalanceamento(raiz->esq);
		}else
			raiz = procuraInserirElemento(raiz->esq, sentinela, valor);
	}else{	
		printf("Parece que esse elemento já está inserido...");
	}
}




void imprimeArvore(TpNodo *raiz){
	if(raiz == NULL)
		return;
	
	imprimeArvore(raiz->esq);
	if(raiz->pai == NULL)
		printf("\nChave: %d ||  Cor: %d || Nivel: %d || PAI: %s", raiz->chave, raiz->cor, raiz->nivel, "Raiz");
	else
		printf("\nChave: %d ||  Cor: %d || Nivel: %d || PAI: %d", raiz->chave, raiz->cor, raiz->nivel, raiz->pai->chave);
	imprimeArvore(raiz->dir);
}





