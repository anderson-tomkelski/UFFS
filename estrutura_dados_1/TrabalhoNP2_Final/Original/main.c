#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "ShellMerge.c"

int main(void){
  int opMenu, tamanhoLista = 0, i;
  clock_t c2, c1; // variáveis que contam ciclos do processador
  float tempoVetor, tempoLista; // armazenam os tempos de execução dos algoritmos de ordenação
  
  lista * l = init(), *lAux = init();
  
  TpContato vet[TAMANHOVETOR], vAux[TAMANHOVETOR];
  //Inicia o primeiro elemento do vetor como nulo para saber que não foi preenchido ainda
  strcpy(vet[0].nome, "\0");

  printf("\n");
  do{

    printf("Digite uma opção:\n1) Criar Lista\n2) Criar Vetor\n3) Shell sort\n4) Merge sort\n5) Sair\n> ");
    scanf("%d", &opMenu);
    system("clear");

    if(opMenu == 1 || opMenu == 2){  //Criação de lista/vetor
      
      if(opMenu == 1){ //Criar lista
        printf("1) Criar lista\nDigite o tamanho da lista:\n");
        scanf("%d", &tamanhoLista);

        l = criaLista(l, tamanhoLista); //Cria lista com elementos vazios
        populaLista(l); //Preenche os contatos

      }else{ //Criar vetor
        printf("2) Criar vetor\n");
        populaVetor(vet, TAMANHOVETOR); //Preenche o vetor

      }

      //Imprime lista/vetor criados
      system("clear");
      imprimeVetor(vet, TAMANHOVETOR);
      printf("\n");
      imprimeLista(l);
      printf("\n");
      
    }else if(opMenu == 3 || opMenu == 4){ //Ordenação
      system("clear");
      
      copiaVetor(vAux, vet, TAMANHOVETOR); //Copia os elementos do vetor original para o secundário

      lAux = criaLista(lAux, tamanhoLista); //Cria uma lista auxiliar com elementos vazios
      copiaLista(lAux, l);  //Copia os elementos para a lista auxiliar
      
      if(opMenu == 3){ //Shell sort
        printf("3) Shell sort\n");

        //Realiza ordenação com lista
        c1 = clock(); //Tempo inicial
        shellSortLista(lAux, tamanhoLista);
        c2 = clock(); //Tempo final
        tempoLista = getTime(c1, c2);
        

        //Realiza as ordenação com o vetor
        c1 = clock(); //Tempo inicial
        shellSortVetor(vAux, TAMANHOVETOR);
        c2 = clock(); //Tempo final
        tempoVetor = getTime(c1, c2);
      }else{ //Merge sort
        printf("4) Merge sort\n");

        //Realiza ordenação com lista
        c1 = clock(); //Tempo inicial
        lAux = mergeSortLista(lAux, tamanhoLista);
        c2 = clock(); //Tempo final
        tempoLista = getTime(c1, c2);

        //Realiza as ordenação com o vetor
        c1 = clock(); //Tempo inicial
        mergeSortVetor(vAux, 0, TAMANHOVETOR);
        c2 = clock(); //Tempo final
        tempoVetor = getTime(c1, c2);
      }

      //Imprime resultado da ordenação
      imprimeVetor(vAux, TAMANHOVETOR);
      if(strlen(vAux[0].nome) > 0) //Se vetor não está vazio
        printf("Tempo: %.2f ms\n\n", tempoVetor);
      
      imprimeLista(lAux);
      if(lAux) //Se lista não está vazia
        printf("Tempo: %.2f ms\n\n", tempoLista);

    }else if(opMenu == 5){ //Sair
      printf("Sair\n");

    }else{ //Opção inválida
      printf("Opção inválida!\n");
      getchar();

    }
  }while(opMenu != 5);
  
  return 0;
}