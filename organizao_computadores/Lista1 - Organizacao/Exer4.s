	.data
vet:	.word 2, 3, 2, 5, 10
tam:	.word 5
	.text

main:
	la $a0, vet
	la $s0, tam
	lw $a1, 0($s0)
	addi $a2, $zero, 3
	jal checaValor
	
	
	move $a0, $t0 # Imprime quantidade menor
	li $v0, 1
	syscall
	move $a0, $t1 # Imprime quantidade igual
	li $v0, 1
	syscall
	move $a0, $t2 # Imprime quantidade menor
	li $v0, 1
	syscall
	li $v0,10
	syscall
	
checaValor:
	add $t3, $a0, $zero
	addi $t5, $zero, -1
loop:
	addi $t5, $t5, 1
	beq $t5, $a1, sair
	lw $t4, 0($t3)   # Carregou o vetor[i]
	
	blt $a2, $t4, menor
	beq $a2, $t4, igual
	bgt $a2, $t4, maior
sair:
	jr $ra

menor:
	addi $t0, $t0, 1   # Soma um valor menor
	add $t3, $t3, 4
	b loop

igual:
	addi $t1, $t1, 1 # Soma um valor igual
	add $t3, $t3, 4
	b loop
	
maior:
	addi $t2, $t2, 1  # Soma um valor maior
	add $t3, $t3, 4
	b loop