public class ItemLivro extends Item{
    private String autor;

    public ItemLivro(String titulo, String ano, String autor){
        super(titulo, ano);
        this.autor = autor;
    }

    @Override
    String dados() {
      return "Livro: " + super.titulo + "   " + this.autor + "   " + super.ano;
    }

    @Override
    String salvar() {
        return  super.titulo + "," + this.autor + "," + super.ano;
    }
}
