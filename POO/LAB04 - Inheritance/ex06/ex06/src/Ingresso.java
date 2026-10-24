public class Ingresso {
    protected double valor;

    public Ingresso(double valor) {
        this.valor = valor;
    }

    public void escreveValor() {
        System.out.println("Valor do ingresso: R$ " + valor);
    }

    public double getValor() {
        return valor;
    }
}
