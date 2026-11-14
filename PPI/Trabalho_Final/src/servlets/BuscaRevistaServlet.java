package servlets;


import java.io.IOException;
import java.util.List;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import dao.RevistaDAO;
import entidade.Revista;

@WebServlet("/buscaRevista")
public class BuscaRevistaServlet extends HttpServlet {
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String acao = request.getParameter("acao");
        RevistaDAO dao = new RevistaDAO();

        try {
            if ("pesquisaAvancada".equals(acao)) {
                String criterio = request.getParameter("criterio");
                String termo = request.getParameter("termo");
                
                List<Revista> resultados = dao.buscarAvancado(criterio, termo);
                request.setAttribute("listaRevistas", resultados);
                request.getRequestDispatcher("listarRevistas.jsp").forward(request, response);
            } else {
                response.sendRedirect("listarRevistas.jsp");
            }
        } catch (Exception e) {
            request.setAttribute("mensagemErro", "Erro ao realizar a pesquisa de revista: " + e.getMessage());
            request.getRequestDispatcher("erro.jsp").forward(request, response);
        }
    }
}