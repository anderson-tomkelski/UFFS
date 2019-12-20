#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct _pecaDomino{
    	int numberRight, numberLeft;
    	struct _pecaDomino *right;
    	struct _pecaDomino *left;
}TppecaDomino;

TppecaDomino* inicializa();
TppecaDomino* embaralhar(TppecaDomino* l);
//TppecaDomino* insereIni(TppecaDomino* l, int pleft, int pright);
TppecaDomino* insereFim(TppecaDomino* l, int pleft, int pright);
TppecaDomino* excluiPeca(TppecaDomino* l, int pleft, int pright);
// Agora tem que tirar do monte e por em um lista - m = lista monte
TppecaDomino* pesca(TppecaDomino** l, TppecaDomino* m, int bleft, int bright);
void imprime(TppecaDomino* l);

TppecaDomino* inicializa(){
    	return NULL;
}

TppecaDomino* embaralhar(TppecaDomino* l){
   	 int i, j;
   	 TppecaDomino* primeiro = NULL;
  	 TppecaDomino* anterior = NULL;
	 // Esse for cria as 28 pecas
  	 for(i=0; i<=6; i++){
        	for(j=i; j<=6; j++){ 
            		TppecaDomino* novo = (TppecaDomino *) malloc(sizeof(TppecaDomino));
            		novo->numberRight = i;
            		novo->numberLeft = j;
            		novo->right = NULL;
            		if(anterior != NULL){
            	    		anterior->right = novo;
                		novo->left = anterior;
            		}
            		if(primeiro == NULL)
                		primeiro = novo;
            		anterior = novo;
        	}
    	}
	
	//agora tem que embaralhar
	TppecaDomino *goFim = NULL;
	
	for(i=0;i<50;i++){
		goFim = primeiro;
		srand((unsigned)time(NULL));

		j=rand()%25;
		while(j>0){
			goFim=goFim->right;
			j--;
		}
		primeiro = insereFim(primeiro, goFim->numberLeft, goFim->numberRight);
		primeiro = excluiPeca(primeiro, goFim->numberLeft, goFim->numberRight);
	}
    	return primeiro;
}

// Insere no inicio ou seja, na esquerda
TppecaDomino* insereIni(TppecaDomino *l, int pleft, int pright){
	TppecaDomino* novo = (TppecaDomino *) malloc(sizeof(TppecaDomino));
	if(l != NULL)
		l->left = novo;
	novo->numberRight = pright;
	novo->numberLeft = pleft;
	novo->right = l;
	novo->left = NULL;
	
	return novo;
}

// Insere no fim ou seja, na direita
TppecaDomino* insereFim(TppecaDomino* l, int pleft, int pright){
	TppecaDomino* endFim = l;
	TppecaDomino* novo = (TppecaDomino *) malloc(sizeof(TppecaDomino));
	novo->numberRight = pright;
	novo->numberLeft = pleft;

	// Como vai inserir no ultimo, o ultimo se transformara no penultimo, precisando apontar para o ultimo
	while(endFim->right != NULL){
		endFim = endFim->right;
	}
	endFim->right = novo;
	novo->right = NULL;
        novo->left = endFim;
	return l;
}

// Exclui peca, funcao que vai tirar a mao de alguma mao
TppecaDomino* excluiPeca(TppecaDomino* l, int pleft, int pright){
	TppecaDomino *prox = NULL, *nodoExc = NULL;
	TppecaDomino *address = l;
	
	// Faz uma busca ate a lista acabar ou ate encontrar a peca onde os valores combinem com os buscados
	while(address != NULL && ((pleft != address->numberLeft) || (pright != address->numberRight))){
		address = address->right;
	}
	
	// Quer dizer que nao encontrou nada
	if(address == NULL)
		return l;
	
	nodoExc = address;
	prox = address->right;
	// Quer dizer que tem que deletar o primeiro elemento
	if(address->left == NULL){
		// O segundo elemento passa a ser o primeiro
		l = address->right;
		// Se so tiver um elemento a operacao abaixo breka
		if(l != NULL)
			l->left = NULL;
	// Se for o ultimo nodo
	}else if(prox == NULL){
		address = address->left;
		address->right = NULL;
	}else{
		// Se for um nodo no meio
		address = address->left;
		prox->left = address;
		address->right = prox;
	}
	free(nodoExc);
	return l;
		
}

