import java.util.*;
class Principal{
	public static void main(String[] args){
		Blog meuBlog = new Blog();

		Scanner sc = new Scanner(System.in);
		ArrayList<Post> posts = new ArrayList<Post>();
		Post newPost = null;
		int opc;
		int index;
		do{
		    opc = Menu();
		    switch(opc){
		    case 1:
			System.out.print("\033[H\033[2J");
			newPost = new News();
			meuBlog.readData(newPost);
			posts.add(newPost);
			break;
		    case 2:
			System.out.print("\033[H\033[2J");
			newPost = new ProductReview();
			meuBlog.readData(newPost);
			posts.add(newPost);
			break;
		    case 3:
			System.out.print("\033[H\033[2J");
			newPost = new Post();
			meuBlog.readData(newPost);
			posts.add(newPost);
			break;
		    case 4:
			System.out.print("\033[H\033[2J");
			meuBlog.showAll(posts);
			break;
		    case 5:
			System.out.print("\033[H\033[2J");
			System.out.println("Digite o código do post que deseja dar \"like\": ");
			index = sc.nextInt();
			if(index > posts.size() - 1)
			    System.out.println("Post inexistente");
			else{
			    newPost = posts.get(index);
			    newPost.like();
			}
			break;
		    case 6:
			System.out.print("\033[H\033[2J");
			System.out.println("Digite o código do post que deseja dar \"Dislike\": ");
			index = sc.nextInt();
			if(index > posts.size() - 1)
			    System.out.println("Post inexistente");
			else{
			    newPost = posts.get(index);
			    newPost.dislike();
			}
			break;
		    case 10:
			System.out.print("\033[H\033[2J");
			System.out.println("Saindo");
			break;
		    default:
			System.out.println("Opção digitada inválida, por favor escolha novamente: ");
		    }
		}while(opc != 10);
	}

	public static int Menu(){
	Scanner sc = new Scanner(System.in);
	System.out.println("BLOG: O que voce quer fazer? ");
	System.out.println("1 - Novo post de noticia");
	System.out.println("2 - Nova resenha de produto");
	System.out.println("3 - Novo post de outros assuntos");
	System.out.println("4 - Listar todas as postagens");
	System.out.println("5 - Curtir uma postagem");
	System.out.println("6 - Nao curtir uma postagem");
	System.out.println("10 - Sair");
	System.out.println("Escolha a opção: ");

	return sc.nextInt();

    }
}
