public class Cachorro extends Pet {
	
	public Cachorro(String nome, int idade){
		super(nome, idade);
	}
	
	@Override
	public void emitirSom(){
		System.out.println("AU");
	}
	
	public void cavar(){
		System.out.println("Cavando...");
	}
}
