package dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;
import entidade.Autor;
import conexao.ConnectionFactory;

public class AutorDAO {
    
    public void inserir(Autor autor) {
        String sql = "INSERT INTO autor (nomeReal, nomeArtistico, dataNascimento) VALUES (?, ?, ?)";
        try (Connection conn = new ConnectionFactory().getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS)) {
            
            stmt.setString(1, autor.getNomeReal());
            stmt.setString(2, autor.getNomeArtistico());
            stmt.setDate(3, autor.getDataNascimento());
            
            stmt.executeUpdate();
            
            ResultSet rs = stmt.getGeneratedKeys();
            if (rs.next()) {
                autor.setId(rs.getLong(1));
            }
            System.out.println("Autor inserido com sucesso! ID: " + autor.getId());
        } catch (SQLException e) {
            throw new RuntimeException("Erro ao inserir autor no banco de dados.", e);
        }
    }
    
    public List<Autor> listarTodos() {
        List<Autor> autores = new ArrayList<>();
        String sql = "SELECT * FROM autor";
        try (Connection conn = new ConnectionFactory().getConnection();
             Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery(sql)) {
            
            while (rs.next()) {
                Autor autor = new Autor();
                autor.setId(rs.getLong("id"));
                autor.setNomeReal(rs.getString("nomeReal"));
                autor.setNomeArtistico(rs.getString("nomeArtistico"));
                autor.setDataNascimento(rs.getDate("dataNascimento"));
                autores.add(autor);
            }
        } catch (SQLException e) {
            throw new RuntimeException("Erro ao listar autores do banco de dados.", e);
        }
        return autores;
    }
    
    public Autor buscarPorId(Long id) {
        String sql = "SELECT * FROM autor WHERE id = ?";
        try (Connection conn = new ConnectionFactory().getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            
            stmt.setLong(1, id);
            ResultSet rs = stmt.executeQuery();
            
            if (rs.next()) {
                Autor autor = new Autor();
                autor.setId(rs.getLong("id"));
                autor.setNomeReal(rs.getString("nomeReal"));
                autor.setNomeArtistico(rs.getString("nomeArtistico"));
                autor.setDataNascimento(rs.getDate("dataNascimento"));
                return autor;
            }
        } catch (SQLException e) {
            throw new RuntimeException("Erro ao buscar autor no banco de dados.", e);
        }
        return null;
    }
    
    // NOVO MÉTODO PARA A TELA DE BUSCA
    public List<Autor> buscarAvancado(String criterio, String termo) {
        List<Autor> autores = new ArrayList<>();
        String sql;
        
        if ("dataNascimento".equals(criterio)) {
            // Assumindo que o banco de dados suporta a função YEAR()
            sql = "SELECT * FROM autor WHERE YEAR(dataNascimento) = ?";
        } else if ("nomeArtistico".equals(criterio)) {
            sql = "SELECT * FROM autor WHERE nomeArtistico LIKE ?";
        } else {
            sql = "SELECT * FROM autor WHERE nomeReal LIKE ?";
        }

        try (Connection conn = new ConnectionFactory().getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            
            if ("dataNascimento".equals(criterio)) {
                stmt.setInt(1, Integer.parseInt(termo));
            } else {
                stmt.setString(1, "%" + termo + "%");
            }
            
            ResultSet rs = stmt.executeQuery();
            while (rs.next()) {
                Autor autor = new Autor();
                autor.setId(rs.getLong("id"));
                autor.setNomeReal(rs.getString("nomeReal"));
                autor.setNomeArtistico(rs.getString("nomeArtistico"));
                autor.setDataNascimento(rs.getDate("dataNascimento"));
                autores.add(autor);
            }
        } catch (SQLException | NumberFormatException e) {
            throw new RuntimeException("Erro ao realizar busca avancada de autor.", e);
        }
        return autores;
    }
    
    public void atualizar(Autor autor) {
        String sql = "UPDATE autor SET nomeReal = ?, nomeArtistico = ?, dataNascimento = ? WHERE id = ?";
        try (Connection conn = new ConnectionFactory().getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            
            stmt.setString(1, autor.getNomeReal());
            stmt.setString(2, autor.getNomeArtistico());
            stmt.setDate(3, autor.getDataNascimento());
            stmt.setLong(4, autor.getId());
            
            int rows = stmt.executeUpdate();
            if (rows == 0) {
                throw new RuntimeException("Nenhum autor encontrado para alteração com o ID: " + autor.getId());
            }
        } catch (SQLException e) {
            throw new RuntimeException("Erro ao atualizar autor no banco de dados.", e);
        }
    }
    
    public void deletar(Long id) {
        String sql = "DELETE FROM autor WHERE id = ?";
        try (Connection conn = new ConnectionFactory().getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            
            stmt.setLong(1, id);
            int rows = stmt.executeUpdate();
            if (rows == 0) {
                throw new RuntimeException("Não foi possível remover: Nenhum autor encontrado com o ID: " + id);
            }
        } catch (SQLException e) {
            throw new RuntimeException("Erro ao deletar autor do banco de dados.", e);
        }
    }
}