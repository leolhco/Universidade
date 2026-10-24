public class Main {
    public static void main(String[] args) {
        Funcionario funcionario = new Funcionario(20000, "Bruno", "12345678900");
        try{
            funcionario.aumentarSalario(200);
        } catch (SalarioInvalidoException e) {
            System.out.println(e.getMessage());
        } finally {
            System.out.println("Salario atual: " +funcionario.getSalario());
        }
    }
}