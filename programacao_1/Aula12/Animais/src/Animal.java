public class Animal {
	protected String nome;
	protected String cor;
	protected String ambiente;
	protected int comprimento;
	protected int patas;
	protected float velocidade;
	
	public Animal(String nome, String cor, String ambiente, int comprimento, int patas, float velocidade){
		this.alteraNome(nome);
		this.alteraCor(cor);
		this.alteraAmbiente(ambiente);
		this.alteraComprimento(comprimento);
		this.alteraPatas(patas);
		this.alteraVelocidade(velocidade);
	}
	
	public void alteraNome(String nome){
		this.nome = nome;
	}
	
	public void alteraCor(String cor){
		this.cor = cor;
	}
	
	public void alteraAmbiente(String ambiente){
		this.ambiente = ambiente;
	}
	
	public void alteraComprimento(int comprimento){
		if(comprimento > 0)
			this.comprimento = comprimento;
	}
	
	public void alteraPatas(int patas){
		if(patas > 0)
			this.patas = patas;
	}
	
	public void alteraVelocidade(float velocidade){
		if(velocidade > 0)
			this.velocidade = velocidade;
	}
	
	public void dados(){
		System.out.println("Nome: " + this.nome + "\nCor: " + this.cor + "\nAmbiente: " + this.ambiente 
				+ "\nComprimento: " + this.comprimento + "\nPatas: " + this.patas + "\nVelocidade: " + this.velocidade);
	}
	
}