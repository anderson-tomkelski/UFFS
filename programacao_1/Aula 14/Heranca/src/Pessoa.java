public class Pessoa {
	private String nome;
	private String cpf;
	
	public Pessoa(String nome, String cpf){
		this.setNome(nome);
		this.setCpf(cpf);
	}

	public void setNome(String nome) {
		if(nome != "")
			this.nome = nome;
	}
	
	public String getNome(){
		return this.nome;
	}

	public void setCpf(String cpf) {
		if(cpf != "")
		this.cpf = cpf;
	}
	

	public String toString() {
		return "Nome: " + this.nome + "\nCPF: "+ this.cpf;
	}	
}