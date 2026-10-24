public class Vendedor extends Funcionario{
    private int idade;

    public Vendedor(String nome, String data, float valorFixo, float comissao, float vendas, int idade){
        super(nome, data);
        this.setSalario(valorFixo + comissao * vendas);
        this.idade = idade;
        this.setCargo("Vendedor");
    }

    @Override
    public void souFuncionario(){
        System.out.println("Oi, eu sou um Vendedor!\n");
    }

    @Override
    public String toString() {
        return super.toString() + "Vendedor\n" +
                "idade = " + idade +
                '}';
    }
}
