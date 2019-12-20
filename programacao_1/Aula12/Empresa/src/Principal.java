public class Principal {
	public static void main(String[] args) {
		Pessoa pessoa = new Pessoa("Anderson", 19);
		System.out.println(pessoa);
		
		Usuario pessoa2 = new Usuario("Gilbert", 18, 12345, "gilbert@sl.org");
		System.out.println(pessoa2);
		
		pessoa.ComparaIdade(pessoa2);
		
		pessoa2.acessar("gilbert@sl.org", 12345);
	}
}
