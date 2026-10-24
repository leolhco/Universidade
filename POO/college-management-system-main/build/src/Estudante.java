public class Estudante implements Exibivel {
    protected String nome;
    protected String dataNascimento;
    protected String CPF;
    protected Float CRA;
    
    public Estudante(String nome, String dataNascimento, String CPF, Float CRA) {
        this.nome = nome;
        this.dataNascimento = dataNascimento;
        this.CPF = CPF;
        this.CRA = CRA;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public void setDataNascimento(String dataNascimento) {
        this.dataNascimento = dataNascimento;
    }

    public void setCPF(String CPF) {
        this.CPF = CPF;
    }

    public void setCRA(Float CRA) {
        this.CRA = CRA;
    }

    public String getNome() {
        return nome;
    }

    public String getDataNascimento() {
        return dataNascimento;
    }

    public String getCPF() {
        return CPF;
    }

    public Float getCRA() {
        return CRA;
    }

    public String mostrarDados() {
        return "Nome: " + nome + "\nData de Nascimento: " + dataNascimento + "\nCPF: " + CPF + "\nCRA: " + CRA;
    }

}