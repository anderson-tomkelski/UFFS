class Conta{
	int numero;
	String dono;
	double saldo;

	public double saldo(){
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
