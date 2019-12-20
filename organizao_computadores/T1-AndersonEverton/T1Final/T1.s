	.data
descritor:	.space 12
theBucket:	.space 80
printMenu:	.asciiz "\n1 - Inserir elemento na lista\n2 - Atualização/Remoção\n3 - Ordenacao com radix sort\n4 - Imprimir lista\n5 - Sair\nOpcao: "
pedeValor:	.asciiz "\nDigite um valor: "
oqueFazer:	.asciiz "\nDeseja alterar ou remover o valor? [0] Altera / [1] Exclui: "
novoValor:	.asciiz "\nDigite um novo valor: "
pedeIndex:	.asciiz "\nDigite o indice do elemento: "
msg_Inval:	.asciiz "\nOpcao invalida\n"
msg_Vazio:	.asciiz "\nLista Vazia\n"
charEnter:	.asciiz "\n"
abreChave:	.asciiz "Index ["
end_Chave:	.asciiz "] = "
	.text

main:
	la $s0, descritor
	sw $zero, 0($s0)	# Primeio elemento
	sw $zero, 4($s0)	# Quantidade Lista
	sw $zero, 8($s0)	# Ultimo elemento
	move $s1, $zero		# $s1 Guarda o inicio da lista

menuOp:
	li  $v0, 4
	la $a0, printMenu
	syscall

	li $v0, 5
	syscall

	beq $v0, 1, insere_elemento
	beq $v0, 2, busca
	beq $v0, 3, ordena
	beq $v0, 4, imprimir_lista
	beq $v0, 5, exit

	j imprimeInvalida

insere_elemento:
	li $v0, 4
	la $a0, pedeValor
	syscall

	li $v0, 5
	syscall
	move $t0, $v0 		#t0 tem o valor que quer inserir

	li $v0, 9
	addi $a0, $zero, 12
	syscall

	lw $t1, 4($s0)		# Incrementa a quantidade no descritor
	addi $t1, $t1, 1
	sw $t1, 4($s0)

	sw $t0, 4($v0)
	sw $zero, 8($v0)

	lw $s1, 8($s0)		# Carrega o valor final do nodo descritor
	bne $s1, $zero, insereFim	# Se existe valor final, insere fim
	sw $v0, 0($s0)		# Nao existe valor final, nodo descritor inicio = nodo criado agora

insereFim:
	sw $v0, 8($s0)		# Atualiza o elemento fim do nodo descritor
	sw $s1, 0($v0)		# Novo fim, aponta para antigo fim
	beq $s1, $zero, retorno
	sw $v0, 8($s1)		# Nodo anterior aponta pra frente
	b retorno

busca:
	li $v0, 4
	la $a0, pedeIndex
	syscall
	li $v0, 5
	syscall
	lw $t1, 0($s0)			# Carrega o inicio da lista
	lw $t0, 4($s0)			# Carrega a qtd_elementos da lista
	addi $t2, $zero, -1		#Contador
	blt $v0, $t0, loop_busca
	li $v0, 4
	la $a0, msg_Inval
	syscall

	b retorno

loop_busca:
	move $t0, $t1
	lw $t1, 8($t1)
	addi $t2, $t2, 1
	blt $t2, $v0, loop_busca

	li $v0, 4
	la $a0, oqueFazer
	syscall

	li $v0, 5
	syscall

	beq $v0, 1, remover_elemento
	bne $v0, $zero, imprimeInvalida

	li $v0, 4
	la $a0, novoValor
	syscall

	li $v0, 5
	syscall

	sw $v0, 4($t0)
	b retorno

remover_elemento:
	lw $t7, 4($s0)
	addi $t7, $t7, -1
	sw $t7, 4($s0)
	lw $t2, 0($t0)	# Grava o elemento anterior
	lw $t3, 8($t0)	# Grava o elemento posterior
	beq $t2, $zero, remove_primeiro
	beq $t3, $zero, remove_ultimo
	sw $t2, 0($t3)
	sw $t3, 8($t2)

	b retorno
remove_primeiro:
	sw $t3, 0($s0)
	beq $t3, $zero, main
	sw $zero, 0($t3)

	b retorno

remove_ultimo:
	sw $t2, 8($s0)
	beq $t2, $zero, main
	sw $zero, 8($t2)

	b retorno

imprimir_lista:
	lw $s1, 0($s0)		# Nodo incial em $s1
	beq $s1, $zero, listaVazia
	move $t0, $zero

loop:
	lw $t1, 4($s1)		# Carrega o primeiro valor da lista

	li $v0, 4
	la $a0, charEnter
	syscall

	li $v0, 4
	la $a0, abreChave
	syscall

	li $v0, 1
	move $a0, $t0
	syscall

	li $v0, 4
	la $a0, end_Chave
	syscall

	li $v0, 1
	move $a0, $t1
	syscall

	lw $s1, 8($s1)
	addi $t0, $t0, 1
	bne $s1, $zero, loop

	li $v0, 4
	la $a0, charEnter
	syscall

	b retorno

