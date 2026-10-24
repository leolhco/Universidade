public class Horista extends Funcionario {
    private double valorPorHora;
    private int totalHorasTrabalhadas;

    public Horista(String nome, String dataNascimento, double valorPorHora, int totalHorasTrabalhadas) {
        super(nome, dataNascimento);
        this.valorPorHora = valorPorHora;
        this.totalHorasTrabalhadas = totalHorasTrabalhadas;
    }

    @Override
    public double calcularSalario() {
        return valorPorHora * totalHorasTrabalhadas;
    }
}
