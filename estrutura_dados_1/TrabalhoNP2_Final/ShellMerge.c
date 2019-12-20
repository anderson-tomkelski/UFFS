#include "ShellMerge.h"

/*--------------------------------------------*/
/* Funções auxiliares comuns para lista/vetor */
/*--------------------------------------------*/
void preencheContato(TpContato * pContato){
  	int i;
  	char cod[TAMCOD+1], tel[TAMFONE+1];
  
  	if(!pContato)
    		return;

  	//Gera fone e código do contato aleatorios
  	if(TAMCOD > TAMFONE){ //Se tamanho do código definido como maior
    		for(i=0;i<TAMCOD;i++){
      			if(i<TAMFONE)
        			tel[i] = (rand() % 10) + 48;
      			cod[i] = (rand() % 10) + 48;
    		}
  	}else{ //Se tamanho do telefone definido como maior
    		for(i=0;i<TAMFONE;i++){
      			if(i<TAMCOD)
        			cod[i] = (rand() % 10) + 48;
      			tel[i] = (rand() % 10) + 48;
    		}
  	}
  	//Atribui nome ao contato
  	cod[TAMCOD] = '\0';
  	strcpy(pContato->nome,"Fulano ");
  	strcat(pContato->nome, cod);

  	//Atribui telefone
  	tel[TAMFONE] = '\0';
  	strcpy(pContato->fone,tel);
}

float getTime(clock_t tempoInicio, clock_t tempoFim){
  	return (tempoFim - tempoInicio)*1000/CLOCKS_PER_SEC;
}

/*--------------------------------------------*/
/*           Funções para lista               */
/*--------------------------------------------*/
lista * init(){
  	return NULL;
}

lista * criaLista(lista * l, int size){
  	int i;
  	//Se a lista já está criada, limpa os registros
  	if(l){
    		lista * aux, * next;
    		aux = l->prox;
    		while(aux){
      			next = aux->prox;
      			free(aux);
      			aux = next;
    		}
    		l = init();
  	}
  	//Adiciona os elementos de acordo com o tamanho da lista
  	for(i=0; i<size; i++){
    		l = addElem(l);
  	}
  	return l;
}

//add elemento inicio
lista * addElem(lista * l){
  	int i;
  
  	lista * novo = (lista *)malloc(sizeof(lista));

  	if(!novo) //Se falha na alocação
    		return NULL;
  
  	novo->prox = l;
  	novo->ant = NULL;
  
  	if(l) 
    		l->ant = novo;
  
  	return novo;
}

int tamanhoLista(lista *l){
  	int tam = 0;

  	while(l){
    		tam++;
    		l = l->prox;
  	}
  	return tam;
}

void populaLista(lista * l){
	while(l){
    		preencheContato(&(l->contato));
    		l = l->prox;
  	}
}

void imprimeLista(lista * pLista) {
	//Se lista vazia
	if(!pLista)
    		return;
	
	printf("Lista: \n\n");
	printf("--------------------\n");
  	do{
		printf("Nome: %s\n", pLista->contato.nome);
		printf("Fone: %s\n", pLista->contato.fone);
		printf("--------------------\n");
		pLista = pLista->prox;
	}while(pLista != NULL);
}

void copiaLista(lista * lDestino, lista * lOrigem){
  	while(lOrigem){
    		lDestino->contato = lOrigem->contato;
    		lDestino = lDestino->prox;
    		lOrigem = lOrigem->prox;
  	}
}

lista * nextValue(lista * l, int vezes){
	int i;
	for(i=0; i<vezes; i++){
		l = l->prox;
	}
	return l;
}

lista *divideLista(lista* l, int n){
	lista*aux=l;
	lista*nova=NULL;
	while(n>1){
		aux=aux->prox;
		n--;
	}
	nova=aux->prox;
	nova->ant = NULL;
	aux->prox=NULL;
	
	return nova;
}

void shellSortLista(lista * l, int size){
	int gap, i, change, j;
	lista *lAux = l, * initialGap;
	TpContato aux;
	
	gap = 1;
	while(gap < size){
		gap = 3*gap+1;
	}
	while(gap > 1){
		gap /= 3;
		for(i = gap; i < size; i++){
			lAux = l;
			lAux = nextValue(lAux, i);
			aux = lAux->contato;
			j = i - gap;
			lAux = l;
			lAux = nextValue(lAux, j);
			change = strcmp(aux.nome, lAux->contato.nome);
			while(j >= 0 && change < 0){
				initialGap = l;
				lAux = l;
				lAux = nextValue(lAux, j+gap);
				initialGap = nextValue(initialGap, j);
				lAux->contato = initialGap->contato;
				j -= gap;
				initialGap = l;
				initialGap = nextValue(initialGap, j);
				change = strcmp(aux.nome, initialGap->contato.nome);
			}
			lAux = l;
			lAux = nextValue(lAux, j+gap);
			lAux->contato = aux;
		}
	}
}

