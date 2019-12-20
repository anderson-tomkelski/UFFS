class ProductReview extends Post implements Evaluable{
    private String brand;
    private int stars;


    public void setBrand(String brand){
	this.brand = brand;
    }
    
    public void show(){
	super.show();
	System.out.println("Marca: " + this.brand + " - Stars: " + this.stars);
    }

    public void evaluate(int value){
	this.stars = value;
    }
}
