	.data
A:		.word 5, 7, 9, 4, 3, 7
B: 		.word 6, 2, 8, 5, 4, 7
C:		.space 24
tab:	.asciiz "\t"
	.text
	
main:
	la $a0, A
	la $a1, B
	la $a2, C
	li $a3, 6
	jal compara
	la $a2, C
	jal imprime
	li $v0, 10
	syscall
	
imprime:
	add $t3, $zero, $zero
laco:
	ble $a3, $t3, sair
	addi $t3, $t3, 1
	lw $t0, 0($a2)
	
	move $a0, $t0
	li $v0, 1
	syscall
	
	la $a0, tab
	li $v0, 4
	syscall
	
	add $a2, $a2, 4
	b laco
	
compara:
	add $t3, $zero, $zero
loop:
	ble $a3, $t3, sair
	addi $t3, $t3, 1
	lw $t0, 0($a0)
	lw $t1, 0($a1)
	bgt $t0, $t1 maior
	beq $t0, $t1 igual
	blt $t0, $t1, menor

sair:
	jr $ra

maior:
	addi $t2, $zero, 1
	sw $t2, 0($a2)
	add $a2, $a2, 4
	add $a0, $a0, 4
	add $a1, $a1, 4
	b loop
	
igual:
	addi $t2, $zero, 0
	sw $t2, 0($a2)
	add $a2, $a2, 4
	add $a0, $a0, 4
	add $a1, $a1, 4
	b loop
	
menor:
	addi $t2, $zero, -1
	sw $t2, 0($a2)
	add $a2, $a2, 4
	add $a0, $a0, 4
	add $a1, $a1, 4
	b loop