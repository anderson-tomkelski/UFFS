import java.util.Scanner;

public class Analista extends Empregado {

    @Override
    public double definirBeneficios(double total){
        double economia = 0.0;
        Scanner scan = new Scanner(System.in);
        System.out.println("Entre com o valor economizado no projeto: ");
        economia = scan.nextDouble();
        total += (0.10 * economia);
        return total;
    }
}
