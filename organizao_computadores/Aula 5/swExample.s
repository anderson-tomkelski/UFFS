		.data
var1:	.word 23, 67   #Declara var1; inicializa com 23
traco:  .asciiz "-"

		.text
main:
		lw $t0, var1	# Le conteudo da RAM em $t0: $t0 = (var1)
		li $t1, 5		# $t1 = 5 ("Load Immediate")
		sw $t1, var1    # Armazena $t1 na RAM: (var1) = $t1
		li $v0, 1
		lw $a0, var1
		syscall
		li $v0, 4
		la $a0, traco
		syscall
		la $t2, var1
		lw $t1, 4($t2)
		li $v0, 1
		move $a0, $t1
		syscall
		li $v0, 10
		syscall