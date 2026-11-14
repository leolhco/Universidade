package servlets;

import java.io.IOException;
import java.io.PrintWriter;

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
    public void init() throws ServletException {
        super.init();
    }

    @Override
    protected void service(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        processar(req, resp);
    }

    private void processar(HttpServletRequest request, HttpServletResponse response) throws IOException {
        request.setCharacterEncoding("UTF-8");
        response.setContentType("text/html;charset=UTF-8");

        String acao = request.getParameter("acao");
        PrintWriter out = response.getWriter();

        out.println("<!DOCTYPE html><html><head><meta charset='UTF-8'>");
        out.println("<title>Livro</title></head><body>");

        try {
            if ("cadastrar".equals(acao)) {
                Livro livro = new Livro(
                        request.getParameter("nome"),
                        request.getParameter("editora"),
                        parseLong(request.getParameter("autorId")));
                try {
                     dao.inserir(livro);
                     out.println("<p>Livro cadastrado com sucesso! ID gerado: " + livro.getId() + "</p>");
                } catch (RuntimeException e) {
                     out.println("<p style='color:red;'>Erro ao cadastrar: Verifique se os dados e o ID do Autor estão corretos.</p>");
                }

            } else if ("alterar".equals(acao)) {
                Livro livro = new Livro(
                        request.getParameter("nome"),
                        request.getParameter("editora"),
                        parseLong(request.getParameter("autorId")));
                livro.setId(parseLong(request.getParameter("id")));
                try {
                     dao.atualizar(livro);
                     out.println("<p>Livro atualizado com sucesso!</p>");
                } catch (RuntimeException e) {
                     out.println("<p style='color:red;'>Erro ao atualizar: Verifique se os dados e o ID do Autor estão corretos.</p>");
                }

            } else if ("consultar".equals(acao)) {
                try {
                    Livro livro = dao.buscarPorId(parseLong(request.getParameter("id")));
                    if (livro != null) {
                        out.println("<p>ID: " + livro.getId() + "</p>");
                        out.println("<p>Nome: " + livro.getNome() + "</p>");
                        out.println("<p>Editora: " + livro.getEditora() + "</p>");
                        out.println("<p>Autor (ID): " + livro.getAutorId() + "</p>");
                    } else {
                        out.println("<p>Nenhum livro encontrado com esse ID.</p>");
                    }
                } catch (RuntimeException e) {
                    out.println("<p style='color:red;'>Erro ao consultar: " + e.getMessage() + "</p>");
                }

            } else if ("remover".equals(acao)) {
                Long id = parseLong(request.getParameter("id"));
                try {
                     dao.deletar(id);
                     out.println("<p>Livro deletado com sucesso!</p>");
                } catch (RuntimeException e) {
                     out.println("<p style='color:red;'>Erro ao deletar: Verifique se o ID está correto.</p>");
                }
            }
        } catch (Exception e) {
            out.println("<p style='color:red;'>Erro inesperado ao processar a requisição: " + e.getMessage() + "</p>");
        }

        out.println("<br><a href='livro.html'>Voltar</a>");
        out.println("</body></html>");
        out.close();
    }

    private Long parseLong(String valor) {
        if (valor == null || valor.trim().isEmpty()) return null;
        return Long.parseLong(valor.trim());
    }
    
    @Override
    public void destroy() {
        super.destroy();
    }
}