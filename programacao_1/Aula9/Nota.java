class Nota{
	Data data;
	String info;
	
	public Nota(int dia, int mes, int ano, String infoNota){
		this.data = new Data(dia, mes, ano);
		this.info = infoNota;
	}

	public String toString(){
		return "\nData: " + this.data +"\nLembrar: " + this.info;
	}
}
