class Programa{
	public static void main(String[] args){
		Aluno aa = new Aluno("Anderson", 123);
	
		Disciplina d1=new Disciplina(4, 12345, "Programação I");
		
		aa.matricular(d1);

		d1=new Disciplina(4, 12547, "ED II");
		aa.matricular(d1);
		
		Disciplina d2=new Disciplina(2, 12548, "Algebra Linear");
		aa.matricular(d2);

		d2=new Disciplina(6, 12549, "Calculo Diferencial Integral I");
		aa.matricular(d2);

		aa.listarDisciplinas();
		System.out.println(aa);
		aa.disciplinas[0].encerrar();
		aa.listarDisciplinas();

		d2.Disciplina();

	}
}