// Busca uma peca com os valores bleft ou bright
TppecaDomino* pesca(TppecaDomino **l, TppecaDomino *m, int bleft, int bright){
	// Lista do monte
	TppecaDomino *pack = m;
	int esq=7, dir=7;	
	// Enquanto existir pecas no monte ou enquanto nao achar a peca que encaixe ou na direita ou na esquerda, a mao recebe uma peca e o monte perde uma peca	
	while(pack != NULL && (esq != bleft && esq != bright) && (dir != bleft && dir != bleft)){
		esq = pack->numberLeft;
		dir = pack->numberRight;
		//printf("[esq]=%d, [dir]=%d\n", esq, dir);
		// Insere no inicio da mao
		*l = insereIni(*l, esq, dir);
		// Exclui no monte
		pack = excluiPeca(pack, esq, dir);
	}
	m = pack;
	return m;
}


//Esta função vai ser a tela, sendo que as ultima 15 linhas serão para a mão do jogador
char imprime_display(char disp[100][121]){
	int i, j;
	for(i=0; i<100; i++){
		for(j=0; j<121; j++){
			//disp[i][j] = ' '; // Para teste
			printf("%c", disp[i][j]);
		}
	}

}

TppecaDomino* distribui(TppecaDomino *p){
	TppecaDomino *pack=p;
	TppecaDomino *hand=NULL;
	int i=0;

	//percorre e conta quantas peças tem na lista
	while(pack != NULL){
		pack=pack->right;
		i++;
	}
	//printf("QTD ELEMENTOS [i] = %d\n", i);
	//diminui 6 unidades do total e aponta para o inicio novamente
	i=i-6;
	pack=p;
	
	//procura o ponto onde a lista será dividida
	while(i > 0){
		pack =pack->right;
		i--;
	}

	//divide a lista em duas e retorna uma lista com 6 peças

	hand = pack;
	pack = pack->left;
	hand->left=NULL;
	pack->right=NULL;
	return hand;
	
}

	//função que realiza uma jogada na mesa
	//recebe a lista do monte, da mesa, a lista da mão do jogador, o numero da esquerda e da direita da peça que será jogada
	//caso a peça deva ser invertida, essa função vai inverter os numeros de esquerda e direita e depois mover a peça para a mesa
	//caso o jogador não tenha uma peça que possa jogar, ele pode informar os numeros à esquerda e direita da mesa
	//se lado==0 então joga na esquerda se for igual a 1 então joga na direita

int procuraPeca(TppecaDomino *l, int esq, int dir){
	int i=0;
	TppecaDomino *hand = l;
	//Para procurar a peça: - Ta quase certo aqui, mas tipo, se o cara jogar 6 6 e tem a peca 6 4 ele valida por que um 6 eh igual
	while(hand != NULL && ((hand->numberLeft != esq && hand->numberRight != esq) || (hand->numberLeft != dir && hand->numberRight != dir))){
		hand=hand->right;
		i++;
	}
	
	if(hand == NULL)
		return -1;
	// Retorna a posicao da peca no nodo
	return i;
}

