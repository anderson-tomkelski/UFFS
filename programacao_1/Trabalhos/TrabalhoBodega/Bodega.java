import java.util.Scanner;
class Bodega{
	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);
	
		Empresa JoaozinhoBodega = new Empresa("JoazinhoBar", "699.884.680.001-32");
		Endereco endereco = new Endereco("Rua 7", "Bairro 13", "Jerusalém", 72);
		Funcionario f1 = new Funcionario("Jesus", "860.261.813-18", endereco, "3323-7777", "Produção de vinho fino", 1860.00);

		JoaozinhoBodega.contratar(f1);
		
		endereco = new Endereco("Rua 7", "Bairro 13", "Jerusalém", 73);
		f1 = new Funcionario("Judas", "385.019.499-06", endereco, "98848-7777", "Balconista", 1000.00);
		JoaozinhoBodega.contratar(f1);

		endereco = new Endereco("Rua 7", "Bairro 13", "Jerusalém", 74);
		f1 = new Funcionario("Pedro", "362.975.187-34", endereco, "99987-7777", "Segurança", 1200.00);
		JoaozinhoBodega.contratar(f1);
		
		int escolha = 0;
		do{
			clear();
			imprimirMenu();
			escolha = sc.nextInt();
			sc.nextLine();
			switch(escolha){
				case 0:
					clear();
					System.out.println("Saindo...");
					break;
				case 1:
					clear();
					menuFuncionarios(JoaozinhoBodega);
					break;
				case 2:
					clear();
					menuClientes(JoaozinhoBodega);
					break;
				case 3:
					clear();
					menuBebidas(JoaozinhoBodega);
					break;
				default:
					System.out.println("Opção inválida");

			}
		}while(escolha != 0);
		
	}
	
	public static void imprimirMenu(){
		System.out.println("1 - Acessar menu de funcionários");
		System.out.println("2 - Acessar menu de clientes");
		System.out.println("3 - Acessar menu de bebidas");
		System.out.println("0 - Sair");
		System.out.println("Selecione uma opção");
	}

	public static void menuFuncionarios(Empresa empresa){
		Scanner sc = new Scanner(System.in);
		int escolha = 0;
		int codigo;
		String nomeBusca;
		do{
			System.out.println("0 - Retornar ao menu principal");
			System.out.println("1 - Contratar funcionário");
			System.out.println("2 - Demitir funcionário");
			System.out.println("3 - Ajustar salário");
			System.out.println("4 - Imprimir lista de funcionários");
			System.out.println("Selecione uma opção");
			escolha = sc.nextInt();
			switch(escolha){
				case 0:
					break;
				case 1:
					clear();
					Funcionario novoFuncionario = leDados();
					empresa.contratar(novoFuncionario);
					break;
				case 2:
					clear();
					System.out.println("Digite o nome do funcionario que deseja demitir");
					sc.nextLine();
					nomeBusca = sc.nextLine();
					codigo = empresa.procurarFuncionario(empresa, nomeBusca);
					if(codigo != -1){
						empresa.demitir(codigo);
						System.out.println("Funcionario demitido");
					}else
						System.out.println("Funcionário não encontrado, verifique o nome procurado");
					break;
				case 3:
					clear();
					System.out.println("Digite o nome do funcionario que deseja buscar");
					sc.nextLine();
					nomeBusca = sc.nextLine();
					codigo = empresa.procurarFuncionario(empresa, nomeBusca);
					if(codigo != -1){
						ajustarSalario(empresa, codigo);
						System.out.println("Salario ajustado");
					}
					else
						System.out.println("Funcionário não encontrado, verifique o nome procurado");
					break;
				case 4:
					clear();
					empresa.imprimirFuncionarios();
					break;
				default:
					System.out.println("Opção inválida");
			}
		}while(escolha != 0);
	}
	
	public static void menuClientes(Empresa empresa){
		Scanner sc = new Scanner(System.in);
		int escolha = 0;
		do{
			System.out.println("0 - Retornar ao menu principal");
			System.out.println("1 - Cadastrar novo cliente");
			System.out.println("2 - Excluir cliente");
			System.out.println("3 - Imprimir lista de clientes");
			System.out.println("Selecione uma opção");
			escolha = sc.nextInt();
			switch(escolha){
				case 0:
					break;
				case 1:
					clear();
					Cliente novoCliente = leDadosCliente();
					empresa.inserirCliente(novoCliente);
					break;
				case 2:
					clear();
					System.out.println("Digite o nome do cliente que deseja excluir da lista");
					sc.nextLine();
					String nome = sc.nextLine();
					int codigo = empresa.procurarCliente(empresa, nome);
					if(codigo != -1){
						empresa.excluirCliente(codigo);
						System.out.println("Cliente excluido");
					}else
						System.out.println("Cliente não encontrado, verifique o nome procurado");
					break;
				case 3:
					clear();
					empresa.imprimirClientes();
					break;
				default:
					System.out.println("Opção inválida");
			}
		}while(escolha != 0);
	}
	
	public static void menuBebidas(Empresa empresa){
		Scanner sc = new Scanner(System.in);
		int escolha = 0;
		int quantidade;
		String nome;
		do{
			System.out.println("0 - Retornar ao menu principal");
			System.out.println("1 - Cadastrar nova bebida");
			System.out.println("2 - Excluir bebida");
			System.out.println("3 - Comprar bebida");
			System.out.println("4 - Vender bebida");
			System.out.println("5 - Imprimir lista de bebidas");
			System.out.println("Selecione uma opção");
			escolha = sc.nextInt();
			switch(escolha){
				case 0:
					break;
				case 1:
					clear();
					Bebida novaBebida = leDadosBebida();
					empresa.inserirBebida(novaBebida);
					break;
				case 2:
					clear();
					System.out.println("Digite o nome da bebida que deseja excluir da lista");
					sc.nextLine();
					nome = sc.nextLine();
					int codigo = empresa.procurarBebida(empresa, nome);
					if(codigo != -1){
						empresa.excluirBebida(codigo);
						System.out.println("Bebida excluida");
					}else
						System.out.println("Bebida não encontrada, verifique o nome procurado");
					break;
				case 3:
					clear();
					System.out.println("Digite o nome da bebida que deseja comprar");
					sc.nextLine();
					nome = sc.nextLine();
					Bebida compraBebida = empresa.procurarBebidaCompraVenda(empresa, nome);
					if(compraBebida != null){
						System.out.println("Digite a quantidade que desja comprar");
						quantidade = sc.nextInt();
						String mensagem = compraBebida.comprar(quantidade);
						System.out.println(mensagem);
					}else
						System.out.println("Bebida não encontrada, verifique o nome procurado");
					break;
				case 4:
					clear();
					System.out.println("Digite o nome da bebida que deseja vender");
					sc.nextLine();
					nome = sc.nextLine();
					Bebida vendeBebida = empresa.procurarBebidaCompraVenda(empresa, nome);
					if(vendeBebida != null){
						System.out.println("Digite a quantidade que desja vender");
						quantidade = sc.nextInt();
						String mensagem = vendeBebida.vender(quantidade);
						System.out.println(mensagem);
					}else
						System.out.println("Bebida não encontrada, verifique o nome procurado");
					break;
				case 5:
					clear();
					empresa.imprimirBebidas();
					break;
				default:
					System.out.println("Opção inválida");
			}
		}while(escolha != 0);
	}

	public static Funcionario leDados(){
		Scanner sc = new Scanner(System.in);
		System.out.println("Digite as informções do usuário");
		System.out.println("Digite o nome");
		String nome = sc.nextLine();
		System.out.println("Digite o CPF");
		String cpf = sc.nextLine();
		System.out.println("Digite a função");
		String funcao = sc.nextLine();
		System.out.println("Digite o telefone");
		String telefone = sc.nextLine();
		System.out.println("Digite o nome da rua");
		String rua = sc.nextLine();
		System.out.println("Digite o bairro");
		String bairro = sc.nextLine();
		System.out.println("Digite a cidade");
		String cidade = sc.nextLine();
		System.out.println("Digite o número da casa");
		int numero = sc.nextInt();
		System.out.println("Digite o salário inicial");
		double salarioInicial = sc.nextDouble();
		Endereco endereco = new Endereco(rua, bairro, cidade, numero);
		Funcionario funcionario = new Funcionario(nome, cpf, endereco, telefone, funcao, salarioInicial);
		return funcionario;
	}

	public static void ajustarSalario(Empresa empresa, int codigo){
		Scanner sc = new Scanner(System.in);
		System.out.println("Digite o percentual de aumento que deseja pagar");
		double percentual = sc.nextDouble();
		empresa.aumentar(codigo, percentual);
		
	}

	public static Cliente leDadosCliente(){
		Scanner sc = new Scanner(System.in);
		System.out.println("Digite o nome do cliente");
		String nome = sc.nextLine();
		System.out.println("Digite o CPF do cliente");
		String cpf = sc.nextLine();
		System.out.println("Permite fiado? S/N");
		boolean fiado = (sc.nextLine().charAt(0) == 'S' ? true : false);
		Cliente novoCliente = new Cliente(nome, cpf, fiado);
		return novoCliente;
		
	}

	public static Bebida leDadosBebida(){
		Scanner sc = new Scanner(System.in);
		System.out.println("Digite o nome da bebida");
		String nome = sc.nextLine();
		System.out.println("Digite o teor alcoolico");
		double teor = sc.nextDouble();
		System.out.println("Digite o preço de venda");
		double preco = sc.nextDouble();
		System.out.println("Digite o tamanho da garrafa - ML");
		int quantidade = sc.nextInt();
		System.out.println("Digite o estoque inicial");
		int estoque = sc.nextInt();
		Bebida novaBebida = new Bebida(nome, teor, preco, quantidade, estoque);
		return novaBebida;
	}

	public static void clear(){
		System.out.println("\033[H\033[2J");
		System.out.flush();
	}
}
