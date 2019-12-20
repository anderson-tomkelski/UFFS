class Principal{
	public static void main(String[] args){
		float f = -4.85f;
		System.out.println(f);
		Material m1;
		Material m2 = new Material(1, "NOME2", 5);
		m1 = m2;
		System.out.println(m1.setNome("Nome1"));
		m1.mostrar();
		m2.mostrar();
		Material.abastecer(10);
		m1.mostrar();
		
	}
}
