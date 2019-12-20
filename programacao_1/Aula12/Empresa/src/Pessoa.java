
public class Pessoa {
	protected int idade;
	protected String nome;
	
	public Pessoa(String nome, int idade){
		this.nome=nome;
		this.idade=idade;
	}
	
	@Override
	public String toString(){
		return "Idade: " + this.idade + " Nome: " + this.nome;
	}
	
	public void ComparaIdade(Pessoa pp){
		if(this.idade > pp.idade){
			System.out.println(this.nome + " É mais velho!");
		}else{
			System.out.println(pp.nome + " É mais velho");
		}
	}
}
