/* DEFINES */
#define MAX 10
#define TAMCOD 5 //Tamanho do código do contato
#define TAMFONE 8
#define TAMANHOVETOR 40
/* FIM DEFINES */

/* STRUCTS */
typedef struct _contato{
  char nome[40];
  char fone[9];
}TpContato;

typedef struct _list{
  TpContato contato;
  struct _list *ant;
  struct _list *prox;
}lista;
/* STRUCTS */

/* FUNCTIONS */
//Funções auxiliares comuns para lista/vetor

/* 
 * Preenche o contato <*pContato> com nome Fulano + código e fone aleatórios
 * de tamanhos, respectivamente TAMCOD e TAMFONE dados nos defines
 */
void preencheContato(TpContato * pContato);

/* 
 * Recebe variáveis do tipo clock_t com o tempo de inicio e fim
 * retorna tempo em ms
 */
float getTime(clock_t tempoInicio, clock_t tempoFim);

//Funções para lista

/*
 * Inicializa a lista, retorna NULL;
 */
lista * init();

/*
 * Cria uma lista <*l> de <size> elementos com contato vazio, retorna cabeça da lista
 */
lista * criaLista(lista * l, int size);

/*
 * Adiciona um elemento ao inicio da lista <*l>, retorna cabeça da lista
 */
lista * addElem(lista * l);

int tamanhoLista(lista *l);

/*
 * Preenche a struct contato da lista <*l>
 */
void populaLista(lista * l);

/*
 * Imprime a lista <*pLista>
 */
void imprimeLista(lista * pLista);

/*
 * Copia o conteúdo da lista <*lOrigem> para a lista <*lDestino>
 */
void copiaLista(lista * lDestino, lista * lOrigem);

/*
 * Aplica algoritmo Shell Sort na lista <*l> de tamanho <size>
 */
void shellSortLista(lista * l, int size);

/*
 * Aplica algoritmo Merge Sort na lista <*l> de tamanho <size>
 */


//Funções para vetor
/*
 * Imprime vetor <*v> de tamanho <size>
 */
void imprimeVetor(TpContato * v, int size);

/*
 * Preenche o vetor <*v> de tamanho <size>
 */
void populaVetor(TpContato * pContato, int size);

/*
 * Copia o conteúdo do vetor vetor <*vOrigem> para o vetor <*vDestino>, ambos de tamanho <size>
 */
void copiaVetor(TpContato * vDestino, TpContato * vOrigem, int size);

/*
 * Aplica algoritmo Shell Sort no vetor <*v> de tamanho <size>
 */
void shellSortVetor(TpContato * vContatos, int size);
