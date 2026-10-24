public class Professor implements Exibivel, ToTXT{
    private String nome;
    private String dataNascimento;
    private String CPF;
    private String inicioContrato;
    private String departamento;

    public Professor(String nome, String dataNascimento, String CPF, String inicioContrato, String departamento) {
        this.nome = nome;
        this.dataNascimento = dataNascimento;
        this.CPF = CPF;
        this.inicioContrato = inicioContrato;
        this.departamento = departamento;
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

    public void setInicioContrato(String inicioContrato) {
        this.inicioContrato = inicioContrato;
    }

    public void setDepartamento(String departamento) {
        this.departamento = departamento;
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

    public String getInicioContrato() {
        return inicioContrato;
    }

    public String getDepartamento() {
        return departamento;
    }

    public String mostrarDados() {
        return "Nome: " + nome + "\nData de Nascimento: " + dataNascimento + "\nCPF: " + CPF + "\nInicio do Contrato: " + inicioContrato + "\nDepartamento: " + departamento + "\n\n\n";
    }

    @Override
    public String toTXT() {
       return  this.nome + "," + this.dataNascimento + "," + this.CPF + "," + this.inicioContrato + "," + this.departamento;
    }
}
