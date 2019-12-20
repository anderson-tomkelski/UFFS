import java.util.*;
class Blog{
    public void showAll(ArrayList<Post> lista){
	for(Post p : lista){
	    if(p instanceof News){
		News n = (News)p;
		n.show();
	    }else if(p instanceof ProductReview){
		ProductReview pr = (ProductReview)p;
		pr.show();
	    }else
		p.show();
	}
    }

    public void readData(Post p){
	Scanner sc = new Scanner(System.in);
	String title;
	String content;
	System.out.println("Digite o titulo do post: ");
	title = sc.nextLine();
	System.out.println("Digite o conteudo do post: ");
	content = sc.nextLine();
	if(p instanceof News){
	    System.out.println("Digite a fonte da noticia: ");
	    String source = sc.nextLine();
	    News news = (News)p;
	    news.setTitle(title);
	    news.setContent(content);
	    news.setSource(source);
	}else if(p instanceof ProductReview){
	    ProductReview product = (ProductReview)p;
	    System.out.println("Digite o nome da marca: ");
	    String brand = sc.nextLine();
	    int stars;
	    do{
		System.out.println("Digite a quantidade de estrelas: ");
		stars = sc.nextInt();
		if(stars < 0 || stars > 10)
		    System.out.println("Quantidade de estrelas inválida, favor, avalie com um valor entre 0 e 10");
	    }while(stars < 0 || stars > 10);
	    product.setTitle(title);
	    product.setContent(content);
	    product.setBrand(brand);
	    product.evaluate(stars);
	}else{
	    p.setTitle(title);
	    p.setContent(content);
	}
    }
}
