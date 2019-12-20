class Tweet{
	private String autor;
	private String mensagem;
	protected int data;
	public String hash;
	
	public void setAutor(String autor){
		this.autor = autor;
	}

	public String getAutor(){
		return this.autor;
	}

	public void setMensagem(String msg){
		this.mensagem = msg;
	}

	public String getMensagem(){
		return this.mensagem;
	}

	public void setData(int data){
		this.data = data;
	}

	public int getData(){
		return this.data;
	}

	
	public void retweet(){
		System.out.println("\nRT - Autor: " + getAutor() + "\nRT - Data: " + getData() + "\nRT - Mensagem: " + getMensagem() + "\nRT - Hash: " + this.hash);
	}
}
