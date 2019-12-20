class Empresa{
	String nome;
	String cnpj;
	Funcionario[] bodegueiros = new Funcionario[10];
	Cliente[] clientes = new Cliente[100];
	Bebida[] bebidas = new Bebida[100];

	public Empresa(String nomeEmpresa, String cnpjEmpresa){
		this.nome = nomeEmpresa;
		this.cnpj = cnpjEmpresa;
	}

	public void contratar(Funcionario novoFuncionario){
		this.bodegueiros[novoFuncionario.numeroFuncionarios] = novoFuncionario;
		novoFuncionario.numeroFuncionarios++;
	}

	public void demitir(int codigo){
		int i=codigo;
		while(i<this.bodegueiros.length && this.bodegueiros[i+1] != null){
			Funcionario aux = this.bodegueiros[i+1];
			this.bodegueiros[i] = aux;
			i++;
		}
		this.bodegueiros[i] = null;
	}	

	public void aumentar(int codigo, double percentual){
		this.bodegueiros[codigo].salario += ((percentual/100)*this.bodegueiros[codigo].salario);
	}

	public static int procurarFuncionario(Empresa empresa, String nome){
		for(int i=0; i<empresa.bodegueiros.length; i++){
			if(empresa.bodegueiros[i] != null && nome.equals(empresa.bodegueiros[i].nome))
				return i;
		}
		return -1;
	}

	public void imprimirFuncionarios(){
		for(int i=0; i<this.bodegueiros.length; i++){
			Funcionario pessoa = this.bodegueiros[i];
			if(pessoa == null)
				break;
			System.out.println("Ordem do funcionário [" + i + "]: " + pessoa);
			System.out.println("----------------------------------------------");
		}
	}

	public void inserirCliente(Cliente novoCliente){
		this.clientes[novoCliente.clientes] = novoCliente;
		novoCliente.clientes++;
	}

	public static int procurarCliente(Empresa empresa, String nome){
		for(int i=0; i<empresa.clientes.length; i++){
			if(empresa.clientes[i] != null && nome.equals(empresa.clientes[i].nome))
				return i;
		}
		return -1;
	}

	public void excluirCliente(int codigo){
		int i=codigo;
		while(i<this.clientes.length && this.clientes[i+1] != null){
			Cliente aux = this.clientes[i+1];
			this.clientes[i] = aux;
			i++;
		}
		this.clientes[i] = null;	
	}
	
	public void imprimirClientes(){
		for(int i=0; i<this.clientes.length; i++){
			Cliente pessoa = this.clientes[i];
			if(pessoa == null)
				break;
			System.out.println(pessoa);
			System.out.println("----------------------------------------------");
		}
	}

	public void inserirBebida(Bebida novaBebida){
		this.bebidas[novaBebida.numeroDeBebidas] = novaBebida;
		novaBebida.numeroDeBebidas++;
	}

	public static int procurarBebida(Empresa empresa, String nome){
		for(int i=0; i<empresa.bebidas.length; i++){
			if(empresa.bebidas[i] != null && nome.equals(empresa.bebidas[i].nome))
				return i;
		}
		return -1;
	}
	
	public static Bebida procurarBebidaCompraVenda(Empresa empresa, String nome){
		for(int i=0; i<empresa.bebidas.length; i++){
			if(empresa.bebidas[i] != null && nome.equals(empresa.bebidas[i].nome))
				return empresa.bebidas[i];
		}
		return null;
	}

	public void excluirBebida(int codigo){
		int i=codigo;
		while(i<this.bebidas.length && this.bebidas[i+1] != null){
			Bebida aux = this.bebidas[i+1];
			this.bebidas[i] = aux;
			i++;
		}
		this.bebidas[i] = null;	
	}

	public void imprimirBebidas(){
		for(int i=0; i<this.bebidas.length; i++){
			Bebida bebida = this.bebidas[i];
			if(bebida == null)
				break;
			System.out.println(bebida);
			System.out.println("----------------------------------------------");
		}
	}
}
