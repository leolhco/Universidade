public class CandidatoVereador {
    private String nome;
    private String data;
    private String sexo;
    private float bens;
    private boolean reeleicao;
    private int numPartido;
    private int numVereador;
    private String bairro;

    public CandidatoVereador(String nome, String data, String sexo, float bens, boolean reeleicao, int numPartido, int numVereador, String bairro) {
        this.nome = nome;
        this.data = data;
        this.sexo = sexo;
        this.bens = bens;
        this.reeleicao = reeleicao;
        this.numPartido = numPartido;
        this.numVereador = numVereador;
        this.bairro = bairro;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getData() {
        return data;
    }

    public void setData(String data) {
        this.data = data;
    }

    public String getSexo() {
        return sexo;
    }

    public void setSexo(String sexo) {
        this.sexo = sexo;
    }

    public float getBens() {
        return bens;
    }

    public void setBens(float bens) {
        this.bens = bens;
    }

    public boolean isReeleicao() {
        return reeleicao;
    }

    public void setReeleicao(boolean reeleicao) {
        this.reeleicao = reeleicao;
    }

    public int getNumPartido() {
        return numPartido;
    }

    public void setNumPartido(int numPartido) {
        this.numPartido = numPartido;
    }

    public int getNumVereador() {
        return numVereador;
    }

    public void setNumVereador(int numVereador) {
        this.numVereador = numVereador;
    }

    public String getBairro() {
        return bairro;
    }

    public void setBairro(String bairro) {
        this.bairro = bairro;
    }

    @Override
    public String toString() {
        return "CandidatoVereador{" +
                "nome ='" + nome + '\'' +
                ", data ='" + data + '\'' +
                ", sexo ='" + sexo + '\'' +
                ", bens =" + bens +
                ", reeleicao =" + reeleicao +
                ", numPartido =" + numPartido +
                ", numVereador =" + numVereador +
                ", bairro ='" + bairro + '\'' +
                '}';
    }
}
