import java.util.Scanner;

public class Lista{
	public static void main(String[] args){
		Scanner le = new Scanner(System.in);
		int[] lista;
		int i, maior, menor, soma=0;
		System.out.println("Digite o tamanho do array");
		i=le.nextInt();
		lista = new int[i];

		for(i=0;i<lista.length; i++){
			System.out.println("Digite um numero para posicao " + i);
			lista[i] = le.nextInt();
		}
		maior = lista[0];
		menor = lista[0];
		for(i=0; i<lista.length; i++){
			if(lista[i] > maior)
				maior = lista[i];
			if(lista[i] < menor)
				menor = lista[i];
			soma+=lista[i];
		}
		for(i=0; i<lista.length; i++){
			System.out.print(lista[i]);
			if(lista[i] == maior)
				System.out.println("< maior");
			else if(lista[i] == menor)
				System.out.println("< menor");
			else
				System.out.print("\n");
		}
		System.out.print("Soma: " + soma);
			
	}
}
