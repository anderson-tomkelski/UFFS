		.data 
array1:	.space  12  #  declara 12 bytes para armazenamento
traco:  .asciiz "\t"
		.text 
main:           
	la  $t0, array1    #  lê o endereço base do array em $t0 
	li  $t1, 5         #  $t1 = 5   ("load immediate") 
	sw  $t1, ($t0)     #  armazena 5 no primeiro elemento do array;  
	li  $t1, 13        #   $t1 = 13 
	sw  $t1, 4($t0)    #  armazena 13 no segundo elementodo array; 
	li  $t1, -7        #   $t1 = -7 
	sw  $t1, 8($t0)    #  armazena -7 no terceiro elemento do array; 
	
	#li $v0, 1
	#lw  $a0, 8($t0)
	#syscall
	#li $v0, 4
	#la $a0, traco
	#syscall
	#li $v0, 1
	#lw  $a0, 4($t0)
	#syscall
	#li $v0, 4
	#la $a0, traco
	#syscall
	#li $v0, 1
	#lw  $a0, 0($t0)
	#syscall
	#li $v0, 10
	#syscall
	
	addi $t1,$t0, 8
mortadela:
	li $v0, 1
	lw $a0, 0($t0)
	syscall
	li $v0, 4
	la $a0, traco
	syscall
	addi $t0, $t0, 4
	ble $t0, $t1, mortadela
	li $v0, 10
	syscall