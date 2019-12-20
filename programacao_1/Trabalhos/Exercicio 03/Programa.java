class Programa{
	public static void main(String[] args){
		Data d = new Data();
		d.dia=30;
		d.mes=01;
		d.ano=2017;

		Laboratorio lab = new Laboratorio();
		lab.nome = "Colins";
		lab.razao = "...";
		lab.cnpj = "123.436.12313425.2143235";
		lab.endereco = "Rua tal, bairro outro";
		lab.telefone = "49 98822-1234";

		Medicamento remedio = new Medicamento();
		remedio.nome = "Paracetamol";
		remedio.precoVenda = 10.00;
		remedio.dataValidade = d;
		remedio.laboratorio = lab;
		remedio.receitaObrigatoria = false;
		remedio.qtdEstoque = 10;

		remedio.mostrar();
		remedio.vender(3);
		remedio.mostrar();
		remedio.comprar(4);
		remedio.mostrar();
		remedio.reajustarPrecoVenda(100);
		remedio.mostrar();
	}
}
