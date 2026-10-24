public class Main {
    public static void main(String[] args) {
        Funcionario func1 = new Funcionario("Marcelo", 12211);
        Funcionario func2 = new Funcionario("Catarina", 12212);


        Departamento departamento = new Departamento("Recursos Humanos", 3);


        departamento.adicionarFuncionario(func1);
        departamento.adicionarFuncionario(func2);


        departamento.listarFuncionarios();

        // Apesar do Departamento agregar os funcionários,
        // os objetos existem independentemente
    }
}