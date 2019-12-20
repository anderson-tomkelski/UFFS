class Conta{
	private int numero;
	private String dono;
	private double saldo;
	
	public Conta(int numero, String dono, double saldo){
		this.numero = numero;
		this.dono = dono;
		this.saldo = saldo;
	}

	public void setNumero(int numero){
		this.numero = numero;
	}

	public void setDono(String dono){
		this.dono = dono;	
	}	

	public double getSaldo(){
		return this.saldo;
	}

	public boolean sacar(double valorSaque){
		if(this.saldo >= valorSaque){
			this.saldo = this.saldo - valorSaque;
			return true;
		} else{
			return false;
		}
	}

	public void depositar(double valorDeposita){
		this.saldo += valorDeposita;
	}
	
	public boolean transferir(double valor, Conta contaDestino){
		if(this.saldo >= valor){
			this.saldo = this.saldo - valor;
			contaDestino.saldo = contaDestino.saldo + valor;
			return true;
		} else{
			return false;
		}
	}
	
	public void dadosConta(){
		System.out.println("Numero da conta: " + this.numero);
		System.out.println("Titular da conta: " + this.dono);
	}
}