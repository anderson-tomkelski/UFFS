import java.awt.Color;
class Programa{	
	public static void imprimir(Conta c){
		System.out.println("Titular " + c.getDono());
		System.out.println("Numero "  + c.getNumero());
		System.out.println("Saldo "   + c.getSaldo());
	}

	public static void verificar(boolean sacou, Conta c){
		if (sacou)
			System.out.println("Valor restante: " + c.getSaldo());
		else
			System.out.println("Saldo insuficiente!\nSaldo atual: " + c.getSaldo());
	}

	public static void main(String[] args){
		Conta c1 = new Conta();
		
		c1.setDono("Anderson");
		c1.setNumero(123);
		c1.setSaldo(0.0);

		imprimir(c1);

		boolean sacou=c1.sacar(100.0);
		verificar(sacou, c1);
		
		c1.depositar(5000);
		sacou=c1.sacar(100.0);
		verificar(sacou, c1);

		imprimir(c1);
	}
}
