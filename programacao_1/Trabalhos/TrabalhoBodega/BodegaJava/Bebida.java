class Bebida{
	String nome;
	double teorAlcoolico;
	double preco;
	int quantidadeML;
	int estoque;
	static int numeroDeBebidas=0;

	public Bebida(String nomeBebida, double teorBebida, double precoBebida, int quantidadeBebida, int estoqueBebida){
		this.nome = nomeBebida;
		this.teorAlcoolico = teorBebida;
		this.preco = precoBebida;
		this.quantidadeML = quantidadeBebida;
		this.estoque = estoqueBebida;
	}

	public String comprar(int quantidade){
		if(quantidade > 0){
			this.estoque += quantidade;
			return "Quantidade em estoque: " + this.estoque;
		}else
			return "Pedido inválido!";
	}

	public String vender(int quantidade){
		if(conferirEstoque(quantidade)){
			estoque -= quantidade;
			return "Total a pagar: R$" + this.preco*quantidade + "\nEstoque atual: " + this.estoque;
		}else
			return "Estoque insuficiente!";
	}

	public boolean conferirEstoque(int quantidade){
		if(this.estoque > 0 && quantidade > 0)
			return true;
		else
			return false;
	}

	public String toString(){
		return "Nome: " + this.nome + "\nPreço: " + this.preco + "\nTamanho: " + this.quantidadeML + " ML " 
			+ "\nTeor Alcoólico: " + this.teorAlcoolico + "%" + "\nQuantidade Disponível: " + this.estoque;
	}	
}
