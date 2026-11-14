import java.sql.*;
import java.util.*;

public class ResponsavelDao {
    private Connection connection;

    public ResponsavelDao() {
        this.connection = ConnectionFactory.getConnection();
    }

    public void adiciona(Responsavel r) {
        String sql = "INSERT INTO Responsavel (nome, email) VALUES (?, ?)";
        try {
            PreparedStatement stmt = connection.prepareStatement(sql);
            stmt.setString(1, r.getNome());
            stmt.setString(2, r.getEmail());
            stmt.execute();
            stmt.close();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public List<Responsavel> listaTodos() {
        List<Responsavel> lista = new ArrayList<>();
        String sql = "SELECT * FROM Responsavel";
        try {
            Statement stmt = connection.createStatement();
            ResultSet rs = stmt.executeQuery(sql);
            while (rs.next()) {
                Responsavel r = new Responsavel(rs.getString("nome"), rs.getString("email"));
                lista.add(r);
            }
            rs.close();
            stmt.close();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return lista;
    }
}
