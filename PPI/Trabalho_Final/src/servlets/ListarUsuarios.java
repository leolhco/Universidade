package servlets;

import java.io.IOException;
import java.util.List;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import dao.UsuarioDAO;
import entidade.Usuario;

// Mapeamento exclusivo para listar usuários
@WebServlet("/listarUsuarios")
public class ListarUsuarios extends HttpServlet {
    private static final long serialVersionUID = 1L;

    private final UsuarioDAO dao = new UsuarioDAO();

    @Override
    protected void service(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.setCharacterEncoding("UTF-8");
        
        try {
            List<Usuario> usuarios = dao.listarTodos();

            request.setAttribute("listaUsuarios", usuarios);

        } catch (Exception e) {
            request.setAttribute("mensagemErro", "Erro ao buscar usuários: " + e.getMessage());
        }

        // 3. Encaminha para o JSP de usuários
        request.getRequestDispatcher("/listarUsuarios.jsp").forward(request, response);
    }
}