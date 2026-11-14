package entidade;

public class Livro {
    private Long id;
    private String nome;
    private String editora;
    private Long autorId;
    
    public Livro() {
    }
    
    public Livro(String nome, String editora, Long autorId) {
        this.nome = nome;
        this.editora = editora;
        this.autorId = autorId;
    }
    
    public Long getId() {
        return id;
    }
    
    public void setId(Long id) {
        this.id = id;
    }
    
    public String getNome() {
        return nome;
    }
    
    public void setNome(String nome) {
        this.nome = nome;
    }
    
    public String getEditora() {
        return editora;
    }
    
    public void setEditora(String editora) {
        this.editora = editora;
    }
    
    public Long getAutorId() {
        return autorId;
    }
    
    public void setAutorId(Long autorId) {
        this.autorId = autorId;
    }
    
    @Override
    public String toString() {
        return "Livro [id=" + id + ", nome=" + nome + ", editora=" + editora + ", autorId=" + autorId + "]";
    }
}