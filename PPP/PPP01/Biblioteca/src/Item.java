abstract public class Item {

    protected String titulo;
    protected String ano;

    public Item(String titulo, String ano){
        this.titulo = titulo;
        this.ano = ano;
    }

    abstract String dados();

    abstract String salvar();
}
