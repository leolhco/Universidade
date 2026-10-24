public class VIP extends Ingresso {
    private double valorAdicional;

    public VIP(double valor, double valorAdicional) {
        super(valor);
        this.valorAdicional = valorAdicional;
    }

    public double valorVIP() {
        return valor + valorAdicional;
    }

    @Override
    public void escreveValor() {
        System.out.println("Valor do ingresso VIP: R$ " + valorVIP());
    }
}
