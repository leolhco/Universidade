public class Produto {
       private String nome;
       private double preco;
       private int qtdEstoque;

       public Produto(String nome, double preco, int qtdEstoque){
           this.nome = nome;
           this.preco = preco;
           this.qtdEstoque = qtdEstoque;
       }

       public Produto(){
           this.nome = "generico";
           this.preco = 10;
           this.qtdEstoque = 100;
       }

       public void setNome(String nome){
           this.nome = nome;
       }

       public void setPreco(double preco) {
           this.preco = preco;
       }

       public void setQtdEstoque(int qtdEstoque){
           this.qtdEstoque = qtdEstoque;
       }

       public String getNome(){
           return this.nome;
       }

       public double getPreco(){
           return this.preco;
       }

       public int getQtdEstoque(){
           return this.qtdEstoque;
       }

       public void mostrar(){
           System.out.println("Nome Do Produto: "+this.getNome());
           System.out.println("Preço Do Produto: "+this.getPreco());
           System.out.println("Quantidade Em Estoque: "+this.getQtdEstoque());
           System.out.println();
       }

       public void desconto(double x){
          if(x > 0) {
              this.preco = this.preco * (1 - x / 100);
          } else {
                System.out.println("ERRO! Valor Invalido!");
          }
       }

       public void aumento(double x){
          if(x > 0) {
              this.preco = this.preco * (1 + x / 100);
          } else {
              System.out.println("ERROR! Valor Invalido!");
          }
       }


}
