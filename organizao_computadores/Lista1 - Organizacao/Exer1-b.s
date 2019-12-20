# Exercício 1b - Arquitetura Acumulador

	.data
A:			.word 2
B:			.word 2
C:			.word 2
X:			.word 0

main:
	movmw 7	 # w = 7
	div B	 # 7/B
	mult A   # ((7/B) * A)
	movwm X  # X = ((7/B)* A)
	movmw B  # w = B
	div A    # B / A
	movwm B  # B = B/A
	movmw C  # w = C
	sub B    # w = (C - (B/A))
	movmw B  # w = (C - (B/A))
	sub X    # w = (C - (B/A)) - ((7/B)* A)
	movwm X  # X = (C - (B/A)) - ((7/B)* A)