public class ItemRevista extends Item {
    private String org;
    private String vol;
    private String nro;

    public ItemRevista(String titulo, String ano, String org, String vol, String nro){
        super(titulo, ano);
        this.org = org;
        this.vol = vol;
        this.nro = nro;
    }

    @Override
    String dados() {
        return "Revista: " + super.titulo + "   " + this.org + "   " + this.vol + "   " + this.nro + "   " + super.ano;
    }

    @Override
    String salvar() {
        return  super.titulo + "," +  this.org + "," + this.vol + "," +  this.nro + "," + super.ano;
    }
}
