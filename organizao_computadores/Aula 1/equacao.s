	.data
A:			.word 2
B:			.word 2
C:			.word 2
D:			.word 6
S:			.word 0
	.text
# S = (A - ((C + B) / A)) + ((D - B) / 2)
main:
	push A
	push B
	push C
	add
	div
	push A
	sub
	push 2
	push B
	push D
	sub
	div
	add
	pop S
	li $v0, 4
	la $a0, S
	syscall
	li $v0, 10
	syscall
	
	
	