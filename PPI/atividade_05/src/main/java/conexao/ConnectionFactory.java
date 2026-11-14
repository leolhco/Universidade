package conexao;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class ConnectionFactory {
    
    static String databaseName = "ppi04"; 
    static String username = "root";      
    static String password = "senha";     
    static String url = "jdbc:mysql://localhost:3306/" + databaseName + "?useSSL=false&useTimezone=true&serverTimezone=UTC";

    public Connection getConnection() {
       
        try {
            
            Class.forName("com.mysql.cj.jdbc.Driver");
           
            return DriverManager.getConnection(url, username, password);
        
        } catch (SQLException e) {
            throw new RuntimeException("Erro ao conectar com o banco de dados: " + e.getMessage(), e);
        
        } catch (ClassNotFoundException e) {
            throw new RuntimeException("Driver do MySQL não encontrado! Verifique o Passo 2.", e);
        }
    
    }
}