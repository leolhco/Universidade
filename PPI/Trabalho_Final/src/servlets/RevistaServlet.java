package servlets;

import java.io.IOException;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import dao.RevistaDAO;
import entidade.Revista;

@WebServlet("/revista")
public class RevistaServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    private final RevistaDAO dao = new RevistaDAO();

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        processar(request, response);
    }
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        processar(request, response);
    }

    private void processar(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.setCharacterEncoding("UTF-8");
        String acao = request.getParameter("acao");

        try {
            if ("cadastrar".equals(acao)) {
                Revista revista = new Revista(
                        request.getParameter("titulo"),
                        request.getParameter("editora"),
                        parseInt(request.getParameter("numeroEdicao")),
                        parseInt(request.getParameter("anoPublicacao")),
                        request.getParameter("mesPublicacao"),
                        request.getParameter("issn"),
                        request.getParameter("periodicidade"));
                
                dao.inserir(revista);
                response.sendRedirect("listarRevistas.jsp");

            } else if ("alterar".equals(acao)) {
                Revista revista = new Revista(
                        request.getParameter("titulo"),
                        request.getParameter("editora"),
                        parseInt(request.getParameter("numeroEdicao")),
                        parseInt(request.getParameter("anoPublicacao")),
                        request.getParameter("mesPublicacao"),
                        request.getParameter("issn"),
                        request.getParameter("periodicidade"));
                revista.setId(parseLong(request.getParameter("id")));
                
                dao.atualizar(revista);
                response.sendRedirect("listarRevistas.jsp");

            } else if ("remover".equals(acao)) {
                Long id = parseLong(request.getParameter("id"));
                dao.deletar(id);
                response.sendRedirect("listarRevistas.jsp");
                
            } else if ("consultar".equals(acao)) {
                response.sendRedirect("busca.jsp");
            }
            
        } catch (Exception e) {
            request.setAttribute("mensagemErro", "Erro ao processar revista: " + e.getMessage());
            request.getRequestDispatcher("erro.jsp").forward(request, response);
        }
    }

    private Long parseLong(String valor) {
        if (valor == null || valor.trim().isEmpty()) return null;
        return Long.parseLong(valor.trim());
    }

    private Integer parseInt(String valor) {
        if (valor == null || valor.trim().isEmpty()) return null;
        return Integer.parseInt(valor.trim());
    }
}	