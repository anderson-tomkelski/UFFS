class Principal{
    public static void main(String[] args){
	Matematica mat = new Matematica();
	try {
	    System.out.println("Soma: " + mat.somar(2, -2));
	} catch (ParamZeroException e){
	    System.out.println(e.getMessage());
	}
    }
}







