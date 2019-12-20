public class Gato extends Pet {
	
	public Gato(String nome, int idade){
		super(nome, idade);
	}
	
	@Override
	public void emitirSom(){
		System.out.println("Tssssss");
	}
	
	public void arranhar(){
		System.out.println("Rau");
	}
}
