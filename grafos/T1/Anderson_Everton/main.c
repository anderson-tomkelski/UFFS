#include <stdio.h>
#include <string.h>

void buscaMinDj(int adj[5][5], int v, int dist[], int tam, int vis[]){
	int menor = 1 << 30, u = -1;
	vis[v] = 1;
	for(int i = 0; i < tam; i++){
		if(adj[v][i] < menor && adj[v][i] && !vis[i]){
			menor = adj[v][i];
			u = i;
		}
	}
	if(u == -1)
		return;
	dist[u] = dist[v] + adj[v][u];
	buscaMinDj(adj, u, dist, tam, vis);
}

void buscaMinInc(int inc[6][9], int v, int dist[], int tamv, int tama, int vis[]){
	int menor = 1 << 30, u = -1;
	vis[v-1] = 1;
	for(int i = 0; i < tama; i++){
		if(inc[0][i] < menor && inc[v][i] == 1){
			menor = inc[0][i];
			u = i;
		}
	}
	if(u == -1)
		return;
	for(int j = 1; j < tamv; j++){
		if(inc[j][u] == -1 && !vis[j-1]){
			dist[j-1] = dist[v-1] + inc[0][u];
			buscaMinInc(inc, j, dist, tamv, tama, vis);
		}
	}
}


void buscaMinDjDois(int adj[7][7], int v, int dist[], int tam, int vis[], int ultimo){
	int menor = 1 << 30, u = -1;
	vis[v] = 1;
	for(int i = 0; i < tam; i++){
		if(adj[v][i] < menor && adj[v][i] && !vis[i]){
			menor = adj[v][i];
			u = i;
		}
	}
	if(u == -1)
		return;
	dist[u] = dist[v] + adj[v][u];
	if(v == ultimo)
		return;
	buscaMinDjDois(adj, u, dist, tam, vis, ultimo);
}


void buscaMinIncDois(int inc[8][9], int v, int dist[], int tamv, int tama, int vis[], int ultimo){
	int menor = 1 << 30, u = -1;
	vis[v-1] = 1;
	for(int i = 0; i < tama; i++){
		if(inc[0][i] < menor && inc[v][i] == 1){
			menor = inc[0][i];
			u = i;
		}
	}
	if(u == -1)
		return;
	for(int j = 1; j < tamv; j++){
		if(inc[j][u] == -1 && !vis[j-1]){
			dist[j-1] = dist[v-1] + inc[0][u];
			if(v-1 == ultimo)
				return;
			buscaMinIncDois(inc, j, dist, tamv, tama, vis, ultimo);
		}
	}
}

int main() {
	//Grafo 1
	int adj1[5][5] = {{0, 30, 0, 0, 20}, {0, 0, 0, 50, 0}, {15, 10, 0, 5, 0}, {0, 50, 0, 0, 0}, {0, 0, 10, 30, 0}};
	int inc1[6][9] = {{20, 15, 30, 10, 10, 30, 5, 50, 50}, {1, -1, 1, 0, 0, 0, 0, 0, 0}, {0, 0, -1, -1, 0, 0, 0, 1, -1},
					  {0, 1, 0, 1, -1, 0, 1, 0, 0}, {0, 0, 0, 0, 0, -1, -1, -1, 1}, {-1, 0, 0, 0, 1, 1, 0, 0, 0}};
	int distAdj1[5] = {0, 0, 0, 0, 0};
	int distInc1[5] = {0, 0, 0, 0, 0};
	int vis[5] = {0, 0, 0, 0, 0};

	//Grafo2
	int adj2[7][7] = {{0, 2, 0, 6, 12, 0, 0}, {0, 0, 1, 0, 0, 5, 0}, {0, 0, 0, 0, 0, 0, 40},
					  {0, 0, 0, 0, 0, 4, 0}, {0, 0, 0, 0, 0, 0, 30}, {0, 0, 0, 0, 0, 0, 8}, {0, 0, 0, 0, 0, 0, 0}};

	int inc2[8][9] = {{2, 6, 12, 1, 5, 4, 30, 40, 8}, {1, 1, 1, 0, 0, 0, 0, 0, 0}, {-1, 0, 0, 1, 1, 0, 0, 0, 0}, {0, 0, 0, -1, 0, 0, 0, 1, 0},
					  {0, -1, 0, 0, 0, 1, 0, 0, 0}, {0, 0, -1, 0, 0, 0, 1, 0, 0}, {0, 0, 0, 0, -1, -1, 0, 0, 1}, {0, 0, 0, 0, 0, 0, -1, -1, -1}};

	int distAdj2[7] = {0, 0, 0, 0, 0, 0, 0};
	int distInc2[7] = {0, 0, 0, 0, 0, 0, 0};
	int vis2[7] = {0, 0, 0, 0, 0, 0, 0};

	buscaMinDj(adj1, 0, distAdj1, 5, vis);
	printf("Adjacencia\n");
	for(int i = 0; i < 5; i++){
		printf("Peso para chegar em %d = %d\n", i+1, distAdj1[i]);
	}

	memset(vis, 0, sizeof(vis));

	buscaMinInc(inc1, 1, distInc1, 6, 9, vis);
	printf("Incidencia\n");
	for(int i = 0; i < 5; i++){
		printf("Peso para chegar em %d = %d\n", i+1, distInc1[i]);
	}

	buscaMinDjDois(adj2, 0, distAdj2, 7, vis2, 7);
	printf("Adjacencia Grafo 2\n");
	for(int i = 0; i < 7; i++){
		printf("Peso para chegar em %d = %d\n", i+1, distAdj2[i]);
	}

	memset(vis2, 0, sizeof(vis2));

	buscaMinIncDois(inc2, 1, distInc2, 8, 9, vis2, 7);
	printf("Incidencia Grafo 2\n");
	for(int i = 0; i < 7; i++){
		printf("Peso para chegar em %d = %d\n", i+1, distInc2[i]);
	}

	return(0);

}
