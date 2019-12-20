import java.util.Scanner;
public class ExemploScanner {
	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);
		char x;
		System.out.println("Qual valor de x? ");
		x = sc.nextLine().charAt(0);
		System.out.println(x);
		sc.nextLine(); //Para Esvaziar o buffer
	}
}
