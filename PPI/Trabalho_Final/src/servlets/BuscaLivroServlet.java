package servlets;

import java.io.IOException;
import java.util.List;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import dao.LivroDAO;
import entidade.Livro;

@WebServlet("/buscaLivro")
public class BuscaLivroServlet extends HttpServlet {
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String acao = request.getParameter("acao");
        LivroDAO dao = new LivroDAO();

        try {
            if ("pesquisaAvancada".equals(acao)) {
                String criterio = request.getParameter("criterio");
                String termo = request.getParameter("termo");
                
                List<Livro> resultados = dao.buscarAvancado(criterio, termo);
                
                request.setAttribute("listaLivros", resultados);
                request.getRequestDispatcher("listarLivros.jsp").forward(request, response);
            } else {
                response.sendRedirect("listarLivros.jsp");
            }
        } catch (Exception e) {
            request.setAttribute("mensagemErro", "Erro ao realizar a pesquisa de livro: " + e.getMessage());
            request.getRequestDispatcher("erro.jsp").forward(request, response);
        }
    }
}	