// A funcao retorna o que tem que fazer, e por referencia passa os valores
int jogar(TppecaDomino *m, TppecaDomino *h, int indice, int lado,  int *numLeft, int *numRight){
	TppecaDomino *table = m;
	TppecaDomino *hand=h;
	int esq, dir, i, hesq, hdir;
	// Pega as pecas da extremidade
	printf("ESQ = [%d] - DIR = [%d]\n", hand->numberLeft, hand->numberRight);
	esq=table->numberLeft;
	while(table->right != NULL){
		table=table->right;
	}
	dir=table->numberRight;

	table = m;
	
	//Pega a peca que sera jogada
	for(i=0; i<indice; i++){
		hand = hand->right;
	}
	hesq = hand->numberLeft;
	hdir = hand->numberRight;
	printf("ESQ = [%d] - DIR = [%d]\n", hand->numberLeft, hand->numberRight);

	//jogar no lado esquerdo sem inverter a peca - return 1 se nao precisa inverter a peca
	if((lado==0)&&(hand->numberRight == esq)){
		printf("ENTREI AQUI OOOOOO\n [%d] - [%d]\n", hand->numberLeft, hand->numberRight);
		*numLeft = hand->numberLeft;
		*numRight = hand->numberRight;
		return 1;
	}

	//jogar no lado direito sem inverter a peca - return 1 se nao precisa inverter a peca
	if((lado==1)&&(hand->numberLeft == dir)){
		*numLeft = hand->numberLeft;
		*numRight = hand->numberRight;
		return 1;
	}
	
	// Jogar no lado esquerdo invertendo a peça - return 0
	if((lado==0)&&(hand->numberRight != esq && hand->numberLeft == esq)){
		hand->numberRight = hesq;
		hand->numberLeft = hdir;
		*numLeft = hand->numberLeft;
		*numRight = hand->numberRight;	
		return 0;
	}
	// Jogar no lado direito invertendo a peca
	if((lado==1)&&(hand->numberLeft != dir && hand->numberRight == dir)){
		hand->numberRight = hesq;
		hand->numberLeft = hdir;
		while(table->right != NULL)
			table=table->right;
		if(hand->numberLeft==table->numberRight){
			*numLeft = hand->numberLeft;
			*numRight = hand->numberRight;
			return 0;	
		}
	}
	// Se a jogada e invalida
	return 2;
}


	
//função para determinar quem tem a peca com maior numero para acontecer a primeira jogada

int primeiraJogada(TppecaDomino *m, TppecaDomino *h, TppecaDomino *q, int *duble){
	TppecaDomino *table=m;
	TppecaDomino *hand=h;
	TppecaDomino *machine=q;
	
	
	int maiorHand=0;
	int maiorMachine=0;

	//primeiro é preciso procurar o maior dublê
	while(hand != NULL){
		if((hand->numberLeft == hand->numberRight) && (maiorHand < hand->numberRight))
			maiorHand=hand->numberRight;	
		hand=hand->right;
	}

	while(machine != NULL){
		if((machine->numberLeft == machine->numberRight) && (maiorMachine < machine->numberRight))
			maiorMachine=machine->numberRight;	
		machine=machine->right;
	}	

	//voltando ao inicio das listas
	machine=q;
	hand=h;

	//agora ele efetua a jogada

	//caso 1: o dublê está na mão do jogador
	if (maiorHand > maiorMachine){
		*duble = maiorHand;
		return 1;
	}else{ 
		//caso 2: o dublê está na mão da maquina
		*duble = maiorMachine;
		return 2;
	}

	return 0;
}


void imprime(TppecaDomino* l){
    	TppecaDomino* p = l;
    	while(p != NULL){
        	printf("%d | %d\n", p->numberLeft, p->numberRight);
        	p = p->right;
    	}
}



int jogaMaquina(TppecaDomino *mesa, TppecaDomino *maq, int *mNumLeft, int *mNumRight){
	int bleft, bright;
	TppecaDomino *table=mesa;
	TppecaDomino *machine=maq;
	int esq, dir;

	//procurando o inicio e o fim da mesa
	bleft=table->numberLeft;
	while(table->right != NULL){
		table=table->right;
	}
	bright=table->numberRight;

	table=mesa;

	while(machine != NULL && ((machine->numberLeft != bleft && machine->numberRight != bleft) && (machine->numberLeft != bright && machine->numberRight != bright))){
		machine=machine->right;
	}
	
	if(machine == NULL){
		return 2;
	}

	//se a peça precisa ser invertida
	if((machine->numberLeft != bright && machine->numberLeft == bleft) || (machine->numberRight != bleft && machine->numberRight == bright)){
		esq = machine->numberLeft;
		dir = machine->numberRight;
		machine->numberLeft = dir;
		machine->numberRight = esq;
	}

	//jogando na mesa
	//caso a peça se encaixe no inico da mesa
	if(machine->numberRight == bleft){
		*mNumLeft = machine->numberLeft;
		*mNumRight = machine->numberRight;		
		//table = insereIni(table, machine->numberLeft, machine->numberRight);
		//machine = excluiPeca(maq, machine->numberLeft, machine->numberRight);
		return 0;
	}else{
		//se não se encaixar no inicio da mesa, ele percorre até o final da lista da mesa e tenta jogar
		while(table->right != NULL)
			table=table->right;
		if(machine->numberLeft == table->numberRight){
			*mNumLeft = machine->numberLeft;
			*mNumRight = machine->numberRight;
			//table = insereFim(mesa, machine->numberLeft, machine->numberRight);
			//machine = excluiPeca(maq, machine->numberLeft, machine->numberRight);
			return 1;	
		}
	}
	return 2;
}


