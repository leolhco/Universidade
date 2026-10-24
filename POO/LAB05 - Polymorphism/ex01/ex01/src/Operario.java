public class Operario extends Funcionario{
     private int idade;

     public Operario(String nome, String data, int idade, float producao, float qtdProd){
         super(nome, data);
         this.idade = idade;
         this.setSalario(producao * qtdProd);
         this.setCargo("Operario");
     }

    @Override
    public void souFuncionario(){
        System.out.println("Oi, eu sou um Operario!\n");
    }

    @Override
    public String toString() {
        return super.toString() +  "Operario\n" +
                "idade = " + idade +
                '}';
    }
}
