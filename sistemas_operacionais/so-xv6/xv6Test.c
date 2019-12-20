#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

int main(int argc, char *argv[]){
	int qtd_process = 0;
	int tickets_per_process[64];
  int id;

	if(argc == 1){
		printf(1, "Enter qtdProcess numTicketsP1 numTicketsP2 ...\n");
		exit();
	}

	qtd_process = atoi(argv[1]);
	printf(1, "Quantidade de processos - %d\n", qtd_process);

	for(int i = 0; i < qtd_process; i++){
    tickets_per_process[i] = atoi(argv[i+2]);
	}

  for(int i = 0; i < qtd_process; i++){
    printf(1, "Tickets per process - %d\n", tickets_per_process[i]);
    id = fork(tickets_per_process[i]);
    if(id == 0){
      for(;;);
      exit();
    }
    if(id == -1) break;
  }

  for(int i = 0; i < qtd_process; i++){
    wait();
  }
  exit();
}
