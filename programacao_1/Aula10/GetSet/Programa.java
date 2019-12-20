import java.util.Scanner;
class Programa{
	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);
		Povo povo = new Povo();
		int opcao;
		do{
			System.out.println("Exercicios Get Set");
			System.out.println("0 - Sair pessoas");
			System.out.println("1 - Adicionar nova pessoa");
			System.out.println("2 - Listar pessoas");
			opcao = sc.nextInt();
			switch(opcao){
				case 0:
					break;
				case 1:
					clear();
					Pessoa novaPessoa = lePessoa(sc);
					povo.adicionar(novaPessoa);
					break;
				case 2:
					clear();
					povo.listar();
					break;
				default:
					clear();
					System.out.println("Mortadela");
			}
		}while(opcao!=0);
	}
	
	public static Pessoa lePessoa(Scanner sc){
		System.out.println("Digite o nome:");
		sc.nextLine();
		String nome = sc.nextLine();
		System.out.println("Digite a idade:");
		int idade = sc.nextInt();
		System.out.println("Digite o peso:");
		float peso = sc.nextInt();
		Pessoa novaPessoa = new Pessoa(idade, peso, nome);
		return novaPessoa;
	}

	public static void clear(){
		System.out.println("\033[H\033[J");
	}
}	
