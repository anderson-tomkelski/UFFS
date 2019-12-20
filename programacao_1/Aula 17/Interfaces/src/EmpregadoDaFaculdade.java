public class EmpregadoDaFaculdade {
	private String nome;
	private double salario;
	
	public EmpregadoDaFaculdade(String nome, double salario){
		setNome(nome);
		setSalario(salario);
	}
	
	public double getGastos(){
		return this.salario;
	}
	
	public String getInfo(){
		return "nome: " + this.nome + " com salário: " + this.salario;
	}
	
	public String getNome(){
		return this.nome;
	}
	
	public void setNome(String nome){
		this.nome = nome;
	}
	
	public double getSalario(){
		return this.salario;
	}
	
	public void setSalario(double salario){
		this.salario = salario;
	}
}
