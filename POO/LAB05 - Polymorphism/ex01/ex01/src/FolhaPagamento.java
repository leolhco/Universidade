public class FolhaPagamento {
    public void payroll(Funcionario[] funcionario){
        for(Funcionario funcionario1 : funcionario){
            System.out.println(funcionario1.getCargo() + " <---> " + funcionario1.getSalario());
        }
    }
}
