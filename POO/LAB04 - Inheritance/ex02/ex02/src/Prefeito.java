public class Prefeito extends Candidato{
   private String vice;
   private String numeroPartido;

    public Prefeito(String nome, String data, String sexo, float bens, boolean reeleicao, int numPartido, String vice, String numeroPartido) {
        super(nome, data, sexo, bens, reeleicao, numPartido);
        this.vice = vice;
        this.numeroPartido = numeroPartido;
    }

    @Override
    public String toString() {
        return "Prefeito{" +
                "vice='" + vice + '\'' +
                ", numeroPartido='" + numeroPartido + '\'' +
                ", nome='" + nome + '\'' +
                ", data='" + data + '\'' +
                ", sexo='" + sexo + '\'' +
                ", bens=" + bens +
                ", reeleicao=" + reeleicao +
                ", numPartido=" + numPartido +
                '}';
    }
}
