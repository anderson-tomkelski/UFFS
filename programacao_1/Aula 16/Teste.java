class Teste{
	public static void main(String[] args){
		AreaCalculavel quadrado = new Quadrado(5);
		AreaCalculavel retangulo = new Retangulo(5, 7);
		AreaCalculavel circulo = new Circulo(4);

		System.out.println("Area quadrado = " + quadrado.calculaArea());
		System.out.println("Area circulo = " + circulo.calculaArea());
		System.out.println("Area retangulo = " + retangulo.calculaArea());
	}
}
