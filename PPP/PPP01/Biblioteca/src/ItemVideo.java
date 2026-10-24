public class ItemVideo extends Item{
    private String autor;
    private String duracao;

    public ItemVideo(String titulo, String ano, String autor, String duracao){
        super(titulo, ano);
        this.autor = autor;
        this.duracao = duracao;
    }

    @Override
    String dados() {
        return "Video: " + super.titulo + "   " + super.ano + "   " + this.autor + "   " + this.duracao;
    }

    @Override
    String salvar() {
        return super.titulo + "," + super.ano + "," + this.autor + "," + this.duracao;
    }
}
