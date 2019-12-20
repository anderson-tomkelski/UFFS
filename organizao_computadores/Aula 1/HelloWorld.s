	.data
Hello:		.asciiz "HELLO WORLD!"
	.text

main:
	li $v0, 4 # li = Load Imediate
	la $a0, Hello #imprime - la = Load Address
	syscall
	li $v0, 10 # faz $v0 = 10 (chamada de sistema exit)
	syscall