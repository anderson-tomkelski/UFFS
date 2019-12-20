class Medicamento{
	String nome;
	double precoVenda;
	Data dataValidade;
	Laboratorio laboratorio;
	boolean receitaObrigatoria;
	int qtdEstoque;

	public void reajustarPrecoVenda(double percentual){
		precoVenda += (percentual/100)*precoVenda;
		System.out.println("O preço de venda foi atualizado, preço atual: " + this.precoVenda); 
	}

	public void vender(int quantidade){
		if(this.receitaObrigatoria)
			System.out.println("Medicamento só pode ser vendido com a receita");
		else{
			if(this.qtdEstoque >= quantidade){
				this.qtdEstoque -= quantidade;
				System.out.println("A venda foi realizada");
				System.out.println("Estoque atual: " + this.qtdEstoque);
			}else{
				System.out.println("Desculpe, estoque insuficiente");
			}
		}
	}
	
	public void comprar(int quantidade){
		this.qtdEstoque += quantidade;
		System.out.println("Estoque atualizado");
		System.out.println("Estoque atual: " + this.qtdEstoque);
	}

	public void mostrar(){
		System.out.println("Nome: " + this.nome);
		System.out.println("Preço: " + this.precoVenda);
		System.out.println("Validade: " + this.dataValidade.formata());
		System.out.println("Laboratorio: " + this.laboratorio.formata());
		System.out.println("Requer receita: " + this.receitaObrigatoria);
		System.out.println("Estoque: " + this.qtdEstoque);
	}
}
