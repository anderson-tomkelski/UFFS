public class Pet {
	public String nome;
	public int idade;
	
	public Pet(String nome, int idade){
		this.nome = nome;
		this.idade = idade;
	}
	
	public void brincar(){
		System.out.println("Brincando...");
	}
	
	public void emitirSom(){
		System.out.println("Sonorizando...");
	}
}
