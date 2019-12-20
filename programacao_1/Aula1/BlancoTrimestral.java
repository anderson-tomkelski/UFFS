public class BlancoTrimestral{
	public static void main(String args[]){
		float gastosTrimestre;
		float janeiro = 15000;
		float fevereiro = 23000;
		float marco = 17000;
		float mediaMensal = (janeiro + fevereiro + marco)/3;
		boolean gastoControlado = false;
		gastosTrimestre = janeiro + fevereiro + marco;
		System.out.println("O gasto total e' " + gastosTrimestre);
		System.out.println("A media e'" + mediaMensal);
		gastoControlado = mediaMensal < 30000.0;
		System.out.println("Verificacao: O gasto esta controlado? " + gastoControlado);
	}
}
