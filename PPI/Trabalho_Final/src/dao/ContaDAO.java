package dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import conexao.ConnectionFactory;
import entidade.Conta;

/**
 * Acesso ao banco para a tabela "conta" (login e cadastro).
 * Segue o mesmo padrao dos demais DAOs do projeto.
 */
public class ContaDAO {

    public void inserir(Conta conta) {
        String sql = "INSERT INTO conta (nome, email, senha) VALUES (?, ?, ?)";

        try (Connection conn = new ConnectionFactory().getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS)) {

            stmt.setString(1, conta.getNome());
            stmt.setString(2, conta.getEmail());
            stmt.setString(3, conta.getSenha()); // ja vem com hash

            stmt.executeUpdate();

            ResultSet rs = stmt.getGeneratedKeys();
            if (rs.next()) {
                conta.setId(rs.getLong(1));
            }
            System.out.println("Conta criada com sucesso! ID: " + conta.getId());

        } catch (SQLException e) {
            throw new RuntimeException("Erro ao criar a conta no banco de dados.", e);
        }
    }

    public Conta buscarPorEmail(String email) {
        String sql = "SELECT * FROM conta WHERE email = ?";

        try (Connection conn = new ConnectionFactory().getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {

            stmt.setString(1, email);
            ResultSet rs = stmt.executeQuery();

            if (rs.next()) {
                Conta conta = new Conta();
                conta.setId(rs.getLong("id"));
                conta.setNome(rs.getString("nome"));
                conta.setEmail(rs.getString("email"));
                conta.setSenha(rs.getString("senha"));
                return conta;
            }

        } catch (SQLException e) {
            throw new RuntimeException("Erro ao buscar a conta no banco de dados.", e);
        }
        return null;
    }

    public boolean emailJaCadastrado(String email) {
        return buscarPorEmail(email) != null;
    }
}
