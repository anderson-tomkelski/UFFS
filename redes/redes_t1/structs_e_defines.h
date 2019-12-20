#define MAX_ROTEADORES 128
#define ARQUIVO_ROTEADORES "roteador.config"
#define ARQUIVO_ENLACES "enlaces.config"
#define INF 1 << 30

typedef struct {
	int porta;
	char ip[16];
} Roteador;

typedef struct {
	int qtd_enlaces[MAX_ROTEADORES];
	int enlaces[MAX_ROTEADORES][MAX_ROTEADORES];
	int pesos[MAX_ROTEADORES][MAX_ROTEADORES];
} Grafo;
