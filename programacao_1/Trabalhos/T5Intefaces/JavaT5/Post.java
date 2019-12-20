import java.util.*;
import java.text.*;
class Post{
    private String title;
    private Date date = new Date();
    private String content;
    private int likes;
    private int dislikes;

    public void setTitle(String title){
	this.title = title;
    }

    public void setContent(String content){
	this.content = content;
    }

    public void setLikes(int likes){
	this.likes = likes;
    }

    public void setDislikes(int dislikes){
	this.dislikes = dislikes;
    }

    public String getDate(){
	Properties ps = System.getProperties();
	Locale local = new Locale((String)ps.get("user.language"), (String)ps.get("user.country"));
	DateFormat df = DateFormat.getDateInstance(DateFormat.MEDIUM, local);
	return df.format(this.date);
    }

    public void show(){
	System.out.println("Título: " + this.title + " - Data: " + this.getDate() + " - Conteúdo: " + this.content
			   + " - Likes: " + this.likes + " - Dislikes " + this.dislikes);
    }

    public void like(){
	this.likes++;
    }

    public void dislike(){
	this.dislikes++;
    }
}
