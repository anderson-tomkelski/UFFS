
public class Sistema {
	public static void main(String[] args) {
		ProfessorDaFaculdade p = new ProfessorDaFaculdade("Anderson", 5000, 40);
		EmpregadoDaFaculdade f = new EmpregadoDaFaculdade("Jorge", 2000);
		
		GeradorDeRelatorio.add(p);
		GeradorDeRelatorio.add(f);
	}
}
