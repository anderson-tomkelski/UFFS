public class Empresa{
    Empregado[] emps = new Empregado[10];
    int n = 0;
    
    public void registrar(Empregado emp){
	emps[n] = emp;
	n++;
    }
}
