public class Chefe extends Funcionario {
   private int idade;


    public Chefe(String nome, String data, int idade, float Salario){
        super(nome, data);
        this.idade = idade;
        this.setCargo("Chefe");
        this.setSalario(Salario);
    }
    @Override
    public void souFuncionario(){
        System.out.println("Oi, eu sou um Chefe!\n");
    }

    @Override
    public String toString() {
        return super.toString() + "Chefe\n" +
                "idade = " + idade +
                '}';
    }
}
