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
    //Preenche os campos do contato randomicamente
    preencheContato(&(l->contato));
    l = l->prox;
  }
}

void imprimeLista(lista * pLista) {
  //Se lista vazia
  if(!pLista)
    return;

  /*
  completar
  */

}

void copiaLista(lista * lDestino, lista * lOrigem){
  while(lOrigem){
    lDestino->contato = lOrigem->contato;
 
    lDestino = lDestino->prox;
    lOrigem = lOrigem->prox;
  }
}

void shellSortLista(lista * l, int size){
  int gap, i, change;
  lista *lAux = l, * initialGap;
  TpContato aux;
  /*
  Complete
  */
}

lista * mergeL(lista *left, lista *right, int size) {
  lista *lAux = init();
  lAux = criaLista(lAux, size);
  lista *lHead = lAux;

  int tam, i;
  
  /*
  Complete
  */
  return lHead;
}

lista * mergeSortLista(lista *l, int size) {
  //Verificadores
  if(!l) //Se lista vazia
    return l;

  if(size < 2 || !l->prox) //Se somente um elemento
    return l;
  
  //Listas auxiliares
  lista *left, *right, *aux;
  int meio, i;
  
    meio = size/2;
    
  /*
  Complete
  */
  left = mergeSortLista(left,meio);
  right = mergeSortLista(right,size-meio);
  
  aux = mergeL(left, right, i);
  return aux;
}

void imprimeVetor(TpContato * v, int size){
  //Se vetor nulo
  if(!v)
    return;

  //Se vetor vazio
  if(strlen(v[0].nome) == 0)
    return;
  
 
  /*
  completar
  */
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

  int gap, i, change;
  TpContato aux;
  
  /*
  Complete
  */
}

void mergeV(TpContato *v, int inicio, int meio, int fim){
  TpContato * aux;
  int p1, p2, tamanho, i, j;
  
  tamanho = fim-inicio+1;

  //ints que vao percorrer os vet
  p1 = inicio;
  p2 = meio+1;
  
  /*
  Complete
  */
}

void mergeSortVetor(TpContato *v, int inicio, int fim){
  int meio;

  if(inicio < fim){
    meio = (inicio+fim)/2;
    mergeSortVetor(v, inicio, meio);
    mergeSortVetor(v, meio+1, fim);
    mergeV(v, inicio, meio, fim);
  }
}