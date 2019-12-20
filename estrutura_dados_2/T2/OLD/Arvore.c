#include<stdio.h>
#include<stdlib.h>

#define clear() printf("\033[H\033[J")

typedef struct _nodo{
	int chave;
	int altura, nivel;
	int altdireita, altesquerda;
	struct _nodo *esq;
	struct _nodo *dir;
	struct _nodo *pai;
} TpNodo;

typedef struct _arvore{
	TpNodo *raiz;
} TpArvore;

TpArvore *inicializa(){
	TpArvore *arvore = (TpArvore*)malloc(sizeof(TpArvore));
	arvore->raiz=NULL;
	return arvore;
}

void imprimirMenu();
void imprimeArvore(TpNodo *raiz);
void insereRaiz(TpNodo *nulo, int valor);
TpNodo * insereNormal(TpNodo *pai, int valor);
TpNodo * procuraInserirElemento(TpNodo *raiz, int valor);
TpNodo * checaBalanceamento(TpNodo *nodoAdicionado);
TpNodo * rotacaoDireita(TpNodo *pai);
TpNodo * rotacaoEsquerda(TpNodo *pai);
TpNodo * rotacaoEsqDoisElementos(TpNodo *raiz);
TpNodo * rotacaoDirDoisElementos(TpNodo *raiz);
TpNodo * rotacaoDuplaEsquerda(TpNodo *raiz);
TpNodo * rotacaoDuplaDireita(TpNodo *raiz);
void novaAlturaDaArvore(TpNodo *subArvore);
int calculaAltura(TpNodo *subArvore);

int main(){
	TpArvore *teste = inicializa();
	
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
				if(teste->raiz == NULL)
					teste->raiz = insereNormal(teste->raiz,valor);
				else
					teste->raiz = procuraInserirElemento(teste->raiz,valor);
				break;
			case 2:
				clear();
				printf ("\nElementos da Arvere:\n");
				imprimeArvore(teste->raiz);
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
	printf("\nArvore AVL\n");
	printf("Escolha a opcao\n");
	printf("0 - Fechar o programa\n");
	printf("1 - Inserir Elemento\n");
	printf("2 - Listar Elementos da arvore\n");
	printf("\nOpção: ");
}

TpNodo *insereNormal(TpNodo *pai, int valor){
	TpNodo *novoNodo = (TpNodo*)malloc(sizeof(TpNodo));
	novoNodo->esq = NULL;
	novoNodo->dir = NULL;
	novoNodo->pai = pai;
	novoNodo->chave = valor;
	novoNodo->altura = 0;
	novoNodo->altdireita = 0;
	novoNodo->altesquerda = 0;

	return novoNodo;
}

TpNodo * procuraInserirElemento(TpNodo *raiz, int valor){
	if(raiz == NULL)
		return raiz;
	
	if(valor > raiz->chave){
		raiz->altdireita++;
		raiz->nivel = raiz->altesquerda - raiz->altdireita;
		if(raiz->dir == NULL){
			raiz->dir = insereNormal(raiz,valor);
			novaAlturaDaArvore(raiz->dir);
			raiz = checaBalanceamento(raiz->dir);
		}else
			raiz = procuraInserirElemento(raiz->dir,valor);

	}else if(valor < raiz->chave){
		raiz->altesquerda++;
		raiz->nivel = raiz->altesquerda - raiz->altdireita;
		if(raiz->esq == NULL){
			raiz->esq = insereNormal(raiz,valor);
			novaAlturaDaArvore(raiz->esq);
			raiz = checaBalanceamento(raiz->esq);
		}else
			raiz = procuraInserirElemento(raiz->esq,valor);
	}else{	
		printf("Parece que esse elemento já está inserido...");
	}
	if(raiz->altesquerda>=raiz->altdireita)
		raiz->altura = raiz->altesquerda;
	else
		raiz->altura = raiz->altdireita;

}


