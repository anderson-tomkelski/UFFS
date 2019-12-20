class Matematica{
    private double resultado;
    
    public double somar(double a, double b){
	if(checaParam(a, b))
	    this.resultado = a+b;
	if(checaOperacao(this.resultado))
	    return resultado;
    }
    public double subtrair(double a, double b){
	if(checaParam(a, b))
	    this.resultado = a-b;
	if(checaOperacao(this.resultado))
	    return resultado;
    }
    public double multiplicar(double a, double b){
	if(checaParam(a, b))
	    this.resultado = a*b;
	if(checaOperacao(this.resultado))
	    return resultado;
    }
    public double dividir(double a, double b){
	if(checaParam(a, b))
	    this.resultado = a/b;
	if(checaOperacao(this.resultado))
	    return resultado;
    }

    private boolean checaParam(double a, double b){
	if(a == 0 || b == 0){
	    throw new ParamZeroException("Valor para operação não pode ser igual a zero");
	    return false;
	} else
	    return true;
    }
    private boolean checaOperacao(double resultado){
	if(resultado == 0){
	    throw new ResultadoZeroException("Resultado é igual a zero");
	    return false;
	}else
	    return true;
    }
}