int checaPeca(TppecaDomino *mao, TppecaDomino *mesa){
	TppecaDomino *table = mesa;
	TppecaDomino *hand = mao;
	int esqMesa, dirMesa;

	esqMesa = table->numberLeft;
	while(table->right != NULL){
		table=table->right;
	}
	dirMesa = table->numberRight;
	// Se nenhuma peca servir
	while(hand != NULL){
		if(hand->numberRight == dirMesa || hand->numberLeft == dirMesa || hand->numberRight == esqMesa || hand->numberLeft == esqMesa)
			return 1;
		hand = hand->right;
	}
	return 0; 
}

int pegaDir(TppecaDomino *mesa){
	TppecaDomino *table = mesa;
	while(table->right != NULL){
		table=table->right;
	}
	return table->numberRight;
}

int pegaEsq(TppecaDomino *mesa){
	return mesa->numberLeft;
}












void * disp(TppecaDomino *mesa, TppecaDomino * mao, char tela[55][128]){

	//aqui é informado quantas peças a lista da mesa possui e quantas peças a lista da mão possui
	//modificando essas variaveis vc vai ver mais ou menos peças na tela
	int contadorMesa=0;
	int contadorMao=0;

	TppecaDomino *valor=mesa;
	while(valor !=NULL){
		valor=valor->right;
		contadorMesa++;
	}
		
	valor=mao;

	while(valor !=NULL){
		valor=valor->right;
		contadorMao++;
	}	

	//variáveis auxiliares para a matriz...
	int m,n;

	//primeiro deixa a matriz toda em branco
	for(m=0;m<47;m++){
		for(n=0;n<128;n++){
			tela[m][n] = ' ';
		}
	}

	//esses serão os valores das peças, futuramente será o valor que possui dentro do nodo de cada pela (numberLeft e numberRight)
	int esq=0;
	int dir=0;
	
	//variavel que faz um teste para verificar se está imprimindo ou atualizando a mão ou a mesa
	int teste=0;

	//variaveis para contar as fileiras e a peças
	int pilhas=0;
	int pecas=0;




	valor=mesa;

	//criando as peças da mesa
	while((contadorMesa>0)||((contadorMao*teste)>0)){

		esq=valor->numberLeft;
		dir=valor->numberRight;
		valor=valor->right;




		for(m=1+(6*pilhas)+(24*teste);m<6+(6*pilhas)+(24*teste);m++){
			for( n=0 ; n<128 ;n++){
				if( (m==1+(6*pilhas)+(24*teste)) || (m==5+(6*pilhas)+(24*teste) )){
					tela[m][n] = '-';
					if(n>((pecas*18)+19))
						tela[m][n]= ' ';
				}else if( (n==(19*pecas)) || (n==(19*pecas)+7) || (n==(19*pecas)+14)){
					tela[m][n] = '|';
				}
					//para pintar a bolinha da posição 1 e 6
				if((esq==3)||(esq==4)||(esq==5)||(esq==6)){
					tela[2+(6*pilhas)+(24*teste)][1+(19*pecas)]='0';
					tela[4+(6*pilhas)+(24*teste)][5+(19*pecas)]='0';	
				}
				if((dir==3)||(dir==4)||(dir==5)||(dir==6)){
					tela[2+(6*pilhas)+(24*teste)][9+(19*pecas)]='0';
					tela[4+(6*pilhas)+(24*teste)][13+(19*pecas)]='0';	
				}
					//para pintar a bolinha da posição 4 e 3
				if((esq==4)||(esq==5)||(esq==6)){
					tela[2+(6*pilhas)+(24*teste)][5+(19*pecas)]='0';
					tela[4+(6*pilhas)+(24*teste)][1+(19*pecas)]='0';
				}
				if((dir==4)||(dir==5)||(dir==6)){
					tela[2+(6*pilhas)+(24*teste)][13+(19*pecas)]='0';
					tela[4+(6*pilhas)+(24*teste)][9+(19*pecas)]='0';
				}
					//para pintar a bolinha da posição 2 e 5
				if((esq==2)||(esq==6)){
					tela[2+(6*pilhas)+(24*teste)][3+(19*pecas)]='0';
					tela[4+(6*pilhas)+(24*teste)][3+(19*pecas)]='0';
				}
				if((dir==2)||(dir==6)){
					tela[2+(6*pilhas)+(24*teste)][11+(19*pecas)]='0';
					tela[4+(6*pilhas)+(24*teste)][11+(19*pecas)]='0';
				}
					//para pintar a bolinha do meio
				if((esq==3)||(esq==1)||esq==5){
					tela[3+(6*pilhas)+(24*teste)][3+(19*pecas)]='0';
				}
				if((dir==3)||(dir==1)||dir==5){
					tela[3+(6*pilhas)+(24*teste)][11+(19*pecas)]='0';
				}
			}	
		}
		pecas++;
		if(contadorMesa>0){
			contadorMesa--;
		}
		if(pecas==6){
			pilhas++;
			pecas=0;
		}
		if(teste==1){
			contadorMao--;
		}

		if((contadorMesa==0) && (teste==0)){
			pilhas=0;
			pecas=0;
			teste=1;
			valor=mao;
		}
		
	}
	//sem esse 'for' as peças ficariam grudadas, ele apaga todas as colunas e deixa os dados separados...	
	for(m=0;m<55;m++){
		for(n=0;n<121;n++){
			if((n==16)||(n==17)||(n==18)||(n==19)||(n==35)||(n==36)||(n==37)||(n==38)||(n==54)||(n==55)||(n==56)||(n==57)||(n==73)||(n==74)||(n==75)||(n==76)||(n==92)||(n==93)||(n==94)||(n==95)||(n==111)||(n==112)||(n==113)||(n==114)){
				tela[m][n-1]= ' ';
			}
		}
	}
	//aqui é feita a divisão entre a mão e a mesa
	for(n=0;n<121;n++)
		tela[24][n] = '=';

	tela[0][30] = 'M';
	tela[0][31] = 'E';
	tela[0][32] = 'S';
	tela[0][33] = 'A';
	tela[0][34] = ':';
	tela[24][29] = ' ';
	tela[24][30] = 'M';
	tela[24][31] = 'A';
	tela[24][32] = 'O';
	tela[24][33] = ':';
	tela[24][34] = ' ';


	//aqui imprime o display
	for(m=0;m<36;m++){
		for(n=0;n<128;n++){
			printf ("%c", tela[m][n]);
		}
	printf ("\n");
	}
}

















