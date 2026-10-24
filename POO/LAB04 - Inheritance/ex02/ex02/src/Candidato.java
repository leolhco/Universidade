public class Candidato {
    protected String nome;
    protected String data;
    protected String sexo;
    protected float bens;
    protected boolean reeleicao;
    protected int numPartido;

    public Candidato(String nome, String data, String sexo, float bens, boolean reeleicao, int numPartido) {
        this.nome = nome;
        this.data = data;
        this.sexo = sexo;
        this.bens = bens;
        this.reeleicao = reeleicao;
        this.numPartido = numPartido;
    }

    @Override
    public String toString() {
        return "Candidato{" +
                "nome='" + nome + '\'' +
                ", data='" + data + '\'' +
                ", sexo='" + sexo + '\'' +
                ", bens=" + bens +
                ", reeleicao=" + reeleicao +
                ", numPartido=" + numPartido +
                '}';
    }
}
