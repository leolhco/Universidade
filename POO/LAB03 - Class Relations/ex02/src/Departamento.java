public class Departamento {
    private String nome;
    private Funcionario[] funcionarios;
    private int quantidadeFuncionarios;


    public Departamento(String nome, int tamanhoMaximo) {
        this.nome = nome;
        this.funcionarios = new Funcionario[tamanhoMaximo];
        this.quantidadeFuncionarios = 0;
    }


    public void adicionarFuncionario(Funcionario funcionario) {
        if (quantidadeFuncionarios < funcionarios.length) {
            funcionarios[quantidadeFuncionarios] = funcionario;
            quantidadeFuncionarios++;
        } else {
            System.out.println("O departamento já atingiu o limite de funcionários.");
        }
    }


    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public Funcionario[] getFuncionarios() {
        return funcionarios;
    }


    public void listarFuncionarios() {
        System.out.println("Funcionários do departamento " + nome + ":");
        for (int i = 0; i < quantidadeFuncionarios; i++) {
            System.out.println(funcionarios[i]);
        }
    }
}
