import java.util.Scanner;

public class Gerente extends Empregado implements VisualizadorProjetos{
    @Override
    public double definirBeneficios(double total){
	double bonus = 0.0;
	Scanner scan = new Scanner(System.in);
	System.out.println("Entre com o valor do bônus: ");
	bonus = scan.nextDouble();
	total += bonus;
	return total;
    }
    
    @Override
    public void listarProjetos(){
	
    }

}
