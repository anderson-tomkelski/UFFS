public class ProfessorDaFaculdade extends EmpregadoDaFaculdade{
	private int horasDeAula;
	
	public ProfessorDaFaculdade(String nome, double salario, int horasDeAula){
		super(nome, salario);
		setHorasDeAula(horasDeAula);
	}
	
	public double getGastos(){
		return super.getSalario() + this.getHorasDeAula()*10;
	}
	
	public int getHorasDeAula(){
		return this.horasDeAula;
	}
	
	public void setHorasDeAula(int horasDeAula){
		this.horasDeAula = horasDeAula;
	}
	
	public String getInfo(){
		return "nome: " + super.getNome() + " com salário: " + super.getSalario() 
				+ " e " + this.getHorasDeAula() + " horas de aula";
	}
}
