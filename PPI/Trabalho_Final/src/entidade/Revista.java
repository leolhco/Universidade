package entidade;

public class Revista {
    private Long id;
    private String titulo;
    private String editora;
    private Integer numeroEdicao;
    private Integer anoPublicacao;
    private String mesPublicacao;
    private String issn;
    private String periodicidade;
    
    public Revista() {
    }
    
    public Revista(String titulo, String editora, Integer numeroEdicao, Integer anoPublicacao, 
                   String mesPublicacao, String issn, String periodicidade) {
        this.titulo = titulo;
        this.editora = editora;
        this.numeroEdicao = numeroEdicao;
        this.anoPublicacao = anoPublicacao;
        this.mesPublicacao = mesPublicacao;
        this.issn = issn;
        this.periodicidade = periodicidade;
    }
    
    public Long getId() {
        return id;
    }
    
    public void setId(Long id) {
        this.id = id;
    }
    
    public String getTitulo() {
        return titulo;
    }
    
    public void setTitulo(String titulo) {
        this.titulo = titulo;
    }
    
    public String getEditora() {
        return editora;
    }
    
    public void setEditora(String editora) {
        this.editora = editora;
    }
    
    public Integer getNumeroEdicao() {
        return numeroEdicao;
    }
    
    public void setNumeroEdicao(Integer numeroEdicao) {
        this.numeroEdicao = numeroEdicao;
    }
    
    public Integer getAnoPublicacao() {
        return anoPublicacao;
    }
    
    public void setAnoPublicacao(Integer anoPublicacao) {
        this.anoPublicacao = anoPublicacao;
    }
    
    public String getMesPublicacao() {
        return mesPublicacao;
    }
    
    public void setMesPublicacao(String mesPublicacao) {
        this.mesPublicacao = mesPublicacao;
    }
    
    public String getIssn() {
        return issn;
    }
    
    public void setIssn(String issn) {
        this.issn = issn;
    }
    
    public String getPeriodicidade() {
        return periodicidade;
    }
    
    public void setPeriodicidade(String periodicidade) {
        this.periodicidade = periodicidade;
    }
    
    @Override
    public String toString() {
        return "Revista [id=" + id + ", titulo=" + titulo + ", edicao=" + numeroEdicao + 
               ", ano=" + anoPublicacao + ", ISSN=" + issn + "]";
    }
}