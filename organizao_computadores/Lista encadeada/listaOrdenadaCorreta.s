			.data
menu:   	.asciiz		"\n\n-  Lista Ordenada  -\n-       MENU       -
					\n1 - Incluir Elemento
					\n2 - Excluir Elemento por indice
					\n3 - Excluir Elemento por valor
					\n4 - Mostrar Lista Ordenada
					\n5 - Mostrar Mostrar Totais
					\n6 - Sair					
					\n\nopcao: "

insercoes:	.asciiz		"\nInsercoes: "
remocoes:	.asciiz		"\nRemocoes: "
txt_invalida: 	.asciiz		"OPCAO INVALIDA\n"
txt_valor: 		.asciiz		"Entre com o valor a ser inserido: "
txt_indice: 	.asciiz		"Entre com o indice do valor a ser removido: "	
txt_ind_inex:	.asciiz 	"Indice Inexistente\n"				
txt_valor_rem: 	.asciiz		"Entre com o valor a ser removido: "
txt_vazia: 		.asciiz		"Lista Vazia \n"
txt_sair: 		.asciiz		"SAIR \n"

txt_lista: 		.asciiz		"Lista: "
txt_espaco: 	.asciiz		" "
txt_posicao:		.asciiz     "Posicao Inserida: "
txt_vremovido:	.asciiz		"Valor Removido: "
txt_iremovido:	.asciiz		"Indice Removido: "
not_implement:  .asciiz		"DEVE IMPLEMENTAR \n"
		
		.text
main:   
		add $t9, $zero, $ra
		add $s0, $zero, $zero  # $s0 é o registrador apontador para o início da lista
		add $t7, $zero, $zero
		add $t8, $zero, $zero
mostra_menu:
		li	$v0, 4			
		la	$a0, menu
		syscall
le_opcao:
		li	$v0, 5			
		syscall
		add	$t0, $zero, $v0		#carrega valor lido em $t0
		li	$v0, 4	
compara_e_desvia:
		addi $t1, $zero, 1
		beq  $t0, $t1, op_insere
		addi $t1, $zero, 2
		beq  $t0, $t1, op_excluii		
		addi $t1, $zero, 3
		beq  $t0, $t1, op_excluiv		
		addi $t1, $zero, 4
		beq  $t0, $t1, op_mostra
		addi $t1, $zero, 5
		beq  $t0, $t1, mostrar_totais
		addi $t1, $zero, 6
		beq  $t0, $t1, op_sair
imprime_opcao_invalida:		
		la	$a0, txt_invalida
		syscall	
		j mostra_menu

# faz as chamadas as funções		
op_insere:
		addi $t7, $t7, 1
		la	$a0, txt_valor
		syscall		
		li	$v0, 5			
		syscall
		add	$a1, $zero, $v0		# carrega valor lido em $v1		
		add $a0, $zero, $s0		# carrega inicio da lista em $v0
		jal  insere
		add  $t0, $zero, $v0 
		
		li	$v0, 4			
		la	$a0, txt_posicao
		syscall	
		add  $a0, $zero, $t0		
		li	$v0, 1			
		syscall
		j   mostra_menu
		
op_excluii:
		addi $t8, $t8, 1
		la	$a0, txt_indice
		syscall		
		li	$v0, 5			
		syscall	
		add	$a1, $zero, $v0		# carrega valor lido em $v1		
		add $a0, $zero, $s0		# carrega inicio da lista em $v0
		jal  remove_indice
		add  $t0, $zero, $v0
		li	$v0, 4			
		la	$a0, txt_vremovido
		syscall	
		add  $a0, $zero, $t0		
		li	$v0, 1			
		syscall		
		j   mostra_menu

op_excluiv:
		addi $t8, $t8, 1
		la	$a0, txt_valor_rem
		syscall		
		li	$v0, 5			
		syscall	
		add	$a1, $zero, $v0		# carrega valor lido em $v1		
		add $a0, $zero, $s0		# carrega inicio da lista em $v0
		jal  remove_valor
		add  $t0, $zero, $v0 
		
		li	$v0, 4			
		la	$a0, txt_iremovido
		syscall	
		add  $a0, $zero, $t0		
		li	$v0, 1			
		syscall				
		j   mostra_menu

op_mostra:	
		add $a0, $zero, $s0		# carrega inicio da lista em $v0
		jal  mostra_lista
		j   mostra_menu
		
op_sair:
		la	$a0, txt_sair
		syscall
		j   mostra_menu		

		jr $t9

		
###########################################################
# Insere elemento na lista
###########################################################		
insere:
		add $t0, $zero, $a0	# copia posição do inicio da lista
		add $t1, $zero, $a1 # copia valor a ser inserido
		add $t6, $zero, $zero # inicia contador indice
		bne  $t0, $zero, insere_valor_na_memoria # caso lista não vazia
#caso lista vazia insere primeiro elemento da lista		
		li	$a0, 8 			 # quantidade de bytes de memória a ser alocado
		li	$v0, 9
		syscall		
		sw   $t1, 4($v0)     # coloca valor na memoria
		sw   $zero, 0 ($v0)  # faz ponteiro apontar para NULL
		add  $s0, $zero, $v0 # faz inicio apontar para primeiro elemento
		addi $v0, $zero, 0   # coloca 0 em $v0
		jr   $ra			 # depois de inserir o primeiro elemento retorna da chamada
