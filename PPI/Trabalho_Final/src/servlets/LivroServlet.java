package servlets;

import java.io.IOException;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import dao.LivroDAO;
import entidade.Livro;

@WebServlet("/livro")
public class LivroServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    private final LivroDAO dao = new LivroDAO();

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
                Livro livro = new Livro(
                        request.getParameter("nome"),
                        request.getParameter("editora"),
                        parseLong(request.getParameter("autorId")));
                
                dao.inserir(livro);
                response.sendRedirect("listarLivros.jsp");

            } else if ("alterar".equals(acao)) {
                Livro livro = new Livro(
                        request.getParameter("nome"),
                        request.getParameter("editora"),
                        parseLong(request.getParameter("autorId")));
                livro.setId(parseLong(request.getParameter("id")));
                
                dao.atualizar(livro);
                response.sendRedirect("listarLivros.jsp");

            } else if ("remover".equals(acao)) {
                Long id = parseLong(request.getParameter("id"));
                dao.deletar(id);
                response.sendRedirect("listarLivros.jsp");
                
            } else if ("consultar".equals(acao)) {
                response.sendRedirect("busca.jsp");
            }
            
        } catch (Exception e) {
            request.setAttribute("mensagemErro", "Erro ao processar livro: " + e.getMessage());
            request.getRequestDispatcher("erro.jsp").forward(request, response);
        }
    }

    private Long parseLong(String valor) {
        if (valor == null || valor.trim().isEmpty()) return null;
        return Long.parseLong(valor.trim());
    }
}