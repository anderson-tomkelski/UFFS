#include <stdio.h>
#define max 1 << 30

void prim(int adj2[8][8], int matPrim[3][8]){
	int small = max;
	int smallPos = 0;
	int qtdZero = 0;
	int currentCost = 0;

	for(int i = 0; i < 8; i++){
		if(matPrim[0][i] < small && matPrim[2][i] == 0){
			small = matPrim[0][i];
			smallPos = i;
		}
	}

	for(int i = 0; i < 8; i++){
		if(adj2[smallPos][i] > 0){
			currentCost = adj2[smallPos][i];
			if(currentCost < matPrim[0][i] && matPrim[2][i] == 0){
				matPrim[0][i] = currentCost;
				matPrim[1][i] = smallPos;
			}
		}
	}
  	matPrim[2][smallPos] = 1;
	
	for(int i = 1; i < 8; i++){
		if(matPrim[2][i] == 0)
			qtdZero++;
	}

	if(qtdZero)
		prim(adj2, matPrim);
}

void printPrim(int matPrim[3][8]){
	int total = 0;

	printf("\n\n.::Algoritmo de Prim::.\n\n");
	printf("Vértice:\tV0\tV1\tV2\tV3\tV4\tV5\tV6\tV7\n");

	for(int i = 0; i < 2; i++){
		switch(i) {
			case 0:
				printf("Distancia:\t");
				break;
			case 1:
				printf("V. Anterior:\t");
				break;
		}
		for(int j = 0; j < 8; j++){
			if(i==1)
				printf("V%d\t", matPrim[i][j]);
			else
				printf("%d\t", matPrim[i][j]);
		}
		printf("\n");
	}

	printf("\nArvore Geradora Minima: ");
	for(int j = 1; j < 8; j++){
		printf("(V%d,V%d)", j, matPrim[1][j]);
		total+= matPrim[0][j];
	}

	printf("\nTotal: %d\n\n", total);

	
}

void criaMatKruskal(int adj[8][8], int matKruskal[4][11]){
	int i,j=0;
	int vertice, pai = 0;
	int peso = max;
	int indiceKruskal = 0;

	while(indiceKruskal < 11){
		for(i=0; i<8; i++){
			for(j=i+1; j<8; j++){
				if(adj[i][j] > 0 && adj[i][j] < peso){
					peso = adj[i][j];
					vertice = i;
					pai = j;
				}
			}
		}
		matKruskal[0][indiceKruskal] = peso;
		matKruskal[1][indiceKruskal] = vertice;
		matKruskal[2][indiceKruskal] = pai;
		adj[vertice][pai] = 0;
		adj[pai][vertice] = 0;
		peso = max;
		indiceKruskal++;
	}
}

void kruskal(int matKruskal[4][11], int vetPais[8]){
	int indiceKruskal = 0;
	int vertices = 0;

	while(vertices < 7){ //condição de parada: numero de vértices-1
		if(vetPais[matKruskal[1][indiceKruskal]] != vetPais[matKruskal[2][indiceKruskal]]){
			vetPais[matKruskal[1][indiceKruskal]] = vetPais[matKruskal[2][indiceKruskal]];
			matKruskal[3][indiceKruskal] = matKruskal[0][indiceKruskal];
			vertices++;
		}
		indiceKruskal++;
	}
}


void printKruskal(int matKruskal[4][11]){
	int somatorio = 0;
	printf("\n.::Algoritmo de Kruskel::.\n\nAresta:");
	for(int j=0; j < 11; j++){
		printf("\tA%d", j);
	}
	for(int i=0; i<3; i++){
		switch(i){
			case 0:
				printf("\nPeso:");
				break;
			case 1:
				printf("Vert.I:");
				break;
			case 2:
				printf("Vert.J:");
				break;
		}
		for(int j=0; j<11; j++){
			printf("\t%d", matKruskal[i][j]);
			if(i==0){
				somatorio+=matKruskal[3][j];
			}
		}
		printf("\n");
	}

	printf("\nArvore Geradora Minima: ");
	for(int j=0; j<11; j++){
		if(matKruskal[3][j] > 0){
			printf("(%d,%d)", matKruskal[1][j], matKruskal[2][j]);
		}
	
	}
	printf("\nTotal: %d\n", somatorio);

}

int main(){
		  	//0 1 2 3 4 5 6 7
	int adj[8][8] = {{0,3,4,3,0,0,0,0},//0
		   	{3,0,0,0,0,0,0,0}, //1
		   	{4,0,0,0,8,8,0,0}, //2
		   	{3,0,0,0,0,8,0,0}, //3
		   	{0,0,8,0,0,0,7,7}, //4
		   	{0,0,8,8,0,0,4,7}, //5
		   	{0,0,0,0,7,4,0,2}, //6
		   	{0,0,0,0,7,7,2,0}};//7                                        

		   	 //0 1 2 3 4 5 6 7
	int adj2[8][8] = {{0,2,0,6,5,0,0,0},//0
		    	 {2,0,7,7,0,0,0,0}, //1
		    	 {0,7,0,0,6,2,0,0}, //2
		   	 {6,7,0,0,0,0,0,0}, //3
		   	 {5,0,6,0,0,0,4,5}, //4
		   	 {0,0,2,0,0,0,4,6}, //5
		    	 {0,0,0,0,4,4,0,1}, //6
		   	 {0,0,0,0,5,6,1,0}};//7 
	      
	int matKruskal[4][11] = {{0,0,0,0,0,0,0,0,0,0,0},//Peso das arestas
		           	{0,0,0,0,0,0,0,0,0,0,0}, // Vértice I
			   	{0,0,0,0,0,0,0,0,0,0,0}, // Vértice J
			   	{0,0,0,0,0,0,0,0,0,0,0}};// Quando > 0 significa o valor da aresta que está na arvore geradora mínima

	int vetPais[8] = {0,1,2,3,4,5,6,7};

		    	   //v0  V1  V2   V3   V4   V5   V6   V7
	int matPrim[3][8]= {{0, max, max, max, max, max, max, max},// Distance
		      	   {0,-1, -1, -1, -1, -1, -1, -1},  	   // Previous V
		   	   {1, 0,  0,  0,  0,  0,  0,  0}}; 	   // Visited?

	criaMatKruskal(adj, matKruskal);
	kruskal(matKruskal, vetPais);
	printKruskal(matKruskal);

	prim(adj2, matPrim);
	printPrim(matPrim);

	return 0;
}
