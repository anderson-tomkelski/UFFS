# Exercício 1b - Arquitetura Acumulador

	.data
A:			.word 2
B:			.word 2
C:			.word 2
X:			.word 0

main:
	load r1, B      # r1 = B
	load r2, A      # r2 = A
	div r3, r1, r2  # r3 = r1/r2
	load r4, C      # r4 = C
	sub r4, r4, r3  # r4 = r4 - r3
	load r5, 7      # r5 = 7
	div r5, r5, r1  #r5 = r5/r1
	mul r5, r5, r2  #r5 = r5 * r2
	sub r4, r4, r5  #r4 = r4 - r5
	store r4, X