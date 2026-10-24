public class Servico implements Classificavel{
    private float preco;

    public Servico(float preco) {
        this.preco = preco;
    }

    public float getPreco() {
        return preco;
    }

    public void setPreco(float preco) {
        this.preco = preco;
    }

    

    @Override
    public String toString() {
        return "Preço = " + this.preco + " ";
    }

    @Override
    public void mostrar(){
        System.out.print(toString());
    }
    
    @Override
    public int ehMenorQue(Classificavel obj) {
       Servico aux = (Servico) obj;
       if (this.preco < aux.preco) return 1;
       else return 0;
    }

    
}
