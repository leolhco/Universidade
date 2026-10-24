public class Normal extends Ingresso {

    public Normal(double valor) {
        super(valor);
    }

    @Override
    public void escreveValor() {
        System.out.println("Ingresso Normal. Valor: R$ " + valor);
    }
}
