class Programa{
	public static void main(String[] args){
		Bhaskara i = new Bhaskara(1, 4, 0);
		Raizes c = new Raizes();
	
		c = i.Bhaskara();
		i.imprimeRaizes(c);
	}
}