retorno:
	b menuOp


listaVazia:
	li $v0, 4
	la $a0, msg_Vazio
	syscall
	j menuOp

imprimeInvalida:
	li $v0, 4
	la $a0, msg_Inval
	syscall
	j menuOp

ordena:
	lw $t0, 4($s0)
	beq $t0, $zero, listaVazia

	li $t1, 4				# Aloca espaco para stack
	mult $t0, $t1
	mflo $t0
	sub $sp, $sp, $t0

	move $s1, $sp			# Guarda endeço do inicio da pilha
	lw $a0, 0($s0)
	jal	procuraMaior

	move $s4, $v0			# s4 = Maior valor na lista
	li $t1, 1

radix:
	jal limpaBucket

	lw $t0, 0($s0)			# Carrega endereço do início da lista
	la $s2, theBucket		# Carrega o bucket
	addi $s2, $s2, 40	
	li $t2, 10				# $t2 Valor do mod
	li $t4, 4

	bgt $t1, $s4, disaloc

encheBucket:
	jal acessaBucket

	lw $t3, 0($v1)

	addi $t3, $t3, 1
	sw $t3, 0($v1)

	lw $t0, 8($t0)				# Carrega próximo elemento da lista

	bne $t0, $zero, encheBucket	# Testa se o próximo elemento não é nulo

	la $t0, theBucket
	lw $t6, 0($t0)
	addi $t0, $t0, 4
	li $t5, 1

soma_buckets:
	lw $t7, 0($t0)
	add $t6, $t6, $t7
	sw $t6, 0($t0)
	addi $t0, $t0, 4
	addi $t5, $t5, 1
	blt $t5, 20, soma_buckets

	lw $t0, 8($s0)				# Carraga o fim da lista

preenche_aux:
	jal acessaBucket

	lw $t3, 0($v1)

	addi $t3, $t3, -1
	sw $t3, 0($v1)

	mult $t3, $t4
	mflo $t3
	sub $t3, $s1, $t3			# $t3 contem o endereco da pilha onde o elemento sera salvo

	lw $t5, 4($t0)				# Carrega valor da lista para salvar na pilha
	sw $t5, 0($t3)				# Salva na pilha
	lw $t0, 0($t0)				# Retorna para o elemento anterior na lista
	bne $t0, $zero, preenche_aux

	lw $t0, 0($s0)				# Carrega inicio da lista para $t0
	lw $t5, 4($s0)				# Carrega quantidade de elementos
	li $t2, 0					# Inicia contador
	move $t3, $s1				# Carrega inicio da pilha

preenche_lista:
	lw $t4, 0($t3)				# Recupera o valor na pilha
	sw $t4, 4($t0)				# Salva o valor na lista
	lw $t0, 8($t0)				# Proximo elemento na lista

	addi $t3, $t3, -4			# Prox elemento na pilha
	addi $t2, $t2, 1			# Somar o contador

	blt $t2, $t5, preenche_lista
	mult $t5, $t2
	mflo $t5

	li $t2, 10
	mult $t2, $t1
	mflo $t1

	b radix

acessaBucket:
	lw $t3, 4($t0)
	div $t3, $t1
	mflo $t3

	div $t3, $t2
	mfhi $t3

	mult $t4, $t3
	mflo $t3

	add $v1, $s2, $t3 			# Retorna em $v1 o endereço da posição do bucket
	jr $ra

procuraMaior:
	li $t7, -1	
	lw $t0, 4($a0)	# Carrega o primeiro elemento
	mult $t0, $t7
	mflo $t6
	bgt $t6, $t0, eMaior
		
loopMaior:
	lw $a0, 8($a0)
	beq $a0, $zero, fimLista	# Mudamos t1 por t6
	lw $t6, 4($a0)
	bgt $t6, $t0, eMaior
	mult $t6, $t7
	mflo $t6
	bgt $t6, $t0, eMaior
	b loopMaior
eMaior:
	move $t0, $t6
	b loopMaior
fimLista:
	move $v0, $t0
	jr $ra

limpaBucket:
	la $s6, theBucket
	move $s7, $zero
loopBucket:
	sw $zero, 0($s6)
	addi $s7, $s7, 1
	addi $s6, $s6, 4
	blt $s7, 20, loopBucket
	jr $ra

disaloc:
	lw $t7, 4($s0)
	li $t4, 4
	mult $t4, $t7
	mflo $t7
	add $sp, $sp, $t7

	b retorno

exit:
	li $v0, 10
	syscall
