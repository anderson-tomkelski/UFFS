import java.util.ArrayList;

public class Principal {

	public static void main(String[] args) {
		ArrayList<Pet> lista = new ArrayList<Pet>();
		
		Gato g = new Gato("Gato1", 1);
		lista.add(g);
		g = new Gato("Gato2", 2);
		lista.add(g);
		g = new Gato("Gato3", 3);
		lista.add(g);
		
		Cachorro c = new Cachorro("Cao1", 1);
		lista.add(c);
		c = new Cachorro("Cao2", 2);
		lista.add(c);
		c = new Cachorro("Cao3", 3);
		lista.add(c);
		
		for(Pet p : lista){
			if(p instanceof Gato){
				Gato g1 = (Gato)p;
				g1.arranhar();
			}
			if(p instanceof Cachorro){
				Cachorro c1 = (Cachorro)p;
				c1.cavar();
			}
		}
		
	}
}
