public class Vereador extends Candidato{
    private String num;
    private String bairro;

    @Override
    public String toString() {
        return "Vereador{" +
                "num='" + num + '\'' +
                ", bairro='" + bairro + '\'' +
                ", nome='" + nome + '\'' +
                ", data='" + data + '\'' +
                ", sexo='" + sexo + '\'' +
                ", bens=" + bens +
                ", reeleicao=" + reeleicao +
                ", numPartido=" + numPartido +
                '}';
    }

    public Vereador(String nome, String data, String sexo, float bens, boolean reeleicao, int numPartido, String num, String bairro) {
        super(nome, data, sexo, bens, reeleicao, numPartido);
        this.num = num;
        this.bairro = bairro;
    }
}
