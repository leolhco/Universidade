public class C1 {
    public String nome;
    protected String genero;
    private String cpf;


    public C1() {
        System.out.println("Classe C1: chamada do construtor padrão, sem parâmetros");
    }


    public C1(String nome, String genero, String cpf) {
        this.nome = nome;
        this.genero = genero;
        this.cpf = cpf;
        System.out.println("Classe C1: chamada do construtor com parâmetros");
    }

    public void mostrarAtributos() {
        System.out.println("C1 - Nome: " + nome);
        System.out.println("C1 - Gênero: " + genero);
        System.out.println("C1 - CPF: " + cpf);
    }

    public void mostrarAtributosSuper() {
        mostrarAtributos();
    }
}
