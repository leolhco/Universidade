package servlets;

import java.io.IOException;
import java.util.List;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import dao.AutorDAO;
import entidade.Autor;

@WebServlet("/buscaAutor")
public class BuscaAutorServlet extends HttpServlet {
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String acao = request.getParameter("acao");
        AutorDAO dao = new AutorDAO();

        try {
            if ("pesquisaAvancada".equals(acao)) {
                String criterio = request.getParameter("criterio");
                String termo = request.getParameter("termo");
                
                List<Autor> resultados = dao.buscarAvancado(criterio, termo);
                request.setAttribute("listaAutores", resultados);
                request.getRequestDispatcher("listarAutores.jsp").forward(request, response);
            } else {
                response.sendRedirect("listarAutores.jsp");
            }
        } catch (Exception e) {
            request.setAttribute("mensagemErro", "Erro ao realizar a pesquisa de autor: " + e.getMessage());
            request.getRequestDispatcher("erro.jsp").forward(request, response);
        }
    }
}