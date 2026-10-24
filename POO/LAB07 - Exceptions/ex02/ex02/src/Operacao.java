public class Operacao {

    public void iniciarOperacao(int numerador, int denominador){
        try{
             calcular(numerador, denominador);
        } catch (DivisaoPorZeroException e) {
            System.out.println(e.getMessage());
        }
    }

    public void calcular(int numerador, int denominador) throws DivisaoPorZeroException {
        dividir(numerador, denominador);
    }

    public void dividir(int numerador, int denominador) throws DivisaoPorZeroException {
        if (denominador == 0) throw new DivisaoPorZeroException("ERRO! NAO EXISTE DIVISAO POR 0");
        int resultado = numerador / denominador;
        System.out.println(resultado);
    }

}