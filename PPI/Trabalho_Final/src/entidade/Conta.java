package entidade;

/**
 * Conta de acesso ao sistema (login).
 *
 * Nao confundir com entidade.Usuario: Usuario e o leitor cadastrado na
 * biblioteca (dominio do sistema); Conta e quem consegue entrar no site.
 */
public class Conta {
    private Long id;
    private String nome;
    private String email;
    private String senha; // formato "salt:hash" (ver util.Senha)

    public Conta() {
    }

    public Conta(String nome, String email, String senha) {
        this.nome = nome;
        this.email = email;
        this.senha = senha;
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

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getSenha() {
        return senha;
    }

    public void setSenha(String senha) {
        this.senha = senha;
    }

    @Override
    public String toString() {
        return "Conta [id=" + id + ", nome=" + nome + ", email=" + email + "]";
    }
}
