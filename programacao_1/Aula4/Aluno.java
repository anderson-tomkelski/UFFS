class Aluno{
	int matricula;
	String nome;
	Disciplina[] disciplinas = new Disciplina[4];
	int qtdD=0;

	public Aluno(String nomeA, int matriculaA){
		this.nome = nomeA;
		this.matricula = matriculaA;
	}

	public void matricular(Disciplina d){
		this.disciplinas[this.qtdD]=d;
		this.qtdD++;
	}
	
	public String toString(){
		return "\nNome: " + this.nome + "\nMatrícula: " 
		       + this.matricula + "\nDisciplinas: " + this.qtdD + "\n";
	}

	public void listarDisciplinas(){
		for(Disciplina d: this.disciplinas){
			System.out.println(d);
		}
	}
}
