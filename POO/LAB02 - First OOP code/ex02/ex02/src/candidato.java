public class candidato {


    private String nome;
    private String data;
    private String genero;
    private double bens;
    private String reeleicao;
    private int partido;
    private String cargo;

    public void mostrar() {
        System.out.println("Nome: " +this.getNome());
        System.out.println("Data de Nascimento: " +this.getData());
        System.out.println("Gênero: " +this.getGenero());
        System.out.println("Total de Bens: " +this.getBens());
        System.out.println("Reeleição: " +this.getReeleicao());
        System.out.println("Partido: " +this.getPartido());
        System.out.println("Cargo: " + this.getCargo());
        System.out.println();
    }


    public void setNome(String novoNome) {

        nome = novoNome;

    }

    public void setData(String novaData) {

        data = novaData;

    }

    public void setGenero(String novoGenero) {

        genero = novoGenero;

    }

    public void setBens(double novosBens) {

        bens = novosBens;

    }

    public void setReeleicao(String novaReeleicao) {

        reeleicao = novaReeleicao;

    }

    public void setPartido(int novoPartido) {

        partido = novoPartido;

    }

    public void setCargo(String novoCargo) {

        cargo = novoCargo;

    }


    public String getNome() {

        return this.nome;

    }

    public String getData() {

        return this.data;

    }

    public String getGenero() {
        return this.genero;
         }

    public double getBens() {
        return this.bens;
         }

    public String getReeleicao() {
        return this.reeleicao;
         }

    public int getPartido() {

        return this.partido;

    }

    public String getCargo() {

        return this.cargo;

    }
}
