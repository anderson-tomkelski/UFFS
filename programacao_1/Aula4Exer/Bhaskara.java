class Bhaskara{
	int a;
	int b;
	int c;
	public Bhaskara(int d, int e, int f){
		this.a = d;
		this.b = e;
		this.c = f;
	}
	public Raizes Bhaskara(){
		Raizes r = new Raizes();		
		double delta = (this.b*this.b) - 4*this.a*this.c;
		r.numa = -this.b+Math.sqrt(delta)/2*this.a;
		r.numb = -this.b-Math.sqrt(delta)/2*this.a;
		return r;
	}
	public void imprimeRaizes(Raizes r){
		System.out.println("Raiz 1: " + r.numa);
		System.out.println("Raiz 2: " + r.numb);
	}
		
}
