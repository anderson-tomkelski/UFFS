class News extends Post{
    private String source;


    public void setSource(String source){
	this.source = source;
    }
    
    public void show(){
	super.show();
	System.out.println("Fontes: " + this.source);
    }
}
