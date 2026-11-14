 package entidade;

import java.sql.Date;

public class Emprestimo {
    private Long id;
    private Date dataEmprestimo;
    private Date dataDevolucao;
    private Long usuarioId;
    private Long livroId;
    private Long revistaId;
    
    public Emprestimo() {
    }
    
    public Emprestimo(Date dataEmprestimo, Date dataDevolucao, Long usuarioId, Long livroId, Long revistaId) {
        this.dataEmprestimo = dataEmprestimo;
        this.dataDevolucao = dataDevolucao;
        this.usuarioId = usuarioId;
        this.livroId = livroId;
        this.revistaId = revistaId;
    }
    
    public Long getId() {
        return id;
    }
    
    public void setId(Long id) {
        this.id = id;
    }
    
    public Date getDataEmprestimo() {
        return dataEmprestimo;
    }
    
    public void setDataEmprestimo(Date dataEmprestimo) {
        this.dataEmprestimo = dataEmprestimo;
    }
    
    public Date getDataDevolucao() {
        return dataDevolucao;
    }
    
    public void setDataDevolucao(Date dataDevolucao) {
        this.dataDevolucao = dataDevolucao;
    }
    
    public Long getUsuarioId() {
        return usuarioId;
    }
    
    public void setUsuarioId(Long usuarioId) {
        this.usuarioId = usuarioId;
    }
    
    public Long getLivroId() {
        return livroId;
    }
    
    public void setLivroId(Long livroId) {
        this.livroId = livroId;
    }
    
    public Long getRevistaId() {
        return revistaId;
    }
    
    public void setRevistaId(Long revistaId) {
        this.revistaId = revistaId;
    }
    
    @Override
    public String toString() {
        return "Emprestimo [id=" + id + ", dataEmprestimo=" + dataEmprestimo + 
               ", usuarioId=" + usuarioId + ", livroId=" + livroId + ", revistaId=" + revistaId + "]";
    }
}