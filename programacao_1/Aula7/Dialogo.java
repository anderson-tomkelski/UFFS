import javax.swing.JOptionPane;

public class Dialogo{
	public static void main(String[] args){
		String nome = JOptionPane.showInputDialog("Que é o seu nome?");
		JOptionPane.showMessageDialog(null, "Olá " + nome + "!");
	}
}
