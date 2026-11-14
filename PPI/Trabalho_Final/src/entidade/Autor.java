package entidade;

import java.sql.Date;

public class Autor {
    private Long id;
    private String nomeReal;
    private String nomeArtistico;
    private Date dataNascimento;
    
    public Autor() {
    }
    
    public Autor(String nomeReal, String nomeArtistico, Date dataNascimento) {
        this.nomeReal = nomeReal;
        this.nomeArtistico = nomeArtistico;
        this.dataNascimento = dataNascimento;
    }
    
    public Long getId() {
        return id;
    }
    
    public void setId(Long id) {
        this.id = id;
    }
    
    public String getNomeReal() {
        return nomeReal;
    }
    
    public void setNomeReal(String nomeReal) {
        this.nomeReal = nomeReal;
    }
    
    public String getNomeArtistico() {
        return nomeArtistico;
    }
    
    public void setNomeArtistico(String nomeArtistico) {
        this.nomeArtistico = nomeArtistico;
    }
    
    public Date getDataNascimento() {
        return dataNascimento;
    }
    
    public void setDataNascimento(Date dataNascimento) {
        this.dataNascimento = dataNascimento;
    }
    
    @Override
    public String toString() {
        return "Autor [id=" + id + ", nomeReal=" + nomeReal + ", nomeArtistico=" + nomeArtistico + "]";
    }
}