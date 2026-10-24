public class Candidato {
    private String nome;
    private String dataNascimento;
    private String genero;
    private float bens;
    private boolean reeleicao;
    private int numPartido;

    public Candidato(String nome, String dataNascimento, String genero, float bens, boolean reeleicao, int numPartido) {
        this.nome = nome;
        this.dataNascimento = dataNascimento;
        this.genero = genero;
        this.bens = bens;
        this.reeleicao = reeleicao;
        this.numPartido = numPartido;
    }


    public String getNome() {
        return nome;
    }

    public String getDataNascimento() {
        return dataNascimento;
    }

    public String getGenero() {
        return genero;
    }

    public float getBens() {
        return bens;
    }

    public boolean isReeleicao() {
        return reeleicao;
    }

    public int getNumPartido() {
        return numPartido;
    }

    @Override
    public String toString() {
        return "Nome: " + nome + "\nData de Nascimento: " + dataNascimento + "\nGênero: " + genero +
                "\nBens: R$ " + bens + "\nReeleição: " + (reeleicao ? "Sim" : "Não") + "\nNúmero do Partido: " + numPartido;
    }
}