		.data  
a:		.word 36, 20, 27, 15, 1, 62, 41 
n:		.word 7 
maxPrint:	.asciiz "MAIOR: " 
		.text 

main: 
	ori $8, $0, 0
	ori $16, $0, 0
    lui $18, 4097 
	lw $17, 28($18)
m1: slt $18, $8, $17 
    beq $18, $0, m3 
    ori $18, $0, 4 
	mul $9, $8, $18 
	lui $18, 4097 
    add $18, $18, $9   
    lw $10, 0($18)     
    slt $18, $16, $10  
	beq $18, $0, m2
	add $16, $0, $10
m2:
	addi $8, $8, 1 
	j m1                     
	
m3:	
	li $v0, 4
	la $a0, maxPrint
	syscall
	li $v0, 1
	move $a0, $16
	syscall
	li $v0, 10
	syscall

# O código imprime o maior valor do vetor