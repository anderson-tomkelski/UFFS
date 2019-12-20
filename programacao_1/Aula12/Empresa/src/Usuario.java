public class Usuario extends Pessoa{
	private int senha;
	private String email;
	
	public Usuario(String nome, int idade, int senha, String email){
		super(nome, idade);
		this.senha = senha;
		this.email = email;
	}
	
	@Override
	public String toString(){
		return super.toString() + " Email: " + this.email;
	}
	
	public boolean acessar(String email, int senha){
		if(this.email==email && this.senha==senha){
			System.out.println("Acesso permitido!");
			return true;
		}
		else{
			System.out.println("Email ou senha incorreto");
			return false;
		}
	}
}
