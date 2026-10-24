public class C3 extends C2 {
    public String profissao;
    protected String nacionalidade;
    private String identidade;


    public C3() {
        System.out.println("Classe C3: chamada do construtor padrão, sem parâmetros");
    }


    public C3(String nome, String genero, String cpf, String endereco, String telefone, String email,
              String profissao, String nacionalidade, String identidade) {
        super(nome, genero, cpf, endereco, telefone, email);
        this.profissao = profissao;
        this.nacionalidade = nacionalidade;
        this.identidade = identidade;
        System.out.println("Classe C3: chamada do construtor com parâmetros");
    }

    @Override
    public void mostrarAtributos() {
        super.mostrarAtributos();
        System.out.println("C3 - Profissão: " + profissao);
        System.out.println("C3 - Nacionalidade: " + nacionalidade);
        System.out.println("C3 - Identidade: " + identidade);
    }

    @Override
    public void mostrarAtributosSuper() {
        super.mostrarAtributos();
    }
}