lista * mergeSortLista(lista *l, int size) {
	if(!l) 				
    		return l;
  	if(size < 2 || !l->prox)
    		return l;

  	lista *left, *right,*leftElement, *rightElement;
	TpContato aux1, aux2;

  	int meio = size/2;
	right = divideLista(l, meio); 	
	left = l;	
	rightElement = right;		
	leftElement = left;
	
	while(rightElement->prox != NULL){
		printf("--------RIGHT - NOME = %s\n", rightElement->contato.nome);
		rightElement = rightElement->prox;
	}

	while(leftElement->prox != NULL){
		printf("--------LEFT - NOME = %s\n", leftElement->contato.nome);
		leftElement = leftElement->prox;
	}	
	
  	left = mergeSortLista(left,meio);
  	right = mergeSortLista(right,size-meio);

  	lista *lAux = init();
  	lAux = criaLista(lAux, size);

  	lista *lHead = lAux;

  	int i=0;
	int j=meio;

  	while(i<=meio || j<=size){
		if(i==meio+1){
			printf("Entrei no IF da vadia1\n");
			rightElement = right;
			rightElement = nextValue(rightElement, j);
			printf("Entrei aqui vadia1 - j = [%d]\n", j);
			lAux->contato = rightElement->contato;

			lAux = lAux->prox;
			j++;
		}else if(j==size+1){
			printf("Entrei no IF da vadia2\n");
			leftElement = left;
			leftElement = nextValue(leftElement, i);
			printf("Entrei aqui vadia2 - i = [%d]\n", i);
			lAux->contato = leftElement->contato;

			lAux = lAux->prox;
			i++;
		}else{ 
			printf("Entrei no ELSE da vadia\n");
			leftElement = left;
			leftElement = nextValue(leftElement, i);
			rightElement = right;
			rightElement = nextValue(rightElement, j);
			
			printf("Entrei aqui vadia2 - i = [%d]\n", i);
			printf("Entrei aqui vadia2 - j = [%d]\n", i);
			aux1 = leftElement->contato;
			aux2 = rightElement->contato;

			if(strcmp(aux1.nome,aux2.nome) < 0){
				lAux->contato = aux1;
				i++;
				lAux = lAux->prox;
			}else{
				lAux->contato = aux2;
				j++;
				lAux = lAux->prox;
			}
		}
	}	
  	return lHead;
}

void imprimeVetor(TpContato * v, int size){
	int i;	
	//Se vetor nulo
	if(!v)
		return;

	//Se vetor vazio
	if(strlen(v[0].nome) == 0)
		return;
	
	printf("Vetor:\n\n");
	printf("--------------------\n");
	for(i=0; i<size; i++){
		printf("Nome: %s\n", v[i].nome);
		printf("Fone: %s\n", v[i].fone);
		printf("--------------------\n\n");
	}
		
}

void populaVetor(TpContato * pContato, int size){
  	int i;
  	if(!pContato)
    		return;
  	for(i=0;i<size;i++){
    		preencheContato(&pContato[i]);
  	}
}

void copiaVetor(TpContato * vDestino, TpContato * vOrigem, int size){
  	int i;

  	for(i=0; i<size; i++){
    		vDestino[i] = vOrigem[i];
  	}
}

void shellSortVetor(TpContato * vContatos, int size){
	if(!vContatos)
		return;

	int gap, i, j, change;
	TpContato aux;
	
	gap = 1;
	while(gap < size){
		gap = 3*gap+1;
	}
	while(gap > 1){
		gap /= 3;
		for(i = gap; i<size; i++){
			aux = vContatos[i];
			j = i - gap;
			change = strcmp(aux.nome, vContatos[j].nome);
			while(j >= 0 && change < 0){
				vContatos[j + gap] = vContatos[j];
				j -= gap;
				change = strcmp(aux.nome, vContatos[j].nome);
			}
			vContatos[j + gap] = aux;
		}
  	}	 
}

void mergeSortVetor(TpContato *vetor, int posicaoInicio, int posicaoFim){
     	int i, j, k, metadeTamanho,change;
	TpContato * vetorTemp;
    	if(posicaoInicio == posicaoFim) 
		return;

    	// ordenacao recursiva das duas metades
   	metadeTamanho = (posicaoInicio + posicaoFim ) / 2;
    	
	mergeSortVetor(vetor, posicaoInicio, metadeTamanho);
    	mergeSortVetor(vetor, metadeTamanho + 1, posicaoFim);

    	// intercalacao no vetor temporario
    	i = posicaoInicio;
    	j = metadeTamanho+1;
    	k = 0;

	vetorTemp = (TpContato *) malloc(sizeof(TpContato) * (posicaoFim - posicaoInicio+1));
	
	while(i<=metadeTamanho || j<=posicaoFim){	// Enquanto não chegar no final das duas partes...
		if(i==metadeTamanho+1){			//se já chegou no final da primeira parte (referente ao "i"), então ele copia o j;
			vetorTemp[k] = vetor[j];
			j++;
		}else if (j==posicaoFim+1){		//se já chegou no final da segunda parte (referente ao "j"), então ele copia o i;
			vetorTemp[k]= vetor[i];
			i++;
		}else if(strcmp(vetor[i].nome,vetor[j].nome)<0){	//se não chegou no final, ele compara o "i" e o "j" e depois copia
			vetorTemp[k]= vetor[i];
			i++;
		}else{
			vetorTemp[k]= vetor[j];
			j++;
		}
		k++;
	}
    	// copia vetor intercalado para o vetor original
    	for(i = posicaoInicio; i <= posicaoFim; i++){
        	vetor[i] = vetorTemp[i - posicaoInicio];
   	}
    	free(vetorTemp);
}
