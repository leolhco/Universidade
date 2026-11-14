package dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;
import entidade.Revista;
import conexao.ConnectionFactory;

public class RevistaDAO {
    
    public void inserir(Revista revista) {
        String sql = "INSERT INTO revista (titulo, editora, numero_edicao, ano_publicacao, mes_publicacao, issn, periodicidade) VALUES (?, ?, ?, ?, ?, ?, ?)";
        try (Connection conn = new ConnectionFactory().getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS)) {
            
            stmt.setString(1, revista.getTitulo());
            stmt.setString(2, revista.getEditora());
            stmt.setInt(3, revista.getNumeroEdicao());
            stmt.setInt(4, revista.getAnoPublicacao());
            stmt.setString(5, revista.getMesPublicacao());
            stmt.setString(6, revista.getIssn());
            stmt.setString(7, revista.getPeriodicidade());
            
            stmt.executeUpdate();
            
            ResultSet rs = stmt.getGeneratedKeys();
            if (rs.next()) {
                revista.setId(rs.getLong(1));
            }
            System.out.println("Revista inserida com sucesso! ID: " + revista.getId());
        } catch (SQLException e) {
            throw new RuntimeException("Erro ao inserir revista no banco de dados.", e);
        }
    }
    
    public List<Revista> listarTodos() {
        List<Revista> revistas = new ArrayList<>();
        String sql = "SELECT * FROM revista";
        try (Connection conn = new ConnectionFactory().getConnection();
             Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery(sql)) {
            
            while (rs.next()) {
                Revista revista = new Revista();
                revista.setId(rs.getLong("id"));
                revista.setTitulo(rs.getString("titulo"));
                revista.setEditora(rs.getString("editora"));
                revista.setNumeroEdicao(rs.getInt("numero_edicao"));
                revista.setAnoPublicacao(rs.getInt("ano_publicacao"));
                revista.setMesPublicacao(rs.getString("mes_publicacao"));
                revista.setIssn(rs.getString("issn"));
                revista.setPeriodicidade(rs.getString("periodicidade"));
                revistas.add(revista);
            }
        } catch (SQLException e) {
            throw new RuntimeException("Erro ao listar revistas do banco de dados.", e);
        }
        return revistas;
    }
    
    public Revista buscarPorId(Long id) {
        String sql = "SELECT * FROM revista WHERE id = ?";
        try (Connection conn = new ConnectionFactory().getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            
            stmt.setLong(1, id);
            ResultSet rs = stmt.executeQuery();
            
            if (rs.next()) {
                Revista revista = new Revista();
                revista.setId(rs.getLong("id"));
                revista.setTitulo(rs.getString("titulo"));
                revista.setEditora(rs.getString("editora"));
                revista.setNumeroEdicao(rs.getInt("numero_edicao"));
                revista.setAnoPublicacao(rs.getInt("ano_publicacao"));
                revista.setMesPublicacao(rs.getString("mes_publicacao"));
                revista.setIssn(rs.getString("issn"));
                revista.setPeriodicidade(rs.getString("periodicidade"));
                return revista;
            }
        } catch (SQLException e) {
            throw new RuntimeException("Erro ao buscar revista no banco de dados.", e);
        }
        return null;
    }
    
    // NOVO MÉTODO PARA A TELA DE BUSCA
    public List<Revista> buscarAvancado(String criterio, String termo) {
        List<Revista> revistas = new ArrayList<>();
        String sql;
        
        if ("ano_publicacao".equals(criterio)) {
            sql = "SELECT * FROM revista WHERE ano_publicacao = ?";
        } else if ("issn".equals(criterio)) {
            sql = "SELECT * FROM revista WHERE issn LIKE ?";
        } else if ("editora".equals(criterio)) {
            sql = "SELECT * FROM revista WHERE editora LIKE ?";
        } else {
            sql = "SELECT * FROM revista WHERE titulo LIKE ?";
        }

        try (Connection conn = new ConnectionFactory().getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            
            if ("ano_publicacao".equals(criterio)) {
                stmt.setInt(1, Integer.parseInt(termo));
            } else {
                stmt.setString(1, "%" + termo + "%");
            }
            
            ResultSet rs = stmt.executeQuery();
            while (rs.next()) {
                Revista revista = new Revista();
                revista.setId(rs.getLong("id"));
                revista.setTitulo(rs.getString("titulo"));
                revista.setEditora(rs.getString("editora"));
                revista.setNumeroEdicao(rs.getInt("numero_edicao"));
                revista.setAnoPublicacao(rs.getInt("ano_publicacao"));
                revista.setMesPublicacao(rs.getString("mes_publicacao"));
                revista.setIssn(rs.getString("issn"));
                revista.setPeriodicidade(rs.getString("periodicidade"));
                revistas.add(revista);
            }
        } catch (SQLException | NumberFormatException e) {
            throw new RuntimeException("Erro ao realizar busca avancada de revista.", e);
        }
        return revistas;
    }
    
    public void atualizar(Revista revista) {
        String sql = "UPDATE revista SET titulo = ?, editora = ?, numero_edicao = ?, ano_publicacao = ?, mes_publicacao = ?, issn = ?, periodicidade = ? WHERE id = ?";
        try (Connection conn = new ConnectionFactory().getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            
            stmt.setString(1, revista.getTitulo());
            stmt.setString(2, revista.getEditora());
            stmt.setInt(3, revista.getNumeroEdicao());
            stmt.setInt(4, revista.getAnoPublicacao());
            stmt.setString(5, revista.getMesPublicacao());
            stmt.setString(6, revista.getIssn());
            stmt.setString(7, revista.getPeriodicidade());
            stmt.setLong(8, revista.getId());
            
            int rows = stmt.executeUpdate();
            if (rows == 0) {
                throw new RuntimeException("Nenhuma revista encontrada para alteração com o ID: " + revista.getId());
            }
        } catch (SQLException e) {
            throw new RuntimeException("Erro ao atualizar revista no banco de dados.", e);
        }
    }
    
    public void deletar(Long id) {
        String sql = "DELETE FROM revista WHERE id = ?";
        try (Connection conn = new ConnectionFactory().getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            
            stmt.setLong(1, id);
            int rows = stmt.executeUpdate();
            if (rows == 0) {
                throw new RuntimeException("Não foi possível remover: Nenhuma revista encontrada com o ID: " + id);
            }
        } catch (SQLException e) {
            throw new RuntimeException("Erro ao deletar revista do banco de dados.", e);
        }
    }
}