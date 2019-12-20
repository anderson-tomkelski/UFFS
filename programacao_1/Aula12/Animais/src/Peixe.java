public class Peixe extends Animal{
	private String caracteristica;
	
	public Peixe(String nome, String cor, String ambiente,
				  int comprimento, int patas, float velocidade, String caracteristica){
		
		super(nome, cor, ambiente, comprimento, patas, velocidade);
		this.alteraCaracteristica(caracteristica);
		}
	
	public void alteraCaracteristica(String caracteristica){
		this.caracteristica = caracteristica;
	}
	
	public String caracteristica(){
		return this.caracteristica;
	}
	
	@Override
	public void dados(){
		super.dados();
		System.out.println(" Característica: " + this.caracteristica);
	}
}
