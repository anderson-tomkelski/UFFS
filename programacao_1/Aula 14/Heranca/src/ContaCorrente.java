public class ContaCorrente extends Conta {
	
	public ContaCorrente(double saldo, String codigo, Pessoa titular){
		super(codigo, titular);
		this.depositar(saldo);
	}
	
	@Override
	public boolean sacar(double valor){
		if(valor <=0){
			System.out.println("Valor Inválido");
			return false;
		}
		if(this.saldo>valor){
			this.saldo-=valor;
			System.out.println("\n\tDébito na Conta: "+this.codigo+"\n\tValor: "+valor+"\n\tSaldo final: "+ this.saldo+"\n");
			this.taxa(1.0);
			return true;
		} else{
			System.out.println("\n\t\tValor selecionado maior que o saldo da conta!\n");
			return false;
		}
	}
	
	@Override
	public boolean depositar(double valor){
		if(valor <=0){
			System.out.println("Valor Inválido");
			return false;
		}else{
			this.saldo+=valor;
			System.out.println("\n\tConta: "+this.codigo+"\n\tValor: "+valor+"\n\tSaldo final: "+ this.saldo+"\n");
			this.taxa(1.0);
			return true;
		}
	}
	
	@Override
	public void transferirPara(Conta c, double valor){
		if(this.sacar(valor)){
			c.depositar(valor);
			this.taxa(4.0);
		}
	}
	
	public void taxa(double valor){
		this.saldo-=valor;
	}
	
	@Override
	public void consultarSaldo(){
		System.out.println("Saldo da conta: " + this.codigo + " = " + this.saldo);
	}
	
	@Override
	public String toString(){
		return "Conta Corrente\n" + super.toString();
	}
}