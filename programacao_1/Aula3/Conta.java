class Conta{
	private int numero;
	private String dono;
	private double saldo;

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
		System.out.println("Novo Saldo: " + this.saldo);
	}

	public void setNumero(int novoNumero){
		numero = novoNumero;
	}
	
	public int getNumero(){
		return numero;
	}
	
	public void setDono(String novoDono){
		dono = novoDono;
	}

	public String getDono(){
		return dono;
	}

	public void setSaldo(double novoSaldo){
		saldo = novoSaldo;
	}
	
	public double getSaldo(){
		return saldo;
	}
}
