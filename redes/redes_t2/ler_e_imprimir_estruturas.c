#include <stdio.h>
#include <string.h>
#include "structs_e_defines.h"
#include "interface.h"

extern int id_proprio;
extern Roteador roteadores[MAX_ROTEADORES];
extern TabelaVetores tab_vetores;
extern int tab_roteamento[MAX_ROTEADORES];
extern int tab_custos[MAX_ROTEADORES];

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

	int id1, id2, custo;
	int id_outro;

	memset(&tab_vetores, -1, sizeof(tab_vetores));
	while(fscanf(arquivo, "%d %d %d", &id1, &id2, &custo) != EOF){
		if(id1 != id_proprio && id2 != id_proprio){
			continue;
		}

		id_outro = id1;
		if(id1 == id_proprio){
			id_outro = id2;
		}
		
		tab_vetores.custo[id_outro] = custo;
		tab_vetores.vetores[id_outro][id_outro] = 0;
	}
	tab_vetores.custo[id_proprio] = 0;
	tab_vetores.vetores[id_proprio][id_proprio] = 0;

	fclose(arquivo);
}

void imprimir_tab_vetores(){
	imprimir(" ");
	imprimir(" == TABELA DE VETORES DE DISTÂNCIA ==");
	for(int i = 0; i < MAX_ROTEADORES; i++){
		if(tab_vetores.custo[i] != -1){
			imprimir(" = ROTEADOR %d =", i);
			for(int j = 0; j < MAX_ROTEADORES; j++){
				if(tab_vetores.vetores[i][j] != -1){
					imprimir(" -> ROTEADOR %d, CUSTO %d", j, tab_vetores.vetores[i][j]);
				}
			}
		}
	}
	imprimir(" ");
}

void imprimir_tab_roteamento(){
	imprimir(" ");
	imprimir(" == TABELA DE ROTEAMENTO ==");
	for(int i = 0; i < MAX_ROTEADORES; i++){
		if(tab_roteamento[i] != -1){
			imprimir(" ROTEADOR %d, SAÍDA %d, CUSTO %d", i, tab_roteamento[i], tab_custos[i]);
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
