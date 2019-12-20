		.data

txt_tamanho:		.asciiz		"\nEntre com o tamanho do vetor: "
txt_entrada:		.asciiz		"\nEntre com o elemento de indice "
txt_2pontos: 		.asciiz		": "
txt_maior:			.asciiz		"\nMaior valor: "
txt_menor:			.asciiz		"\nIndice do menor valor: "
vetor: 				.space		400   # tamanho máximo 100 inteiros

		.text
main:
		add $s2, $zero, $ra		# salva endereço de retorno
		li	$v0, 4			
		la	$a0, txt_tamanho
		syscall					#Imprime string
		
		li	$v0, 5			
		syscall					#Le tamanho do vetor
		add	$s1, $zero, $v0		#e copia em $s1
		add	$a1, $zero, $v0		# e também em $a1
		
		la  $t0, vetor
		
		add $t1, $zero, $zero	#Inicializa variavel de controle (contador) do laco $t1
laco:   slt $t2, $t1, $s1		# Se contador < quantidade entra no corpo do laço
		beq $t2, $zero, fim_leitura # senão pula para fim
		
		li	$v0, 4				
		la	$a0, txt_entrada
		syscall					#Imprime string

		li	$v0, 1
		add	$a0, $zero, $t1
		syscall					#Imprime indice
		
		li	$v0, 4
		la	$a0, txt_2pontos
		syscall					#Imprime ":"
		
		li	$v0, 5			
		syscall					#Le elemento do vetor
		
		sw  $v0, 0 ($t0)		#Le armazena na memória em vetor[i]

		addi $t0, $t0, 4		#aponta para a proxima posição do vetor
		addi $t1, $t1, 1		#atualiza variável de controle
		j laco					# volta para testar novamente
		
fim_leitura:
		la  $a0, vetor			#coloca endereço de vetor[0] em $a0; tamanho já está em $a1
		jal maior_menor			# tirar o comentário para fazer a chamada da função
		
		add $s0, $zero, $v0		# copia resultados para $s0 e $s1
		add $s1, $zero, $v1

		li	$v0, 4				#imprime texto 
		la	$a0, txt_maior
		syscall

		li	$v0, 1				#imprime maior valor
		move	$a0, $s0
		syscall
		
		li	$v0, 4				#imprime texto 
		la	$a0, txt_menor
		syscall

		li	$v0, 1				#mostra indice do menor valor
		move	$a0, $s1
		syscall

		jr  $s2					#retorna para quem chamou a função main

maior_menor:
	add $t3, $zero, $zero		#$a1 tamanho do vetor
	add $t4, $zero, $zero
	addi $t5, $zero, 9999
	addi $t7, $zero, -1
loop:
	bge $t3, $a1, retorna
	lw $t6, 0($a0)
	addi $t7, $t7, 1
	addi $t3, $t3, 1
	bgt $t6, $t4, pegaMaior
	blt $t6, $t5, pegaMenor
	
pegaMaior:
	add $v0, $zero, $t6
	addi $a0, $a0, 4
	b loop
	
pegaMenor:
	add $v1, $zero, $t7
	addi $a0, $a0, 4
	b loop
	
retorna:
	jr $ra