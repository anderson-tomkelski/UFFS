#include <stdio.h>
#include <stdlib.h>

#define clear() printf("\033[H\033[J");

typedef struct _nodo{
	int chave;
	int nivel;
	int cor; //0 == vermelho, 1 == preto?
	struct _nodo *esq;
	struct _nodo *dir;
	struct _nodo *pai;
} TpNodo;

typedef struct _arvore{
	TpNodo *raiz;
	TpNodo *sentinela;
} TpArvore;

TpArvore *inicializa();
TpNodo * insereNormal(TpNodo *pai, int valor,TpNodo *sent);
TpNodo * procuraInserirElemento(TpNodo *raiz, int valor, TpNodo *sent);
TpNodo * rotacaoEsquerda(TpNodo *raiz);
TpNodo * rotacaoDireita(TpNodo *raiz);
void inseriu(TpNodo *novoNodo);
void novaAltura(TpNodo *filho, TpNodo *sent);
void imprimirMenu();
void imprimeArvore(TpNodo *raiz, int nivel);
int calculaAlturaPreto(TpNodo *raiz, TpNodo *sent);


TpArvore *inicializa(){//aloca memoria para inicializar a arvore
	TpArvore *arvore=(TpArvore *)malloc(sizeof(TpArvore));
	TpNodo *sentinela=(TpNodo *)malloc(sizeof(TpNodo));

	arvore->raiz= NULL;
	arvore->sentinela = sentinela;
	arvore->sentinela->chave = -1;
	arvore->sentinela->cor = 1;
	arvore->sentinela->pai = NULL;
	arvore->sentinela->esq = NULL;
	arvore->sentinela->dir = NULL;
	return arvore;
}

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
					arvore->raiz = insereNormal(arvore->raiz, valor, arvore->sentinela);
					
				else
					arvore->raiz = procuraInserirElemento(arvore->raiz, valor, arvore->sentinela);
				break;
			case 2:
				clear();
				printf ("\nElementos da Arvore:\n");
				imprimeArvore(arvore->raiz, 0);
				getchar();
				getchar();
				break;
			default:
				clear();
				printf("Opcao invalida\n");
		}
	}while(1);
}

TpNodo * insereNormal(TpNodo *pai, int valor, TpNodo *sentinela){
	TpNodo * Novo = (TpNodo*)malloc(sizeof(TpNodo));
	Novo->chave = valor;
	Novo->nivel = 0;
	if(pai == NULL)
		Novo->cor = 1;
	else
		Novo->cor = 0;
	Novo->esq = sentinela;
	Novo->dir = sentinela;
	Novo->pai = pai;

	return Novo;
}


TpNodo * procuraInserirElemento(TpNodo *inicio, int valor, TpNodo *sentinela){
	TpNodo *raiz = inicio;
	if(valor > raiz->chave){
		if(raiz->dir == sentinela){
			raiz->dir = NULL;
			raiz->dir = insereNormal(raiz, valor, sentinela);
			inseriu(raiz->dir);
		}else
			raiz = procuraInserirElemento(raiz->dir, valor, sentinela);
			
	}else if(valor < raiz->chave){
		if(raiz->esq == sentinela){
			raiz->esq = NULL;
			raiz->esq = insereNormal(raiz, valor, sentinela);
			inseriu(raiz->esq);	
		}else
			raiz = procuraInserirElemento(raiz->esq, valor, sentinela);
	}else
		printf("Parece que esse elemento já está inserido...");

	
	while(raiz->pai != NULL)
		raiz = raiz->pai;
	return raiz;
}

void inseriu(TpNodo *novoNodo){
	if(novoNodo->pai == NULL || novoNodo->pai->pai == NULL){
		return;
	}

	TpNodo *pai = novoNodo->pai;
	TpNodo *avo = pai->pai;
	TpNodo *tio = (avo->esq == pai)? avo->dir : avo->esq;	
	//caso 1
	while(tio->cor == 0 && pai->cor == 0){
		pai->cor = 1;
		tio->cor = 1;
		if(avo->pai != NULL)
			avo->cor = 0;
		
		novoNodo = avo;
		pai = novoNodo->pai;
		if(pai == NULL)
			return;

		avo = pai->pai;
		
		if(avo == NULL)
			return;
		tio = (avo->esq == pai)? avo->dir : avo->esq;
	}

	//caso 2
	if(pai->cor == 0 && tio->cor == 1){
		if(novoNodo->chave < avo->chave){
			if(novoNodo->chave > pai->chave){
				pai = rotacaoEsquerda(pai);
				novoNodo = pai->esq;
				avo = pai->pai;
			}
			//caso 3 do caso 2
			avo->cor = 0;
			pai->cor = 1;
			avo = rotacaoDireita(avo);
		}else{
			if(novoNodo->chave < pai->chave){
				pai = rotacaoDireita(pai);
				novoNodo = pai->dir;
				avo = pai->pai;
			}
			avo->cor = 0;
			pai->cor = 1;
			avo = rotacaoEsquerda(avo);
		}
	}
}

TpNodo *  rotacaoEsquerda(TpNodo *raiz){	
	TpNodo *filho = raiz->dir;

	raiz->dir = filho->esq;	
	filho->esq->pai = raiz;
    	filho->esq = raiz;
   	filho->pai = raiz->pai;
    	
	if (raiz->pai != NULL)
        	if (raiz->pai->esq == raiz)
            		raiz->pai->esq = filho;
        	else
            		raiz->pai->dir = filho;
    	raiz->pai = filho;

	TpNodo * filhoEsq = filho->esq;
	TpNodo * filhoDir = filho->dir;

	return filho;
}

TpNodo * rotacaoDireita(TpNodo *raiz){
	TpNodo *filho = raiz->esq;

    	raiz->esq = filho->dir;
	filho->dir->pai = raiz;
	filho->dir = raiz;
    	filho->pai = raiz->pai;
    	if (raiz->pai != NULL)
        	if ( raiz->pai->esq == raiz )
            		raiz->pai->esq = filho;
        	else
            		raiz->pai->dir = filho;
    	raiz->pai = filho;

	return filho;
}

int calculaAlturaPreto(TpNodo *raiz, TpNodo *sent){
	if(raiz == sent)
		return 1;

	int altesq = 0;
	int altdir = 0;
		
	altesq = calculaAlturaPreto(raiz->esq, sent);
	altdir = calculaAlturaPreto(raiz->dir, sent);

	if(altesq>=altdir){
		if(raiz->cor == 1)
			return altesq+1;
		else 
			return altesq;
	}
	else{ 
		if(raiz->cor == 1)
			return altdir+1;
		else
			return altdir;
	}
}

void imprimirMenu(){
	printf("\nArvore RedBlack\n");
	printf("Escolha a opcao\n");
	printf("0 - Fechar o programa\n");
	printf("1 - Inserir Elemento\n");
	printf("2 - Listar Elementos da arvore\n");
	printf("\nOpção: ");
}

void imprimeArvore(TpNodo *raiz, int nivel){
	if(raiz->esq == NULL && raiz->dir == NULL)
		return;
	
	
	imprimeArvore(raiz->esq, nivel+1);
	printf("\nChave: %d || Nivel %d ", raiz->chave, nivel);
	
	if(raiz->cor == 1)
		printf ("NODO PRETO");
	else
		printf("NODO VERMELHO");

	if(raiz->pai != NULL)
		printf (" PAI = %d", raiz->pai->chave);
	else
		printf(" I'm the root");
	imprimeArvore(raiz->dir, nivel+1);
}

			
