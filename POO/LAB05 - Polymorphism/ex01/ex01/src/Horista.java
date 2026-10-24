public class Horista extends Funcionario{
    private int idade;

    public Horista(String nome, String data, int idade, float valorHora, float totalHora){
        super(nome, data);
        this.idade = idade;
        this.setSalario(valorHora * totalHora);
        this.setCargo("Horista");
    }
    @Override
    public void souFuncionario(){
        System.out.println("Oi, eu sou um Horista!\n");
    }
}
