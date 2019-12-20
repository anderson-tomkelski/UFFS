import java.util.*;
class Povo{
	List<Pessoa> pessoas = new ArrayList<>();
	
	public void adicionar(Pessoa pessoa){
		this.pessoas.add(pessoa);
	}

	public void listar(){
		System.out.println("\n\tLista de pessoas:");
		for(Pessoa n : pessoas){
			System.out.println(n);
		}
	}
}
