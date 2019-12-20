class Endereco{
	String rua;
	String bairro;
	String cidade;
	int numeroCasa;

	public Endereco(String enderecoRua, String enderecoBairro, String enderecoCidade, int enderecoNumero){
		this.rua = enderecoRua;
		this.bairro = enderecoBairro;
		this.cidade = enderecoCidade;
		this.numeroCasa = enderecoNumero;
	}
	
	public String toString(){
		return "\nRua: " + this.rua + "\nBairro: " + this.bairro + "\nCidade: " + this.cidade + "\nNumero: " + this.numeroCasa;
	}
}
