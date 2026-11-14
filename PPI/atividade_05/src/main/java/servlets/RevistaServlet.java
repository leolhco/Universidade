package servlets;

import java.io.IOException;
import java.io.PrintWriter;

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
        out.println("<title>Revista</title></head><body>");

        try {
            if ("cadastrar".equals(acao)) {
                try {
                    Revista revista = new Revista(
                            request.getParameter("titulo"),
                            request.getParameter("editora"),
                            parseInt(request.getParameter("numeroEdicao")),
                            parseInt(request.getParameter("anoPublicacao")),
                            request.getParameter("mesPublicacao"),
                            request.getParameter("issn"),
                            request.getParameter("periodicidade"));
                    
                    dao.inserir(revista);
                    out.println("<p>Revista cadastrada com sucesso! ID gerado: " + revista.getId() + "</p>");
                } catch (RuntimeException e) {
                    out.println("<p style='color:red;'>Erro ao cadastrar: Verifique se os dados estão corretos.</p>");
                }

            } else if ("alterar".equals(acao)) {
                try {
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
                    out.println("<p>Revista de ID " + revista.getId() + " alterada.</p>");
                } catch (RuntimeException e) {
                    out.println("<p style='color:red;'>Erro ao atualizar: Verifique se os dados estão corretos.</p>");
                }

            } else if ("consultar".equals(acao)) {
                try {
                    Revista revista = dao.buscarPorId(parseLong(request.getParameter("id")));
                    if (revista != null) {
                        out.println("<p>ID: " + revista.getId() + "</p>");
                        out.println("<p>Titulo: " + revista.getTitulo() + "</p>");
                        out.println("<p>Editora: " + revista.getEditora() + "</p>");
                        out.println("<p>Numero da edicao: " + revista.getNumeroEdicao() + "</p>");
                        out.println("<p>Ano de publicacao: " + revista.getAnoPublicacao() + "</p>");
                        out.println("<p>Mes de publicacao: " + revista.getMesPublicacao() + "</p>");
                        out.println("<p>ISSN: " + revista.getIssn() + "</p>");
                        out.println("<p>Periodicidade: " + revista.getPeriodicidade() + "</p>");
                    } else {
                        out.println("<p>Nenhuma revista encontrada com esse ID.</p>");
                    }
                } catch (RuntimeException e) {
                    out.println("<p style='color:red;'>Erro ao consultar: " + e.getMessage() + "</p>");
                }

            } else if ("remover".equals(acao)) {
                Long id = parseLong(request.getParameter("id"));
                try {
                    dao.deletar(id);
                    out.println("<p>Revista de ID " + id + " removida.</p>");
                } catch (RuntimeException e) {
                    out.println("<p style='color:red;'>Erro ao deletar: Verifique se o ID está correto.</p>");
                }
            }
        } catch (Exception e) {
            
            out.println("<p style='color:red;'>Erro inesperado ao processar a requisição: " + e.getMessage() + "</p>");
        }

        out.println("<br><a href='revista.html'>Voltar</a>");
        out.println("</body></html>");
        out.close();
    }

    private Long parseLong(String valor) {
        if (valor == null || valor.trim().isEmpty()) return null;
        return Long.parseLong(valor.trim());
    }

    private Integer parseInt(String valor) {
        if (valor == null || valor.trim().isEmpty()) return null;
        return Integer.parseInt(valor.trim());
    }
    
    @Override
    public void destroy()  {
        super.destroy();
    }
}