class Cliente{
	String nome;
	String cpf;
	boolean fiado;
	static int clientes=0;

	public Cliente(String nomeCliente, String cpfCliente, boolean podeFiado){
		this.nome = nomeCliente;
		this.cpf = cpfCliente;
		this.fiado = podeFiado;
	}

	public String toString(){
		return "Nome: " + this.nome + "\nCPF: " + this.cpf + "\nCliente: " + (this.fiado ? "Confiável" : "Não confiável");
	}
}