# lista não é vazia
insere_valor_na_memoria:
		lw $t3, 0 ($a0)     # $t3 = ponteiro para proximo
		lw $t4, 4 ($a0)		# $t4 = valor atual

		slt $t5, $a1, $t4,   # testa se novo valor é menor que o presente neste indice
		beq $t5, $zero, prepara_proximo # não é menor, prepara para ler o proximo
novo_primeiro:
		li	$a0, 8  		 # quantidade de bytes de memória a ser alocado
		li	$v0, 9
		syscall
		add $s0, $zero, $v0  # faz inicio apontar para nova posicao alocada
		sw  $t0, 0 ($v0)	 # faz novo inicio apontar para antigo inicio
		sw  $t1, 4 ($v0)     # armazena valor no novo inicio
		addi $v0, $zero, 0   # carrega indice da posicao inserida em $v0
		jr $ra		

prepara_proximo:
		addi $t6, $t6, 1    #incrementa indice
		add $t2, $zero, $a0 # anterior = atual; $t2 = $a0
		add $a0, $zero, $t3 # atual = proximo; $a0 = $t3

		beq $t3, $zero, achou_fim	 # proximo = NULL então é o ultimo
			
		lw $t3, 0 ($a0)     # $t3 = ponteiro para proximo
		lw $t4, 4 ($a0)		# $t4 = valor atual
		
		slt $t5, $a1, $t4,   # testa se novo valor é menor que o presente neste indice
		beq $t5, $zero, prepara_proximo # não é menor, prepara para ler o proximo		
		
insere_meio:
		li	$a0, 8  		 # quantidade de bytes de memória a ser alocado
		li	$v0, 9
		syscall
		
		lw $t3, 0 ($t2)		# le próximo do anterior em $t3
		sw $t3, 0 ($v0)		# grava o ponteiro para o próximo 
		sw $t1, 4 ($v0)		# grava novo valor
		sw $v0, 0 ($t2)     # faz anterior apontar para o novo
		add $v0, $zero, $t6 # devolve indice
		jr $ra

achou_fim:
		li	$a0, 8  		# quantidade de bytes de memória a ser alocado
		li	$v0, 9
		syscall
		sw $v0, 0 ($t2)
		sw $zero, 0 ($v0)
		sw $t1, 4 ($v0)
		add $v0, $zero, $t6  # devolve indice
		jr $ra

		
###########################################################
# Remove elemeno pelo indice
###########################################################		
remove_indice:
	add $t0, $zero, $a0    # Coloca inicio da lista em $t0
	add $t1, $zero, $a1	   # Copia indice a ser excluido para $t1
	
	beq $t1, $zero, remove_zero
	
	addi $t2, $zero, 8
	mult $t1, $t2	       # Multiplica o indice por 8 para chegar no endereço do elemento a ser excluido
	mflo $t2
	
	add $t0, $t0, $t2      # t0 aponta para o valor que quero excluir - no caso, basta tirar o ponteiro anterior para ele
	lw $v0, 4($t0)
	lw $t1, 0($t0)   	   # t1 tem o endereço para o próximo elemento
	
	addi $t0, $t0, -8      # t0 aponta para o nodo anterior ao que quero excluir
	sw $t1, 0($t0)		   # Nodo pula o elemento que exclui, apontando para o proximo
	
	jr $ra
	
remove_zero:
	lw $v0, 4($a0)
	addi $s0, $a0, 8
	jr $ra
	

###########################################################
# Remove elemeno pelo valor
###########################################################		
remove_valor:
	add $t0, $zero, $a0    # Coloca inicio da lista em $t0
	add $t1, $zero, $a1	   # Copia valor a ser excluido para $t1
	
loop:
	lw $t2, 4($t0)
	lw $t3, 0($t0)
	beq $t2, $t1, exclui
	addi $t0, $t0, 8
	beq $t3, $zero, sair
	b loop

exclui:
	lw $v0, 4($t0)
	lw $t1, 0($t0)   	   # t1 tem o endereço para o próximo elemento
	
	addi $t0, $t0, -8      # t0 aponta para o nodo anterior ao que quero excluir
	sw $t1, 0($t0)		   # Nodo pula o elemento que exclui, apontando para o proximo
	b sair
	
sair:
	jr $ra
	
###########################################################
# Mostra o total de inserções e inclusões
###########################################################	

mostrar_totais:

	li $v0, 4
	la $a0, insercoes
	syscall
	
	
	li	$v0, 1			
	add	$a0, $zero $t7		#Inserções
	syscall
	
	li $v0, 4
	la $a0, remocoes
	syscall
	
	li	$v0, 1			
	add	$a0, $zero $t8		#Remoções
	syscall
	
	jr $ra

###########################################################
# Mostra a lista ordenada na tela
###########################################################
mostra_lista:
		add $t0, $zero, $a0	# copia posição do inicio da lista
		bne $t0, $zero, segue_mostra
		la	$a0, txt_vazia
		syscall
		jr  $ra
segue_mostra:
		la	$a0, txt_lista
		syscall
laco_mostra:
		lw $a0, 4 ($t0)
		li $v0, 1
		syscall
		
		la $a0, txt_espaco
		li $v0, 4
		syscall		
		
		lw $t0, 0 ($t0)
		bne $t0, $zero, laco_mostra
		jr $ra