#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define clear() printf("\033[H\033[J");

typedef struct _produto{
  int codigo;
  char nome[20];
  float preco;
} TpProduto;

void imprimeMenu();
void insereProduto();
void listaProdutos();

int main(){
  int opcao;
  do{
    imprimeMenu();
    scanf("%d", &opcao);
    clear();
    switch(opcao){
    case 0:
      exit(0);
      break;
    case 1:
      insereProduto();
      break;
    case 2:
      listaProdutos();
      break;
    default:
      printf("Opcao invalida\n");
    }
  }while(opcao != 0);
}

void imprimeMenu(){
  printf("Escolha a opcao desejada\n");
  printf("0 - Sair\n");
  printf("1 - Inserir um novo produto\n");
  printf("2 - Listar Produto\n");
}

int existeCodigo(int novoCodigo){
  FILE *arquivo = fopen("Produtos.txt", "r");
  if(!arquivo)
    return 0;
  int codigo;
  char *nome;
  float preco;
  while(fscanf(arquivo, "%d", &codigo) != EOF){
    if(codigo == novoCodigo){
      fclose(arquivo);
      return 1;
    }
    fscanf(arquivo, "%s", &nome);
    fscanf(arquivo, "%f", &preco);
  }
  fclose(arquivo);
  return 0;
}

void insereProduto(){
  TpProduto novo;
  novo.codigo = 0;
  novo.nome[0] = '\0';
  novo.preco = 0.0;
  printf("Digite o codigo do produto a ser inserido: ");
  scanf("%d", &novo.codigo);
  if(existeCodigo(novo.codigo)){
    printf("Codigo ja inserido\n");
    return;
  }
  getchar();
  printf("Digite o nome do produto: ");
  fgets(novo.nome, 20, stdin);
  novo.nome[strcspn(novo.nome, "\r\n")] = '\0';
  printf("Digite o preco do produto: ");
  scanf("%f", &novo.preco);

  FILE *arquivo = fopen("Produtos.txt", "a+");
  if(!arquivo){
    printf("Erro ao abrir o arquivo, tente novamente\n");
    return;
  }
  fprintf(arquivo, "%d ", novo.codigo);
  fprintf(arquivo, "%s ", novo.nome);
  fprintf(arquivo, "%.2f\n", novo.preco);

  fclose(arquivo);
}

void listaProdutos(){
  TpProduto temp;
  FILE *arquivo = fopen("Produtos.txt", "r");
  if(!arquivo){
    printf("Parece que nao ha nenhum registro\n");
    return;
  }

  printf("------------------------------------------------------\n");
  while(fscanf(arquivo, "%d", &temp.codigo) != EOF){
    fscanf(arquivo, "%s", temp.nome);
    fscanf(arquivo, "%f", &temp.preco);
    printf("Codigo: %d\n", temp.codigo);
    printf("Nome: %s\n", temp.nome);
    printf("Preco: %.2f\n", temp.preco);
    printf("------------------------------------------------------\n");
  }
  fclose(arquivo);
}