public class C2 extends C1 {
    public String endereco;
    protected String telefone;
    private String email;


    public C2() {
        System.out.println("Classe C2: chamada do construtor padrão, sem parâmetros");
    }


    public C2(String nome, String genero, String cpf, String endereco, String telefone, String email) {
        super(nome, genero, cpf);
        this.endereco = endereco;
        this.telefone = telefone;
        this.email = email;
        System.out.println("Classe C2: chamada do construtor com parâmetros");
    }

    @Override
    public void mostrarAtributos() {
        super.mostrarAtributos();
        System.out.println("C2 - Endereço: " + endereco);
        System.out.println("C2 - Telefone: " + telefone);
        System.out.println("C2 - Email: " + email);
    }

    @Override
    public void mostrarAtributosSuper() {
        super.mostrarAtributos();
    }
}
