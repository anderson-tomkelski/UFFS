import java.util.Scanner;
class Programa{
	public static void main(String[] args){
		int op=7;
		Scanner le = new Scanner(System.in);		
		Conta c1=new Conta(1, "Joaozinho", 50);
		Conta c2=new Conta();
		c2.setNumero(2);

		System.out.println("\n\n\t\tBANCO DE UMA CONTA SÓ\n");
		do{
			
			System.out.println("\t\t\t\tMENU");
			System.out.println("\t1 - Consultar Saldo");
			System.out.println("\t2 - Efetuar Saque");
			System.out.println("\t3 - Efetuar Deposito");
			System.out.println("\t4 - Realizar Transferência");
			System.out.println("\t5 - Exibir dados da conta");
			System.out.println("\t6 - Sair");
			op=le.nextInt();
			switch(op){
				case 1:	
					System.out.println("\tSaldo da conta: "+c1.getSaldo());
					break;
				case 2:
					System.out.println("\tDigite o valor para sacar: ");
					c1.sacar(le.nextDouble());
					break;
				case 3:
					System.out.println("\tDigite o valor para deposito: ");
					c1.depositar(le.nextDouble());
					break;
				case 4:
					System.out.println("\tDigite o valor para transferência: ");
					c1.transferirPara(c2, le.nextDouble());
					break;
				case 5:
					System.out.println(c1);
					break;
				case 6:
					break;
				default:
					System.out.println("Opção inexistente!\n");	
			}
		}while(op!=6);
	
				
	}
}