TpNodo * checaBalanceamento(TpNodo *nodoAdicionado){
	TpNodo *nodoPai = nodoAdicionado->pai;
	TpNodo *nodoAvo = nodoPai->pai;

	novaAlturaDaArvore(nodoAdicionado);

	while(nodoAvo != NULL){
		if(nodoAvo->nivel < -1 && nodoPai->nivel < 0){
			nodoPai = rotacaoEsquerda(nodoAvo);
			break;
		}else if(nodoAvo->nivel > 1 && nodoPai->nivel > 0){
			nodoPai = rotacaoDireita(nodoAvo);
			break;
		}else if(nodoAvo->nivel< -1 && nodoPai->nivel > 0){
			nodoPai = rotacaoDireita(nodoPai);
			nodoAvo = rotacaoEsquerda(nodoAvo);
			break;
		}else if(nodoAvo->nivel > 1 && nodoPai->nivel < 0){
			nodoPai = rotacaoEsquerda(nodoPai);
			nodoAvo = rotacaoDireita(nodoAvo);
			break;
		}

		nodoAvo = nodoAvo->pai;
		nodoPai = nodoPai->pai;
	}
	while(nodoPai->pai != NULL)
		nodoPai = nodoPai->pai;

	return nodoPai;
}

void imprimeArvore(TpNodo *raiz){
	if(raiz == NULL)
		return;
	
	imprimeArvore(raiz->esq);
	if(raiz->pai == NULL)
		printf("\nChave: %d || Alt_ESQ: %d || Alt DIR: %d || Altura: %d || Nivel de BAL: %d || PAI: %s", raiz->chave, raiz->altesquerda, raiz->altdireita, raiz->altura, raiz->nivel, "Raiz");
	else
		printf("\nChave: %d || Alt_ESQ: %d || Alt DIR: %d || Altura: %d || Nivel de BAL: %d || PAI: %d", raiz->chave, raiz->altesquerda, raiz->altdireita, raiz->altura, raiz->nivel, raiz->pai->chave);
	imprimeArvore(raiz->dir);
}


TpNodo * rotacaoEsquerda(TpNodo *raiz){	
	TpNodo *filho = raiz->dir;
    	raiz->dir = filho->esq;

    	if ( filho->esq != NULL )
        	filho->esq->pai = raiz;
    	filho->esq = raiz;
   	filho->pai = raiz->pai;
    	if ( raiz->pai != NULL )
        	if ( raiz->pai->esq == raiz )
            		raiz->pai->esq = filho;
        	else
            		raiz->pai->dir = filho;
    	raiz->pai = filho;
	
	novaAlturaDaArvore(filho->dir);
	novaAlturaDaArvore(filho->esq);
	return filho;
}

TpNodo * rotacaoDireita(TpNodo *raiz){
	TpNodo *filho = raiz->esq;

    	raiz->esq = filho->dir;
    	if ( filho->dir != NULL )
        	filho->dir->pai = raiz;
    	filho->dir = raiz;
    	filho->pai = raiz->pai;
    	if ( raiz->pai != NULL )
        	if ( raiz->pai->esq == raiz )
            		raiz->pai->esq = filho;
        	else
            		raiz->pai->dir = filho;
    	raiz->pai = filho;

	novaAlturaDaArvore(filho->dir);
	novaAlturaDaArvore(filho->esq);
	return filho;
}

void novaAlturaDaArvore(TpNodo *filho){
	if(filho == NULL)
		return;

	filho->altdireita = calculaAltura(filho->dir);
	filho->altesquerda = calculaAltura(filho->esq);
	if(filho->altesquerda >= filho->altdireita)
		filho->altura = filho->altesquerda;
	else
		filho->altura = filho->altdireita;

	filho->nivel = filho->altesquerda - filho->altdireita;
	novaAlturaDaArvore(filho->pai);
}

int calculaAltura(TpNodo *subArvore){
	if(subArvore == NULL)
		return 0;

	int altesq;
	int altdir;

	altesq = calculaAltura(subArvore->esq);
	altdir = calculaAltura(subArvore->dir);

	if(altesq>=altdir)
		return altesq+1;
	else
		return altdir+1;
}
