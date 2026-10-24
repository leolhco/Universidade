public class Funcionario {
    private String nome;
    private String cpf;
    private float salario;
    private float tetoSalarial;

    public Funcionario(float salario, String nome, String cpf) {
        this.salario = salario;
        this.nome = nome;
        this.cpf = cpf;
        this.tetoSalarial = 40000;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getCpf() {
        return cpf;
    }

    public void setCpf(String cpf) {
        this.cpf = cpf;
    }

    public float getSalario() {
        return salario;
    }

    public void setSalario(float salario) {
        this.salario = salario;
    }

    public float getTetoSalarial() {
        return tetoSalarial;
    }

    public void setTetoSalarial(float tetoSalarial) {
        this.tetoSalarial = tetoSalarial;
    }

    public void aumentarSalario(float aumento){
        float salario = this.salario * (1 + (aumento/100));
        if(salario < 0) throw new SalarioInvalidoException("VALOR INVALIDO DE SALARIO!");
        if(salario > this.tetoSalarial) throw new SalarioInvalidoException("VALOR ULTRAPASSA O TETO!");
        this.salario = salario;
    }
}
