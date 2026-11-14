package servlets;

import java.io.IOException;
import java.sql.Date;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import dao.AutorDAO;
import entidade.Autor;

@WebServlet("/autor")
public class AutorServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    private final AutorDAO dao = new AutorDAO();

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
                Autor autor = new Autor(
                        request.getParameter("nomeReal"),
                        request.getParameter("nomeArtistico"),
                        parseDate(request.getParameter("dataNascimento")));
                
                dao.inserir(autor);
                response.sendRedirect("listarAutores.jsp");

            } else if ("alterar".equals(acao)) {
                Autor autor = new Autor(
                        request.getParameter("nomeReal"),
                        request.getParameter("nomeArtistico"),
                        parseDate(request.getParameter("dataNascimento")));
                autor.setId(parseLong(request.getParameter("id")));
                
                dao.atualizar(autor);
                response.sendRedirect("listarAutores.jsp");

            } else if ("remover".equals(acao)) {
                Long id = parseLong(request.getParameter("id"));
                dao.deletar(id);
                response.sendRedirect("listarAutores.jsp");
                
            } else if ("consultar".equals(acao)) {
                // Redireciona para a nova central de buscas inteligente
                response.sendRedirect("busca.jsp");
            }
            
        } catch (Exception e) {
            request.setAttribute("mensagemErro", "Erro ao processar autor: " + e.getMessage());
            request.getRequestDispatcher("erro.jsp").forward(request, response);
        }
    }

    private Long parseLong(String valor) {
        if (valor == null || valor.trim().isEmpty()) return null;
        return Long.parseLong(valor.trim());
    }

    private Date parseDate(String valor) {
        if (valor == null || valor.trim().isEmpty()) return null;
        return Date.valueOf(valor.trim());
    }
}