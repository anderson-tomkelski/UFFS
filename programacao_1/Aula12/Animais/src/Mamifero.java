public class Mamifero extends Animal{
	private String alimento;
	
	public Mamifero(String nome, String cor, String ambiente,
			  int comprimento, int patas, float velocidade, String alimento){
		super(nome, cor, ambiente, comprimento, patas, velocidade);
		this.alteraAlimento(alimento);
	}
	
	public void alteraAlimento(String alimento){
		this.alimento = alimento;
	}
	
	public String alimento(){
		return this.alimento;
	}
	
	@Override
	public void dados(){
		super.dados();
		System.out.println("Alimento: " + this.alimento);
	}
	
}
