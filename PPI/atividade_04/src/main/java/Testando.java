import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.Statement;

public class Testando {
    public static void main(String[] args) {
        try {
            Connection conexao = ConnectionFactory.getConnection();

            if (conexao != null) {
                System.out.println("Conexão realizada com sucesso!");

                // Teste: listar registros da tabela Responsavel
                Statement stmt = conexao.createStatement();
                ResultSet rs = stmt.executeQuery("SELECT * FROM responsavel");

                while (rs.next()) {
                    System.out.println(
                        rs.getInt("idResponsavel") + " - " +
                        rs.getString("nome") + " - " +
                        rs.getString("email")
                    );
                }

                conexao.close();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
