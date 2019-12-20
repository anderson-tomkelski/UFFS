class Laboratorio{
	String nome;
	String razao;
	String cnpj;
	String endereco;
	String telefone;
	
	public String formata(){
		String concat = "Nome: " + this.nome + "razao: " + this.razao + "cnpj: " + this.cnpj + "endereço: " + this.endereco;
		return concat; 
	}
}
