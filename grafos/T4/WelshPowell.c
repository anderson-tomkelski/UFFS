#include <stdio.h>

typedef struct listVertex {
	int vertex, degree, color, painted;
} list;

void sort(list dList[11]){
	int max, swapV, swapD, pos;
	for(int i = 0; i < 11; i++){
		max = dList[i].degree;
		for(int j = i; j < 11; j++){
			if(dList[j].degree > max){
				max = dList[j].degree;
				pos = j;
			}
		}
		swapV = dList[pos].vertex;
		swapD = dList[pos].degree;
		dList[pos].vertex = dList[i].vertex;
		dList[pos].degree = dList[i].degree;
		dList[i].vertex = swapV;
		dList[i].degree = swapD;
	}
}

void searchPaint(list dList[11], int name, int quantityColors){
	for(int i = 0; i < 11; i++){
		if(dList[i].vertex == name){
			dList[i].color = quantityColors;
			dList[i].painted = -1;
		}
	}
}

int isPainted(list dList[11], int name){
	for(int i = 0; i < 11; i++){
		if(dList[i].vertex == name)
			return dList[i].painted;
	}
}

int main(){
	int quantityColors = 1;
	int graph[11][11] = {{0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0},
									     {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
									     {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
									     {0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1},
									     {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
									     {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
									     {0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1},
									     {1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1},
									     {0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0},
									     {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1},
									     {0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0}};
	list degreeList[11];

	for(int i = 0; i < 11; i++){
		degreeList[i].vertex = i;
		degreeList[i].degree = 0;
		for(int j = 0; j < 11; j++){
			degreeList[i].degree += graph[i][j];
		}
	}

	sort(degreeList);

	printf("---------------------------------------------------------------------------\n");
	printf("Coloracao\n");

	for(int i = 0; i < 11; i++){
		if(degreeList[i].painted == -1)
			continue;

		degreeList[i].color = quantityColors;
		degreeList[i].painted = -1;
		for(int j = 0; j < 11; j++){
			if(graph[degreeList[i].vertex][j] == 0 && (isPainted(degreeList, j) != -1)){
				searchPaint(degreeList, j, quantityColors);
			}
		}
		quantityColors += 1;
	}

	for(int i = 0; i < 11; i++){
		printf("Vertice: %c\n Grau: %d\n Cor: %d\n", 65+degreeList[i].vertex, degreeList[i].degree, degreeList[i].color);
	}
	printf("---------------------------------------------------------------------------\n");

	return 0;
}
