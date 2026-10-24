public class Empresa {
    public static void main(String[] args) {
        Funcionario[] funcionarios = new Funcionario[8];


        funcionarios[0] = new Chefe("Carlos Silva", "01/01/1980", 5000);
        funcionarios[1] = new Chefe("Ana Oliveira", "02/02/1985", 6000);


        funcionarios[2] = new Vendedor("Pedro Almeida", "03/03/1990", 2000, 0.1, 10000);
        funcionarios[3] = new Vendedor("Mariana Santos", "04/04/1992", 2500, 0.15, 15000);


        funcionarios[4] = new Operario("Roberto Costa", "05/05/1995", 10, 300);
        funcionarios[5] = new Operario("Julia Mendes", "06/06/1998", 12, 250);


        funcionarios[6] = new Horista("Lucas Pereira", "07/07/1996", 20, 160);
        funcionarios[7] = new Horista("Clara Ribeiro", "08/08/1994", 25, 120);


        for (Funcionario funcionario : funcionarios) {
            System.out.println(funcionario);
        }
    }
}
