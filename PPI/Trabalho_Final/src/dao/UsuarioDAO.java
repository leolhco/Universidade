package dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;
import entidade.Usuario;
import conexao.ConnectionFactory;

public class UsuarioDAO {
    
    public void inserir(Usuario usuario) {
        String sql = "INSERT INTO usuario (nome, dataNascimento, email, telefone) VALUES (?, ?, ?, ?)";
        try (Connection conn = new ConnectionFactory().getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS)) {
            
            stmt.setString(1, usuario.getNome());
            stmt.setDate(2, usuario.getDataNascimento());
            stmt.setString(3, usuario.getEmail());
            stmt.setString(4, usuario.getTelefone());
            
            stmt.executeUpdate();
            
            ResultSet rs = stmt.getGeneratedKeys();
            if (rs.next()) {
                usuario.setId(rs.getLong(1));
            }
            System.out.println("Usuario inserido com sucesso! ID: " + usuario.getId());
        } catch (SQLException e) {
            throw new RuntimeException("Erro ao inserir usuario no banco de dados.", e);
        }
    }
    
    public List<Usuario> listarTodos() {
        List<Usuario> usuarios = new ArrayList<>();
        String sql = "SELECT * FROM usuario";
        try (Connection conn = new ConnectionFactory().getConnection();
             Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery(sql)) {
            
            while (rs.next()) {
                Usuario usuario = new Usuario();
                usuario.setId(rs.getLong("id"));
                usuario.setNome(rs.getString("nome"));
                usuario.setDataNascimento(rs.getDate("dataNascimento"));
                usuario.setEmail(rs.getString("email"));
                usuario.setTelefone(rs.getString("telefone"));
                usuarios.add(usuario);
            }
        } catch (SQLException e) {
            throw new RuntimeException("Erro ao listar usuarios do banco de dados.", e);
        }
        return usuarios;
    }
    
    public Usuario buscarPorId(Long id) {
        String sql = "SELECT * FROM usuario WHERE id = ?";
        try (Connection conn = new ConnectionFactory().getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            
            stmt.setLong(1, id);
            ResultSet rs = stmt.executeQuery();
            
            if (rs.next()) {
                Usuario usuario = new Usuario();
                usuario.setId(rs.getLong("id"));
                usuario.setNome(rs.getString("nome"));
                usuario.setDataNascimento(rs.getDate("dataNascimento"));
                usuario.setEmail(rs.getString("email"));
                usuario.setTelefone(rs.getString("telefone"));
                return usuario;
            }
        } catch (SQLException e) {
            throw new RuntimeException("Erro ao buscar usuario no banco de dados.", e);
        }
        return null;
    }
    
    // NOVO MÉTODO PARA A TELA DE BUSCA
    public List<Usuario> buscarAvancado(String criterio, String termo) {
        List<Usuario> usuarios = new ArrayList<>();
        String sql;
        
        if ("id".equals(criterio)) {
            sql = "SELECT * FROM usuario WHERE id = ?";
        } else if ("email".equals(criterio)) {
            sql = "SELECT * FROM usuario WHERE email LIKE ?";
        } else {
            sql = "SELECT * FROM usuario WHERE nome LIKE ?";
        }

        try (Connection conn = new ConnectionFactory().getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            
            if ("id".equals(criterio)) {
                stmt.setLong(1, Long.parseLong(termo));
            } else {
                stmt.setString(1, "%" + termo + "%");
            }
            
            ResultSet rs = stmt.executeQuery();
            while (rs.next()) {
                Usuario usuario = new Usuario();
                usuario.setId(rs.getLong("id"));
                usuario.setNome(rs.getString("nome"));
                usuario.setDataNascimento(rs.getDate("dataNascimento"));
                usuario.setEmail(rs.getString("email"));
                usuario.setTelefone(rs.getString("telefone"));
                usuarios.add(usuario);
            }
        } catch (SQLException | NumberFormatException e) {
            throw new RuntimeException("Erro ao realizar busca avancada de usuario.", e);
        }
        return usuarios;
    }
    
    public void atualizar(Usuario usuario) {
        String sql = "UPDATE usuario SET nome = ?, dataNascimento = ?, email = ?, telefone = ? WHERE id = ?";
        try (Connection conn = new ConnectionFactory().getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            
            stmt.setString(1, usuario.getNome());
            stmt.setDate(2, usuario.getDataNascimento());
            stmt.setString(3, usuario.getEmail());
            stmt.setString(4, usuario.getTelefone());
            stmt.setLong(5, usuario.getId());
            
            int rows = stmt.executeUpdate();
            if (rows == 0) {
                throw new RuntimeException("Nenhum usuário encontrado para alteração com o ID: " + usuario.getId());
            }
        } catch (SQLException e) {
            throw new RuntimeException("Erro ao atualizar usuario no banco de dados.", e);
        }
    }
    
    public void deletar(Long id) {
        String sql = "DELETE FROM usuario WHERE id = ?";
        try (Connection conn = new ConnectionFactory().getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            
            stmt.setLong(1, id);
            int rows = stmt.executeUpdate();
            if (rows == 0) {
                throw new RuntimeException("Não foi possível remover: Nenhum usuário encontrado com o ID: " + id);
            }
        } catch (SQLException e) {
            throw new RuntimeException("Erro ao deletar usuario do banco de dados.", e);
        }
    }
}