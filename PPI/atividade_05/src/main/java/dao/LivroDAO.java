package dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;
import entidade.Livro;
import conexao.ConnectionFactory;

public class LivroDAO {
    
    public void inserir(Livro livro) {
        String sql = "INSERT INTO livro (nome, editora, autor_id) VALUES (?, ?, ?)";
        try (Connection conn = new ConnectionFactory().getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS)) {
            
            stmt.setString(1, livro.getNome());
            stmt.setString(2, livro.getEditora());
            stmt.setLong(3, livro.getAutorId());
            
            stmt.executeUpdate();
            
            ResultSet rs = stmt.getGeneratedKeys();
            if (rs.next()) {
                livro.setId(rs.getLong(1));
            }
            System.out.println("Livro inserido com sucesso! ID: " + livro.getId());
        } catch (SQLException e) {
            throw new RuntimeException("Erro ao inserir livro no banco de dados.", e);
        }
    }
    
    public List<Livro> listarTodos() {
        List<Livro> livros = new ArrayList<>();
        String sql = "SELECT * FROM livro";
        try (Connection conn = new ConnectionFactory().getConnection();
             Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery(sql)) {
            
            while (rs.next()) {
                Livro livro = new Livro();
                livro.setId(rs.getLong("id"));
                livro.setNome(rs.getString("nome"));
                livro.setEditora(rs.getString("editora"));
                livro.setAutorId(rs.getLong("autor_id"));
                livros.add(livro);
            }
        } catch (SQLException e) {
            System.err.println("Erro!");
        }
        return livros;
    }
    
    public Livro buscarPorId(Long id) {
        String sql = "SELECT * FROM livro WHERE id = ?";
        try (Connection conn = new ConnectionFactory().getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            
            stmt.setLong(1, id);
            ResultSet rs = stmt.executeQuery();
            
            if (rs.next()) {
                Livro livro = new Livro();
                livro.setId(rs.getLong("id"));
                livro.setNome(rs.getString("nome"));
                livro.setEditora(rs.getString("editora"));
                livro.setAutorId(rs.getLong("autor_id"));
                return livro;
            }
        } catch (SQLException e) {
            throw new RuntimeException("Erro ao buscar livro no banco de dados.", e);
        }
        return null;
    }
    
    public void atualizar(Livro livro) {
        String sql = "UPDATE livro SET nome = ?, editora = ?, autor_id = ? WHERE id = ?";
        try (Connection conn = new ConnectionFactory().getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            
            stmt.setString(1, livro.getNome());
            stmt.setString(2, livro.getEditora());
            stmt.setLong(3, livro.getAutorId());
            stmt.setLong(4, livro.getId());
            
            int rows = stmt.executeUpdate();
            if (rows > 0) {
                System.out.println("Livro atualizado com sucesso!");
            } else {
                System.out.println("Nenhum livro encontrado com ID: " + livro.getId());
            }
        } catch (SQLException e) {
           throw new RuntimeException("Erro ao atualizar livro no banco de dados.", e);
        }
    }
    
    public void deletar(Long id) {
        String sql = "DELETE FROM livro WHERE id = ?";
        try (Connection conn = new ConnectionFactory().getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            
            stmt.setLong(1, id);
            int rows = stmt.executeUpdate();
            if (rows > 0) {
                System.out.println("Livro deletado com sucesso!");
            } else {
                System.out.println("Nenhum livro encontrado com ID: " + id);
            }
        } catch (SQLException e) {
           throw new RuntimeException("Erro ao deletar livro do banco de dados.", e);
        }
    }
}