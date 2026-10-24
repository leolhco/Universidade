public class Operario extends Funcionario {
    private double valorPorProducao;
    private int quantidadeProduzida;

    public Operario(String nome, String dataNascimento, double valorPorProducao, int quantidadeProduzida) {
        super(nome, dataNascimento);
        this.valorPorProducao = valorPorProducao;
        this.quantidadeProduzida = quantidadeProduzida;
    }

    @Override
    public double calcularSalario() {
        return valorPorProducao * quantidadeProduzida;
    }
}
