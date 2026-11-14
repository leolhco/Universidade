package dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;
import entidade.Emprestimo;
import conexao.ConnectionFactory;

public class EmprestimoDAO {
    
    public void inserir(Emprestimo emprestimo) {
        String sql = "INSERT INTO emprestimo (data_emprestimo, data_devolucao, usuario_id, livro_id, revista_id) VALUES (?, ?, ?, ?, ?)";
        try (Connection conn = new ConnectionFactory().getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS)) {
            
            stmt.setDate(1, emprestimo.getDataEmprestimo());
            stmt.setDate(2, emprestimo.getDataDevolucao());
            stmt.setLong(3, emprestimo.getUsuarioId());
            
            if (emprestimo.getLivroId() != null) {
                stmt.setLong(4, emprestimo.getLivroId());
            } else {
                stmt.setNull(4, java.sql.Types.BIGINT);
            }
            
            if (emprestimo.getRevistaId() != null) {
                stmt.setLong(5, emprestimo.getRevistaId());
            } else {
                stmt.setNull(5, java.sql.Types.BIGINT);
            }
            
            stmt.executeUpdate();
            
            ResultSet rs = stmt.getGeneratedKeys();
            if (rs.next()) {
                emprestimo.setId(rs.getLong(1));
            }
            System.out.println("Emprestimo inserido com sucesso! ID: " + emprestimo.getId());
        } catch (SQLException e) {
            throw new RuntimeException("Erro ao inserir emprestimo no banco de dados.", e);
        }
    }
    
    public List<Emprestimo> listarTodos() {
        List<Emprestimo> emprestimos = new ArrayList<>();
        String sql = "SELECT * FROM emprestimo";
        try (Connection conn = new ConnectionFactory().getConnection();
             Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery(sql)) {
            
            while (rs.next()) {
                Emprestimo emprestimo = new Emprestimo();
                emprestimo.setId(rs.getLong("id"));
                emprestimo.setDataEmprestimo(rs.getDate("data_emprestimo"));
                emprestimo.setDataDevolucao(rs.getDate("data_devolucao"));
                emprestimo.setUsuarioId(rs.getLong("usuario_id"));
                
                long livroId = rs.getLong("livro_id");
                if (!rs.wasNull()) {
                    emprestimo.setLivroId(livroId);
                }
                
                long revistaId = rs.getLong("revista_id");
                if (!rs.wasNull()) {
                    emprestimo.setRevistaId(revistaId);
                }
                
                emprestimos.add(emprestimo);
            }
        } catch (SQLException e) {
            throw new RuntimeException("Erro ao listar emprestimos do banco de dados.", e);
        }
        return emprestimos;
    }
    
    public List<String> listarTodosComDetalhes() {
        List<String> emprestimosDetalhados = new ArrayList<>();
        String sql = "SELECT e.id, e.data_emprestimo, e.data_devolucao, " +
                     "u.nome as usuario_nome, " +
                     "l.nome as livro_nome, " +
                     "r.titulo as revista_titulo " +
                     "FROM emprestimo e " +
                     "LEFT JOIN usuario u ON e.usuario_id = u.id " +
                     "LEFT JOIN livro l ON e.livro_id = l.id " +
                     "LEFT JOIN revista r ON e.revista_id = r.id";
        
        try (Connection conn = new ConnectionFactory().getConnection();
             Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery(sql)) {
            
            while (rs.next()) {
                String livroNome = rs.getString("livro_nome");
                String revistaTitulo = rs.getString("revista_titulo");
                String itemNome = (livroNome != null) ? livroNome : revistaTitulo;
                String tipoItem = (livroNome != null) ? "LIVRO" : "REVISTA";
                
                String detalhe = "Emprestimo ID: " + rs.getLong("id") +
                                 " | Usuario: " + rs.getString("usuario_nome") +
                                 " | Item: " + itemNome +
                                 " (" + tipoItem + ")" +
                                 " | Emprestimo: " + rs.getDate("data_emprestimo") +
                                 " | Devolucao: " + rs.getDate("data_devolucao");
                emprestimosDetalhados.add(detalhe);
            }
        } catch (SQLException e) {
            throw new RuntimeException("Erro ao listar emprestimos com detalhes.", e);
        }
        return emprestimosDetalhados;
    }
    
    public Emprestimo buscarPorId(Long id) {
        String sql = "SELECT * FROM emprestimo WHERE id = ?";
        try (Connection conn = new ConnectionFactory().getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            
            stmt.setLong(1, id);
            ResultSet rs = stmt.executeQuery();
            
            if (rs.next()) {
                Emprestimo emprestimo = new Emprestimo();
                emprestimo.setId(rs.getLong("id"));
                emprestimo.setDataEmprestimo(rs.getDate("data_emprestimo"));
                emprestimo.setDataDevolucao(rs.getDate("data_devolucao"));
                emprestimo.setUsuarioId(rs.getLong("usuario_id"));
                
                long livroId = rs.getLong("livro_id");
                if (!rs.wasNull()) {
                    emprestimo.setLivroId(livroId);
                }
                
                long revistaId = rs.getLong("revista_id");
                if (!rs.wasNull()) {
                    emprestimo.setRevistaId(revistaId);
                }
                
                return emprestimo;
            }
        } catch (SQLException e) {
            throw new RuntimeException("Erro ao buscar emprestimo no banco de dados.", e);
        }
        return null;
    }
    
    public void atualizar(Emprestimo emprestimo) {
        String sql = "UPDATE emprestimo SET data_emprestimo = ?, data_devolucao = ?, usuario_id = ?, livro_id = ?, revista_id = ? WHERE id = ?";
        try (Connection conn = new ConnectionFactory().getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            
            stmt.setDate(1, emprestimo.getDataEmprestimo());
            stmt.setDate(2, emprestimo.getDataDevolucao());
            stmt.setLong(3, emprestimo.getUsuarioId());
            
            if (emprestimo.getLivroId() != null) {
                stmt.setLong(4, emprestimo.getLivroId());
            } else {
                stmt.setNull(4, java.sql.Types.BIGINT);
            }
            
            if (emprestimo.getRevistaId() != null) {
                stmt.setLong(5, emprestimo.getRevistaId());
            } else {
                stmt.setNull(5, java.sql.Types.BIGINT);
            }
            
            stmt.setLong(6, emprestimo.getId());
            
            int rows = stmt.executeUpdate();
            if (rows > 0) {
                System.out.println("Emprestimo atualizado com sucesso!");
            } else {
                System.out.println("Nenhum emprestimo encontrado com ID: " + emprestimo.getId());
            }
        } catch (SQLException e) {
            throw new RuntimeException("Erro ao atualizar emprestimo no banco de dados.", e);
        }
    }
    
    public void deletar(Long id) {
        String sql = "DELETE FROM emprestimo WHERE id = ?";
        try (Connection conn = new ConnectionFactory().getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            
            stmt.setLong(1, id);
            int rows = stmt.executeUpdate();
            if (rows > 0) {
                System.out.println("Emprestimo deletado com sucesso!");
            } else {
                System.out.println("Nenhum emprestimo encontrado com ID: " + id);
            }
        } catch (SQLException e) {
            throw new RuntimeException("Erro ao deletar emprestimo do banco de dados.", e);
        }
    }
}