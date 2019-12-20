public class ContaPoupanca extends Conta {
	
	public ContaPoupanca(double saldo, String codigo, Pessoa titular){
		super(codigo, titular);
		this.depositar(saldo);
	}
	
	@Override
	public boolean sacar(double valor){
		if(valor > 800)
			this.taxa(5.0);
		
		if(valor <=0){
			System.out.println("Valor Inválido");
			return false;
		}else{
			this.saldo = this.saldo - valor;
			System.out.println("\n\tDébito na Conta: "+this.codigo+"\n\tValor: "+valor+"\n\tSaldo final: "+ this.saldo+"\n");
			return true;
		}
	}
	
	@Override
	public boolean depositar(double valor){
		if(valor <=0){
			System.out.println("Valor Inválido");
			return false;
		}else{
			this.saldo+=valor;
			System.out.println("\n\tCrédito na Conta: "+this.codigo+"\n\tValor: "+valor+"\n\tSaldo final: "+ this.saldo+"\n");
			return true;
		}
	}
	
	@Override
	public void transferirPara(Conta CD, double valor){
		System.out.println("MERDA" + CD);
		if(this.sacar(valor)){
			CD.depositar(valor);
		}
	}
	
	public void atualiza(double taxa){
		if(taxa >= 1){
			taxa = taxa/100;
			this.saldo += this.saldo * taxa;
		} else
			this.saldo += this.saldo * taxa;
	}
	
	public void taxa(double taxa){
		this.saldo-=taxa;
	}
	
	@Override
	public void consultarSaldo(){
		System.out.println("Saldo da conta: " + this.codigo + " = " + this.saldo);
	}
	
	@Override
	public String toString(){
		return "Conta Poupança\n" + super.toString();
	}
	
}