int main(){
	// escEsq e escDir sao os valores que o usuario escolhe para jogar sua peca
	int escEsq, escDir, lado, qmJogou, indicePeca, jogada, numLeft, numRight;
	int mNumLeft=0, mNumRight=0, jogadaMaquina;
	int firstPlay, duble;
	// Aqui eh declarado o tamanho da tela
	char display[55][128];
	// O monte eh onde fica todas as pecas que serao pescadas
    	TppecaDomino* monte;
	//A mao eh a lista contendo a mao do jogador
	TppecaDomino* mao;
	// A maq eh a lista contendo a mao da maq
	TppecaDomino* maq;
	// A mesa eh a lista que vai guardar as pecas que estao na mesa
	TppecaDomino* mesa;

	// Inicializa todas as listas como null
    	monte = inicializa();
	mao = inicializa();
	maq = inicializa();
	mesa = inicializa();
	
	// Aqui eh criado as 28 pecas e entao 
    	monte = embaralhar(monte);
	//Aqui eh dado 6 peças para o jogador e 6 para a maquina
	mao = distribui(monte);
	maq = distribui(monte);
	
	//imprime(mao);
	printf("\n");	

	printf("\n\nPRIMEIRA JOGADA:\n");

	//aqui acontece a primeira jogada
	firstPlay = primeiraJogada(mesa, mao, maq, &duble);

	if(firstPlay == 1){
		mesa = insereIni(mesa, duble, duble);
		mao = excluiPeca(mao, duble, duble);
	} else if(firstPlay == 2){
		mesa = insereIni(mesa, duble, duble);
		mao = excluiPeca(mao, duble, duble);
	}
	else{
		printf("Primeira jogada nao ocorreu!!!");
		return 0;
	}
	// Inverte a ordem de inicio, caso jogador tiver maior duble;
	if(firstPlay == 1){
		if(monte != NULL && !checaPeca(maq, mesa)){
			monte = pesca(&maq, monte, pegaEsq(mesa), pegaDir(mesa));
		}else if(monte == NULL){
			if(!checaPeca(maq, mesa)){
				printf("COMPUTADOR PERDEU \n");
				return 0;
			}
		}

		jogadaMaquina = jogaMaquina(mesa, maq, &mNumLeft, &mNumRight);
		if(jogadaMaquina == 2){
			printf ("Computador nao jogou");
		} else if(jogadaMaquina == 1){
			mesa = insereFim(mesa, mNumLeft, mNumRight);
			maq = excluiPeca(maq, mNumLeft, mNumRight);
		} else if(jogadaMaquina == 0){
			mesa = insereIni(mesa, mNumLeft, mNumRight);
			maq = excluiPeca(maq, mNumLeft, mNumRight);
		}
	}
	//imprime(mesa);
	//printf ("\n\nMao:\n");
	//imprime(mao);
	//printf("\n\nMaq: \n");
	//imprime(maq);
	disp(mesa, mao, display);
	//Enquanto os dois tiverem peças
	while(mao != NULL && maq != NULL){
		// Chaca se tem peca, se nao pesca - Perde se nao tiver o que jogar e o que pescar
		if(monte != NULL && !checaPeca(mao, mesa)){
			monte = pesca(&mao, monte, pegaEsq(mesa), pegaDir(mesa));
		}else if(monte == NULL){
			if(!checaPeca(mao, mesa)){
				printf("JOGADOR PERDEU \n");
				return 0;
			}
		}
	
		do{
			// Vez da pessoa
			printf("Digite os dois valores da peca que deseja jogar - Ex: 	1 3  (E O LADO: 1 ou 0)\n");
			scanf("%d %d %d", &escEsq, &escDir, &lado);
			//Aqui acontece uma jogada normal
			indicePeca = procuraPeca(mao, escEsq, escDir);
			if(indicePeca != -1){
				jogada = jogar(mesa, mao, indicePeca, lado, &numLeft, &numRight);
				if(jogada == 2){
					printf("Jogada invalida\n");
				} else if(lado == 0){
					mesa = insereIni(mesa, numLeft, numRight);
					mao = excluiPeca(mao, numLeft, numRight);
				} else if(lado == 1){
					mesa = insereFim(mesa, numLeft, numRight);
					mao = excluiPeca(mao, numLeft, numRight);
				}
			}
		}while(jogada == 2);

		if(mao == NULL){
			disp(mesa, mao, display);
			printf("Voce ganhou !!!!!\n");
			return 0;
		}


		// Vez da maquina
		// Checa se precisa pescar, ou se ainda nao perdeu
		if(monte != NULL && !checaPeca(maq, mesa)){
			monte = pesca(&maq, monte, pegaEsq(mesa), pegaDir(mesa));
		}else if(monte == NULL){
			if(!checaPeca(maq, mesa)){
				printf("COMPUTADOR PERDEU \n");
				return 0;
			}
		}
		
		jogadaMaquina = jogaMaquina(mesa, maq, &mNumLeft, &mNumRight);
		if(jogadaMaquina == 2){
			printf ("Computador nao jogou");
		} else if(jogadaMaquina == 1){
			mesa = insereFim(mesa, mNumLeft, mNumRight);
			maq = excluiPeca(maq, mNumLeft, mNumRight);
		} else if(jogadaMaquina == 0){
			mesa = insereIni(mesa, mNumLeft, mNumRight);
			maq = excluiPeca(maq, mNumLeft, mNumRight);
		}
		
		if(maq == NULL){
			printf("Maquina venceu voce !!!\n");
			printf("PERDEDOR\n");
			printf("LOOOSEEER\n");
			printf("Voce eh tao feio que te jogaram fora e criaram a placenta\n");
			return 0;
		}
		// Chaca se tem peca, se nao pesca
		// jogar maq
		//printf("\n\nMESA:\n");
		//imprime(mesa);
		//printf ("\n\nMAO:\n");
		//imprime(mao);
		//printf ("\n\nMAQUINA:\n");
		//imprime(maq);


		//aqui eu imprimo o display.... AeeE CATIORO 
		disp(mesa, mao, display);
		
	}
		
    	return 0;
}




