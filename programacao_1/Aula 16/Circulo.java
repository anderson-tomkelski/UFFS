import java.lang.Math;
class Circulo implements AreaCalculavel{
	public double raio;
	public Circulo(double raio){
		this.raio = raio;
	}

	public double calculaArea(){
		return 2 * Math.PI * this.raio;
	}
}