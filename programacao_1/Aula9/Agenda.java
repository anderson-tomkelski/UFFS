import java.util.*;

class Agenda{
	List<Nota> notas;
	
	public Agenda(){
		notas = new ArrayList<>();
	}

	public void incluir(Nota n){
		this.notas.add(n);
	}

	public boolean remover(int posicao){
		if(posicao < 0 || posicao>=this.notas.size()){
			System.out.println("Posição inválida");			
			return false;
		}else{
			this.notas.remove(posicao);
			return true;
		}
	}

	public int buscar(String info){
		int indice = -1;
		for(Nota n : this.notas){
			if(n.info.equals(info)){
				indice=this.notas.indexOf(n);
				System.out.println("A nota buscada está na posição " + indice);
				break;
			}
		}
		return indice;
	}

	public boolean remover(String info){
		if(this.remover(this.buscar(info)))
			return true;
		else
			return false;
	}

	public void listar(){
		System.out.println("\n\tSuas anotações:");
		for(Nota n : this.notas){
			System.out.println(n);
		}
	}
}
