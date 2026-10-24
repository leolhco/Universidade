public class Empresa {
    public static void main(String[] args) {

        Funcionario[] funcionario = new Funcionario[4];

        funcionario[0] = new Chefe("AAA", "000", 23, 50000);

        funcionario[1] = new Vendedor("BBB", "111",
                2000, 300, 40, 24);

        funcionario[2] = new Operario("CCC", "222", 25,
                70, 400 );

        funcionario[3] = new Horista("DDD", "333", 26,
                80, 8*25);

       /* for(Funcionario funcionario1 : funcionario){
            funcionario1.souFuncionario();
        }*/

        FolhaPagamento folhaPagamento = new FolhaPagamento();
        folhaPagamento.payroll(funcionario);
    }
}