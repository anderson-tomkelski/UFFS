public abstract class Conta {
	protected double saldo;
	protected String codigo;
	protected Pessoa titular;
	
	public Conta(String codigo, Pessoa titular){
		this.codigo = codigo;
		this.titular = titular;
	}
	
	public abstract boolean sacar(double valor);
	public abstract boolean depositar(double valor);
	public abstract void transferirPara(Conta c, double valor);
	public abstract void consultarSaldo();
	public String toString(){
		return "Titular \n" + this.titular + "\nCódigo: " + this.codigo + "\nSaldo: " + this.saldo;
	}
}