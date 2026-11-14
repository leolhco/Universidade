public class Responsavel {
    private int idResponsavel;
    private String nome;
    private String email;

    public Responsavel(String nome, String email) {
        this.nome = nome;
        this.email = email;
    }

    public int getIdResponsavel() { return idResponsavel; }
    public String getNome() { return nome; }
    public String getEmail() { return email; }
}
