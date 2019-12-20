		.data

meses:		.word		31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
titulo:		.asciiz		"CALCULA DIFERENCA ENTRE DUAS DATAS VALIDAS"
texto:		.asciiz		"\nDiferença das datas em dias: "
le_dia:		.asciiz		"\nEntre com o dia: "
le_mes:		.asciiz		"Entre com o mes: "
le_ano:		.asciiz		"Entre com o ano: "
data1:		.asciiz		"\n\nDATA NUMERO 1"
data2:		.asciiz		"\nDATA NUMERO 2"

		.text

main:
		li	$v0, 4			#LENDO A 1º DATA
		la	$a0, titulo
		syscall
		la	$a0, data1
		syscall
		la	$a0, le_dia
		syscall
		li	$v0, 5			
		syscall
		add	$t0, $zero, $v0
		li	$v0, 4
		la	$a0, le_mes
		syscall
		li	$v0, 5
		syscall
		add	$t1, $zero, $v0
		li	$v0, 4
		la	$a0, le_ano
		syscall
		li	$v0, 5
		syscall
		add	$t2, $zero, $v0


		li	$v0, 4			#LENDO A 2º DATA
		la	$a0, data2
		syscall
		la	$a0, le_dia
		syscall
		li	$v0, 5			
		syscall
		add	$s0, $zero, $v0
		li	$v0, 4
		la	$a0, le_mes
		syscall
		li	$v0, 5
		syscall
		add	$s1, $zero, $v0
		li	$v0, 4
		la	$a0, le_ano
		syscall
		li	$v0, 5
		syscall
		add	$s2, $zero, $v0


		addi	$s7, $zero, 365

		sub 	$s3, $s2, $t2	#diferença de anos
		#$sub	$s4, $s1, $t1	#diferença de meses
		sub	$s5, $s0, $t0	#diferença de dias

		mult	$s3, $s7
		mflo	$s3
		add 	$s6, $s3, $zero #calcula a diferença de anos e multiplica por dias
		add 	$s6, $s5, $s6	#adiciona a diferença de dias do mes


		add $t6, $zero, $zero
		add $t7, $zero, $zero	
		
		la	$t3, meses
		addi	$t4, $t1, -2
		blt	$t4, $zero, mortadela14
		addi 	$t5, $zero, 4
		mult	$t4, $t5
		mflo	$t4
		add 	$t4, $t3, $t4
		
laco:
		lw	$t5, 0($t4)
		add 	$t6, $t6, $t5
		addi	$t4, $t4, -4
		ble	$t3, $t4, laco
		
mortadela14:
		

		addi 	$t4, $s1, -2
		blt	$t4, $zero, mortadela15
		addi 	$t5, $zero, 4
		mult 	$t4, $t5
		mflo	$t4
		add	$t4, $t3, $t4

laco2:		
		lw 	$t5, 0($t4)
		add	$t7, $t7, $t5
		addi 	$t4, $t4, -4
		ble	$t3, $t4, laco2

mortadela15:
		 
		sub	$t7, $t7, $t6
		add	$t7, $t7, $s6

		li 	$v0, 1
		add	$a0, $t7, $zero	#imprime resultado
		syscall	
	




	
		li	$v0, 10			#FINALIZAÇÃO DO PROGRAMA
		syscall


		
