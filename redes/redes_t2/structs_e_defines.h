#define MAX_ROTEADORES 8
#define ARQUIVO_ROTEADORES "roteador.config"
#define ARQUIVO_ENLACES "enlaces.config"
#define INF 1 << 30
#define TAMANHO_PACOTE 128
#define ID_PACOTE_DADOS -1
#define ID_PACOTE_CONTROLE -2
#define GERAR_SEQUENCIA_INTERNA -1
#define NAO_GERAR_SEQUENCIA_INTERNA -2
#define MAX_DIAMETRO 100
#define EXIBIR_VETORES_DISTANCIA 0

typedef struct {
	int porta;
	char ip[16];
} Roteador;

typedef struct {
	int custo[MAX_ROTEADORES];
	int vetores[MAX_ROTEADORES][MAX_ROTEADORES];
} TabelaVetores;
