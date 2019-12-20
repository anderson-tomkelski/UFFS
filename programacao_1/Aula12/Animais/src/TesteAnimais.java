public class TesteAnimais {
	public static void main(String[] args) {
		Animal camelo = new Animal("Camelo", "Amarelo", "Terra", 150, 4, 2);
		Peixe tubarao = new Peixe("TuTubarão", "Cinzento", "Mar", 300, 0, (float) 1.5, "Barbatanas e cauda");
		Mamifero ursoCanadense = new Mamifero("Urso-do-Canadá", "Vermelho", "Terra", 180, 4, (float) 0.5, "Mel");
		
		System.out.println("Zoo:");
		System.out.println("------------------------------");
		camelo.dados();
		System.out.println("------------------------------");
		tubarao.dados();
		System.out.println("------------------------------");
		ursoCanadense.dados();
		System.out.println("------------------------------");
	}

}
