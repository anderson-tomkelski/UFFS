class Material{
	private int codigo;
	private static int qtd;
	private String nome;
	
	public Material(int codigo, String nome, int qtd){
		this.codigo = codigo;
		this.nome = nome;
		abastecer(qtd);
	}
	
	public Material(){
	}
	
	public void setNome(String nome){
		this.nome = nome;
	}

	public Material(int codigo, String nome){
		this.codigo = codigo;
		this.nome = nome;
		this.qtd = 0;
	}
	
	public static void abastecer(int qtd){
		System.out.println("Chamou");
		if(qtd<0)
			System.out.println("Quantidade inválida");
		else
			qtd += qtd;
	}

	public void retiradas(int qtd){
		if(qtd<0)
			System.out.println("Quantidade inválida");
		else
			this.qtd -= qtd;
	}

	public void mostrar(){
		System.out.println("\nCódigo: " + this.codigo + "\nNome: " + this.nome + "\nQuantidade: "+ this.qtd);
	}
}
