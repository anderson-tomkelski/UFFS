class Programa{
	public static void main(String[] args){
		Aluno a1 = new Aluno("Anderson", 13);
		a1.totalDeAlunos++;
		
		Aluno a2 = new Aluno("Altair", 15);
		a2.totalDeAlunos++;
		
		System.out.println("Total em a1: " + a1.totalDeAlunos);
		System.out.println("Total em a2: " + a2.totalDeAlunos);
	}
}