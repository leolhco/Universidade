import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class ConnectionFactory {
    private static final String url = "jdbc:mysql://localhost:3306/sistemaprojetos?useSSL=false&serverTimezone=UTC";
    private static final String user = "root";
    private static final String password = "senha";

    public static Connection getConnection() {
        try {
            // Força o carregamento do driver
            Class.forName("com.mysql.jdbc.Driver");
            return DriverManager.getConnection(url, user, password);
        } catch (ClassNotFoundException e) {
            throw new RuntimeException("Driver JDBC não encontrado: " + e.getMessage());
        } catch (SQLException e) {
            throw new RuntimeException("Erro na conexão: " + e.getMessage());
        }
    }
    
    public static void main(String args[]) {
    	System.out.println("Teste");
    	
    	getConenncti
    }
}
