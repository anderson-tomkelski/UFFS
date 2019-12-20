# Exercício 1 - Arquitetura Pilha

	.data
A:			.word 2
B:			.word 2
C:			.word 2
X:			.word 0

main:
	push A  # Coloca A na pilha
	push B  # Coloca B na pilha
	push 7  # Coloca 7 na pilha
	div		# 7/B
	mult	# (7/B) * A
	push A  # Coloca A na pilha
	push B  # Coloca B na pilha
	div		# (B/A)
	push C	# Coloca C na pilha
	sub		# (C - (B/A))
	sub		# (C - (B/A)) - ((7/B) * A)
	pop X   # Coloca o resultado da equação em X