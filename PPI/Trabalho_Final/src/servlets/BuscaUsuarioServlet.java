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

@WebServlet("/buscaUsuario")
public class BuscaUsuarioServlet extends HttpServlet {
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String acao = request.getParameter("acao");
        UsuarioDAO dao = new UsuarioDAO();

        try {
            if ("pesquisaAvancada".equals(acao)) {
                String criterio = request.getParameter("criterio");
                String termo = request.getParameter("termo");
                
                List<Usuario> resultados = dao.buscarAvancado(criterio, termo);
                request.setAttribute("listaUsuarios", resultados);
                request.getRequestDispatcher("listarUsuarios.jsp").forward(request, response);
                
            } else {
                String idParam = request.getParameter("id");
                if (idParam != null && !idParam.isEmpty()) {
                    Usuario usuario = dao.buscarPorId(Long.parseLong(idParam));
                    
                    if (usuario != null) {
                        request.setAttribute("usuario", usuario);
                        request.setAttribute("encontrado", true);
                    } else {
                        request.setAttribute("mensagemErro", "Nenhum usuário localizado com o ID: " + idParam);
                        request.setAttribute("encontrado", false);
                    }
                }
                request.getRequestDispatcher("roteadorBusca.jsp").forward(request, response);
            }
            
        } catch (Exception e) {
            request.setAttribute("mensagemErro", "Erro ao realizar a pesquisa de usuário: " + e.getMessage());
            request.getRequestDispatcher("erro.jsp").forward(request, response);
        }
    }
}