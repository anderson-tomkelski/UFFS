public class Principal {
	public static void main(String[] args) {
		Pai p = new Filha();
		
		p.m1();
		p.m2();
		
		//p.m3();
		if(p instanceof Filha){
			Filha f = (Filha) p;
			f.m1();
			f.m2();
			f.m3();
		}
	}

}
