import java.util.Scanner;

class Programa{
	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);

		Conta c1 = new Conta();
		c1 = criaContas(c1);

		Conta transfer = new Conta();
		transfer.setDono("Banco");
		transfer.depositar(0.0);
		transfer.setNumero(2);
		operacoes(c1, transfer);
	}

	public static Conta criaContas(Conta c1){
		Scanner sc = new Scanner(System.in);
		char decisao;
	
		c1.setNumero(1);
		System.out.println("Digite o nome do titular da conta");
		c1.setDono(sc.nextLine());
		
		System.out.println("Deseja fazer um deposito inicial? S/N");
		decisao = sc.nextLine().charAt(0);
		
		if (decisao == 'S' || decisao == 's'){
			System.out.println("Digite o valor do deposito inicial");
			c1.depositar(sc.nextDouble());

		}else if (decisao == 'N' || decisao == 'n'){
			c1.depositar(0.0);

		} else{
			System.out.println("Opção inválida, seu saldo iniciará zerado");
			c1.depositar(0.0);
		}

		return c1;
	}

	public static void operacoes(Conta c1, Conta c2){
		Scanner sc = new Scanner(System.in);
		int opcao=0;
		do{
			System.out.println("1. Consultar saldo");
			System.out.println("2. Efetuar saque");
			System.out.println("3. Efetuar depósito");
			System.out.println("4. Efetuar transferência");
			System.out.println("5. Exibir dados da conta");
			System.out.println("6. Sair");

			opcao=sc.nextInt();
			System.out.print("\033[H\033[2J");
		
			switch(opcao){
				case 1:
					System.out.println("Saldo atual: " + c1.getSaldo());
					break;
				case 2:
					System.out.println("Digite o valor que deseja sacar");
					double valorSaque = sc.nextDouble();
					boolean sacou = c1.sacar(valorSaque);
					checaSaque(sacou, c1);
					break;
				case 3:
					System.out.println("Digite o valor que deseja depositar");
					double valorDeposito = sc.nextDouble();
					c1.depositar(valorDeposito);
					System.out.println("Saldo atual: " + c1.getSaldo());
					break;
				case 4:
					System.out.println("Digite o valor que deseja tranferir");
					double valorTransf = sc.nextDouble();
					boolean transferiu = c1.transferir(valorTransf, c2);
					checaTransferencia(transferiu, c1);
					break;
				case 5:
					c1.dadosConta();
					break;
				case 6:
					break;
				default:
					System.out.print("\033[H\033[2J");
					System.out.println("Opção inválida");
					continue;
			}				
		}while(opcao!=6);
	}
	
	public static void checaTransferencia(boolean transferiu, Conta c){
		if(transferiu)
			System.out.println("Valor restante: " + c.getSaldo());
		else
			System.out.println("Saldo insuficiente para transferencia!\nSaldo atual: " + c.getSaldo());
	
	}
	public static void checaSaque(boolean sacou, Conta c){
		if (sacou)
			System.out.println("Valor restante: " + c.getSaldo());
		else
			System.out.println("Saldo insuficiente!\nSaldo atual: " + c.getSaldo());
	}
}
