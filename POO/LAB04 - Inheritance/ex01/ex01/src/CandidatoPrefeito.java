public class CandidatoPrefeito {
    private String nome;
    private String data;
    private String sexo;
    private float bens;
    private boolean reeleicao;
    private int numPartido;
    private String vice;
    private String numVice;

    public CandidatoPrefeito(String nome, String data, String sexo, float bens, boolean reeleicao, int numPartido, String vice, String numVice) {
        this.nome = nome;
        this.data = data;
        this.sexo = sexo;
        this.bens = bens;
        this.reeleicao = reeleicao;
        this.numPartido = numPartido;
        this.vice = vice;
        this.numVice = numVice;
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

    public String getVice() {
        return vice;
    }

    public void setVice(String vice) {
        this.vice = vice;
    }

    public String getNumVice() {
        return numVice;
    }

    public void setNumVice(String numVice) {
        this.numVice = numVice;
    }

    @Override
    public String toString() {
        return "CandidatoPrefeito{" +
                "nome ='" + getNome() + '\'' +
                ", data ='" + getData() + '\'' +
                ", sexo ='" + getSexo() + '\'' +
                ", bens =" + getBens() +
                ", reeleicao =" + isReeleicao() +
                ", numPartido =" + getNumPartido() +
                ", vice='" + getVice() + '\'' +
                ", numVice ='" + getNumVice() + '\'' +
                '}';
    }
}
