class Disciplina{
	int creditos;
	int codigo;
	String nome;
	boolean concluida=false;

	public Disciplina(){
	}
	public Disciplina(int creditosA, int codigoA, String nomeA){
		this.creditos=creditosA;
		this.codigo=codigoA;
		this.nome=nomeA;
	}

	public String toString(){
		String con=(this.concluida)?"Disciplina Concluída.":"Em andamento";
		return "\nDisciplina: " + this.nome + "\nCódigo: " + this.codigo 
			+ "\nCréditos: " + this.creditos + "\n"+con+"\n";
	}

	public void encerrar(){
		this.concluida=true;
	}
}