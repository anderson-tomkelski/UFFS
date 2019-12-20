class Funcionario{
	static int numeroFuncionarios = 0;
	double salario;
	String nome;
	String cpf;
	String funcao;
	String telefone;
	Endereco endereco;

	public Funcionario(String nomeFunc, String cpfFunc, Endereco enderecoFunc, String telefoneFunc, String FuncaoFunc, double salarioInicial){
		this.nome = nomeFunc;
		this.cpf = cpfFunc;
		this.endereco = enderecoFunc;
		this.telefone = telefoneFunc;
		this.funcao = FuncaoFunc;
		this.salario = salarioInicial;
	}

	public String toString(){
		return "Nome: " + this.nome + "\nCPF: " + this.cpf + this.endereco + "\nTelefone: " + this.telefone + "\nFunção: " + this.funcao + "\nSalário: " + this.salario;
	}
}
