public class CamaroteSuperior extends VIP {
    public CamaroteSuperior(double valor, double valorAdicional) {
        super(valor, valorAdicional);
    }

    @Override
    public void escreveValor() {
        System.out.println("Valor do ingresso Camarote Superior: R$ " + valorVIP());
    }
}
