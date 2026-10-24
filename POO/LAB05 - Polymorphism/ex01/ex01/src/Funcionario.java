public class Funcionario {
    private String nome;
    private String data;
    private String cargo;
    private float salario;

    public Funcionario(String nome, String data) {
        this.nome = nome;
        this.data = data;
    }

    public void souFuncionario(){
        System.out.println("Oi, eu sou um Funcionario!\n");
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

    public float getSalario() {
        return salario;
    }

    public void setSalario(float salario) {
        this.salario = salario;
    }

    public String getCargo() {
        return cargo;
    }

    public void setCargo(String cargo) {
        this.cargo = cargo;
    }

    @Override
    public String toString() {
        return "Funcionario{" +
                "\nnome ='" + nome + '\'' +
                ", \ndata ='" + data + '\'' +
                ", \nsalario =" + salario +
                '\n';
    }
}
