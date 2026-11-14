package servlets;

import java.io.IOException;
import java.io.PrintWriter;
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
        out.println("<title>Autor</title></head><body>");

        try {
            if ("cadastrar".equals(acao)) {
                try {
                    Autor autor = new Autor(
                            request.getParameter("nomeReal"),
                            request.getParameter("nomeArtistico"),
                            parseDate(request.getParameter("dataNascimento")));
                    
                    dao.inserir(autor);
                    out.println("<p>Autor cadastrado com sucesso! ID gerado: " + autor.getId() + "</p>");
                } catch (RuntimeException e) {
                    out.println("<p style='color:red;'>Erro ao cadastrar: Verifique se os dados estão corretos.</p>");
                }

            } else if ("alterar".equals(acao)) {
                try {
                    Autor autor = new Autor(
                            request.getParameter("nomeReal"),
                            request.getParameter("nomeArtistico"),
                            parseDate(request.getParameter("dataNascimento")));
                    autor.setId(parseLong(request.getParameter("id")));
                    
                    dao.atualizar(autor);
                    out.println("<p>Autor de ID " + autor.getId() + " alterado.</p>");
                } catch (RuntimeException e) {
                    out.println("<p style='color:red;'>Erro ao atualizar: Verifique se os dados estão corretos.</p>");
                }

            } else if ("consultar".equals(acao)) {
                try {
                    Autor autor = dao.buscarPorId(parseLong(request.getParameter("id")));
                    if (autor != null) {
                        out.println("<p>ID: " + autor.getId() + "</p>");
                        out.println("<p>Nome real: " + autor.getNomeReal() + "</p>");
                        out.println("<p>Nome artistico: " + autor.getNomeArtistico() + "</p>");
                        out.println("<p>Data de nascimento: " + autor.getDataNascimento() + "</p>");
                    } else {
                        out.println("<p>Nenhum autor encontrado com esse ID.</p>");
                    }
                } catch (RuntimeException e) {
                    out.println("<p style='color:red;'>Erro ao consultar: " + e.getMessage() + "</p>");
                }

            } else if ("remover".equals(acao)) {
                Long id = parseLong(request.getParameter("id"));
                try {
                    dao.deletar(id);
                    out.println("<p>Autor de ID " + id + " removido.</p>");
                } catch (RuntimeException e) {
                    out.println("<p style='color:red;'>Erro ao deletar: Verifique se o ID está correto.</p>");
                }
            }
        } catch (Exception e) {
            out.println("<p style='color:red;'>Erro inesperado ao processar a requisição: " + e.getMessage() + "</p>");
        }

        out.println("<br><a href='autor.html'>Voltar</a>");
        out.println("</body></html>");
        out.close();
    }

    private Long parseLong(String valor) {
        if (valor == null || valor.trim().isEmpty()) return null;
        return Long.parseLong(valor.trim());
    }

    private Date parseDate(String valor) {
        if (valor == null || valor.trim().isEmpty()) return null;
        return Date.valueOf(valor.trim());
    }

    @Override
    public void destroy() {
        super.destroy();
    }
}