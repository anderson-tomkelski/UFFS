import java.util.*;

public class Principal {
	private static Scanner sc;

	public static void main(String[] args) {
		
		List<Conta> contas = new ArrayList<Conta>();
		
		Pessoa p1 = new Pessoa("Vector", "091.291.293-12");
		ContaCorrente CC = new ContaCorrente(1000000, "123.1231", p1);
		contas.add(CC);
		
		p1 = new Pessoa("Gru", "235.987.234-21");
		ContaPoupanca CP = new ContaPoupanca(5000000, "098098.1231", p1);
		contas.add(CP);
		
		sc = new Scanner(System.in);
		String nome;
		double valor;
		Conta c;
		int op;
		do{
			System.out.println("BANCO DO MAL");
			System.out.println("0 - Sair");
			System.out.println("1 - Cadastrar novos usuarios");
			System.out.println("2 - Mostrar dados do usuario");
			System.out.println("3 - Remover conta");
			System.out.println("4 - Sacar");
			System.out.println("5 - Depositar");
			System.out.println("6 - Transferir");
			System.out.println("7 - Atualiza taxa da poupança");
			op = sc.nextInt();
			switch(op){
				case 0:
					break;
				case 1:
					cadastrarUsuarios(sc, contas);
					break;
				case 2:
					sc.nextLine();
					System.out.println("Digite o nome do titular: ");
					nome = sc.nextLine();
					if(!mostrarConta(nome, contas))
						System.out.println("Conta não encontrada!");
					break;
				case 3:
					sc.nextLine();
					System.out.println("Digite o nome do titular: ");
					nome = sc.nextLine();
					if(removerConta(nome, contas))
						System.out.println("Usuário removido!");
					else
						System.out.println("Usuário não removido");
					break;
					
				case 4:
					System.out.println("Digite o nome do titular: ");
					sc.nextLine();
					nome = sc.nextLine();
					System.out.println("Digite o valor que deseja sacar");
					valor = sc.nextDouble();
					c = buscarConta(nome, contas);
					if(c!=null){
						c.sacar(valor);
					}
					break;
				case 5:
					System.out.println("Digite o nome do titular: ");
					sc.nextLine();
					nome = sc.nextLine();
					System.out.println("Digite o valor que deseja depositar");
					valor = sc.nextDouble();
					c = buscarConta(nome, contas);
					if(c!=null){
						c.depositar(valor);
					}else{
						System.out.println("Conta não encontrada!");
					}
					break;
				case 6:
					System.out.println("Digite o nome do titular da conta origem: ");
					sc.nextLine();
					nome = sc.nextLine();
					c = buscarConta(nome,  contas);
					System.out.println("Digite o nome do titular da conta de destino: ");
					nome = sc.nextLine();
					Conta CD = buscarConta(nome, contas);
					if(c==null && CD==null){
						System.out.println("Conta não encontrada!");
						break;
					}
					System.out.println("Digite o valor a ser transferido: ");
					valor = sc.nextDouble();
					c.transferirPara(CD, valor);
					break;
				case 7:
					System.out.println("Digite o nome do titular da conta a ser atualizada: ");
					sc.nextLine();
					nome = sc.nextLine();
					ContaPoupanca cp = buscarPoupanca(nome, contas);
					if(cp==null){
						System.out.println("Conta não encontrada!");
						break;
					}
					System.out.println("Digite  a taxa que deseja atualizar: ");
					double taxa = sc.nextDouble();
					cp.atualiza(taxa);
					break;
				default:
					System.out.println("Opção inválida!!!");
			}
			
		} while(op != 0);
		
		System.out.println("Saindo...");
	}
	
	public static ContaPoupanca buscarPoupanca(String nome, List<Conta> contas){
		ContaPoupanca cp = null;
		for(Conta c: contas){
			if(c.titular.getNome().equals(nome)){
				try{
					cp = (ContaPoupanca) c;
				}catch(Exception e){
				}
			}
		}
		return cp;
	}
	
	public static Conta buscarConta(String nome, List<Conta> contas){
		for(Conta c: contas){
			if(c.titular.getNome().equals(nome)){
				return c;
			}
		}
		return null;
	}
	
	public static void cadastrarUsuarios(Scanner sc, List<Conta> contas){
		sc.nextLine();
		System.out.println("Digite o nome do usuário: ");
		String nome = sc.nextLine();
		System.out.println("Digite o CPF do usuario: ");
		String cpf = sc.nextLine();
		Pessoa p = new Pessoa(nome, cpf);
		double valor = 0;
		System.out.println("Deseja iniciar com um depósito? S/N");
		if(sc.nextLine().charAt(0) == 'S'){
			System.out.println("Entre com o valor desejado: ");
			valor = sc.nextDouble();
			sc.nextLine();
		}
		System.out.println("Digite o número da conta e a agência (xxxx.xxxx): ");
		String numero = sc.nextLine();
		
		
		System.out.println("Digite o tipo da conta desejada: 1 - Conta Corrente; 2 - Conta Poupança");
		int tipo = sc.nextInt();
		if(tipo == 1){
			ContaCorrente CC = new ContaCorrente(valor, numero, p);
			contas.add(CC);
		}else{
			ContaPoupanca CP = new ContaPoupanca(valor, numero, p);
			contas.add(CP);
		}
	}
	
	public static boolean mostrarConta(String nome, List<Conta> contas){
		for(Conta c: contas){
			if(c.titular.getNome().equals(nome)){
				System.out.println(c);
				return true;
			}
		}
		return false;
	}
	
	public static boolean removerConta(String nome, List<Conta> contas){
		int indice = -1;
		for(Conta c: contas){
			if(c.titular.getNome().equals(nome)){
				indice=contas.indexOf(c);
				contas.remove(indice);
				return true;
			}
		}
		return false;
	}

}