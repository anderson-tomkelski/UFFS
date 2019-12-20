#include "structs_e_defines.h"

extern Grafo grafo;
extern int tab_roteamento[MAX_ROTEADORES];

int todos_visitados(int visitados[MAX_ROTEADORES]){
	for(int i = 0; i < MAX_ROTEADORES; i++){
		if(grafo.qtd_enlaces[i] != 0 && visitados[i] == 0){
			return 0;
		}
	}
	return 1;
}

int proximo_vertice(int distancias[MAX_ROTEADORES], int visitados[MAX_ROTEADORES]){
	int menor_distancia = INF;
	int proximo = -1;

	for(int i = 0; i < MAX_ROTEADORES; i++){
		if(!visitados[i] && distancias[i] < menor_distancia){
			menor_distancia = distancias[i];
			proximo = i;
		}
	}

	return proximo;
}

void dijkstra(int origem, int anteriores[MAX_ROTEADORES]){
	int distancias[MAX_ROTEADORES], visitados[MAX_ROTEADORES];

	for(int i = 0; i < MAX_ROTEADORES; i++){
		anteriores[i] = -1;
		distancias[i] = INF;
		visitados[i] = 0;
	}

	distancias[origem] = 0;
	anteriores[origem] = -1;

	while(!todos_visitados(visitados)){
		int u = proximo_vertice(distancias, visitados);
		visitados[u] = 1;
		for(int i = 0; i < grafo.qtd_enlaces[u]; i++){
			int v = grafo.enlaces[u][i];
			int distancia_v = grafo.pesos[u][i];
			if(distancias[v] > distancias[u] + distancia_v){
				distancias[v] = distancias[u] + distancia_v;
				anteriores[v] = u;
			}
		}
	}
}

void preencher_tab_roteamento(int id_proprio){
	int anteriores[MAX_ROTEADORES];

	dijkstra(id_proprio, anteriores);

	int anterior;
	for(int i = 0; i < MAX_ROTEADORES; i++){
		if(grafo.qtd_enlaces[i] != 0 && i != id_proprio){
			for(anterior = i; anteriores[anterior] != id_proprio; anterior = anteriores[anterior]);
			tab_roteamento[i] = anterior;
		} else {
			tab_roteamento[i] = -1;
		}
	}
}
