public class Main {
    public static void selectionSortString(Produto[] produtos){
      int i, j, aux;
      Produto Menor = new Produto();
      Produto tmp = new Produto();
      for(i = 0; i < produtos.length; i++){
          Menor.setNome(produtos[i].getNome());
          aux = i;
          for(j = i + 1; j < produtos.length; j++){
              if(produtos[j].getNome().compareTo(Menor.getNome()) < 0){
                  Menor.setNome(produtos[j].getNome());
                  aux = j;
              }
          }
          if (aux != i){
          tmp.setNome(produtos[i].getNome());
          produtos[i].setNome(produtos[aux].getNome());
          produtos[aux].setNome(tmp.getNome());
          }
      }
    }
    public static void main(String[] args) {
        Produto[] produtos = new Produto[5];
        for(int i = 0; i < produtos.length; i++){
            produtos[i] = new Produto();
        }
        produtos[0].setNome("Notebook");
        produtos[0].setPreco(3000);
        produtos[0].setQtdEstoque(50);

        produtos[1].setNome("Mouse");
        produtos[1].setPreco(400);
        produtos[1].setQtdEstoque(100);

        produtos[2].setNome("Teclado");
        produtos[2].setPreco(500);
        produtos[2].setQtdEstoque(100);

        produtos[3].setNome("Gabinete");
        produtos[3].setPreco(800);
        produtos[3].setQtdEstoque(30);

        produtos[4].setNome("Tablet");
        produtos[4].setPreco(1800);
        produtos[4].setQtdEstoque(70);

        System.out.println("Vetor Antes Da Ordenaçao:");
        for(int i = 0; i < produtos.length; i++){
            produtos[i].mostrar();
        }

        selectionSortString(produtos);

        System.out.println("Vetor Apos A Ordenaçao:");
        for(int i = 0; i < produtos.length; i++){
            produtos[i].mostrar();
        }
    }
}