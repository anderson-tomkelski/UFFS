class Teste{
	public static void main(String[] args){
		Agenda agenda = new Agenda();
		
		Nota n1 = new Nota(19,4,2017,"Corrigir trabalho");
		agenda.incluir(n1);
		
		n1 = new Nota(25,12,2017, "Natal");
		agenda.incluir(n1);
		
		n1 = new Nota(20,04,2017, "Lavar o carro");
		agenda.incluir(n1);
		
		agenda.listar();
		
		//agenda.remover(agenda.buscar("Lavar o carro"));
		agenda.remover("Natal");
		agenda.listar();
	}
}
