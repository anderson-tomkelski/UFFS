#include <stdio.h>
#include <string.h>
#include "structs_e_defines.h"
#include "interface.h"

extern Roteador roteadores[MAX_ROTEADORES];
extern Grafo grafo;
extern int tab_roteamento[MAX_ROTEADORES];

void ler_roteadores(char *nome_arquivo){
	FILE *arquivo = fopen(nome_arquivo, "r");

	int id;
	int porta;
	char ip[16];

	for(int i = 0; i < MAX_ROTEADORES; i++){
		roteadores[i].porta = -1;
	}

	while(fscanf(arquivo, "%d %d %s", &id, &porta, ip) != EOF){
		roteadores[id].porta = porta;
		strcpy(roteadores[id].ip, ip);
	}

	fclose(arquivo);
}

void imprimir_roteadores(){
	imprimir(" ");
	imprimir(" == ROTEADORES ==");
	for(int i = 0; i < MAX_ROTEADORES; i++){
		if(roteadores[i].porta == -1) continue;
		imprimir(" (%d) %s:%d", i, roteadores[i].ip, roteadores[i].porta);
	}
	imprimir(" ");
}

void ler_enlaces(char *nome_arquivo){
	FILE *arquivo = fopen(nome_arquivo, "r");

	int id1, id2, peso;
	int qtd_enlaces;

	memset(&grafo, 0, sizeof(grafo));
	while(fscanf(arquivo, "%d %d %d", &id1, &id2, &peso) != EOF){
		// id1 -> id2
		qtd_enlaces = grafo.qtd_enlaces[id1];
		grafo.enlaces[id1][qtd_enlaces] = id2;
		grafo.pesos[id1][qtd_enlaces] = peso;
		grafo.qtd_enlaces[id1] += 1;
		// id2 -> id1
		qtd_enlaces = grafo.qtd_enlaces[id2];
		grafo.enlaces[id2][qtd_enlaces] = id1;
		grafo.pesos[id2][qtd_enlaces] = peso;
		grafo.qtd_enlaces[id2] += 1;
	}

	fclose(arquivo);
}

void imprimir_grafo(){
	char aux[256];
	int pos, pos_add;

	imprimir(" ");
	imprimir(" == GRAFO ==");
	for(int i = 0; i < MAX_ROTEADORES; i++){
		if(grafo.qtd_enlaces[i] != 0){
			sprintf(aux, " v%d -> %n", i, &pos);
			for(int j = 0; j < grafo.qtd_enlaces[i]; j++){
				sprintf(aux + pos, "{v%d}{p%d},%n", grafo.enlaces[i][j], grafo.pesos[i][j], &pos_add);
				pos += pos_add;
			}
			imprimir(aux);
		}
	}
	imprimir(" ");
}

void imprimir_tab_roteamento(){
	imprimir(" ");
	imprimir(" == TABELA DE ROTEAMENTO ==");
	for(int i = 0; i < MAX_ROTEADORES; i++){
		if(tab_roteamento[i] != -1){
			imprimir(" %d -> %d", i, tab_roteamento[i]);
		}
	}
	imprimir(" ");
}

extern int porcentagem_perda;

void imprimir_porcentagem_perda(){
	imprimir(" ");
	imprimir(" Perda de pacotes atualizada para %d%%", porcentagem_perda);
	imprimir(" ");
}
