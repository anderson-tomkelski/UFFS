class Retangulo implements AreaCalculavel{
	public double base;
	public double altura;
	public Retangulo(double base, double altura){
		this.base = base;
		this.altura = altura;
	}
	
	public double calculaArea(){
		return this.base * this.altura;
	}
}
