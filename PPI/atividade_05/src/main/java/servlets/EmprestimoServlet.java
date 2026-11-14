package servlets;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Date;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import dao.EmprestimoDAO;
import entidade.Emprestimo;

@WebServlet("/emprestimo")
public class EmprestimoServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    private final EmprestimoDAO dao = new EmprestimoDAO();

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
        out.println("<title>Emprestimo</title></head><body>");

        try {
            if ("cadastrar".equals(acao)) {
                try {
                    Long usuarioId = parseLong(request.getParameter("usuarioId"));
                    Long livroId = parseLong(request.getParameter("livroId"));
                    Long revistaId = parseLong(request.getParameter("revistaId"));

                    if (usuarioId == null) {
                        throw new RuntimeException("O ID do Usuário é obrigatório.");
                    }
                    if (livroId == null && revistaId == null) {
                        throw new RuntimeException("É necessário informar o ID de pelo menos um Livro ou Revista.");
                    }

                    Emprestimo emp = new Emprestimo(
                            parseDate(request.getParameter("dataEmprestimo")),
                            parseDate(request.getParameter("dataDevolucao")),
                            usuarioId,
                            livroId,
                            revistaId);
                    
                    dao.inserir(emp);
                    out.println("<p>Emprestimo cadastrado com sucesso! ID gerado: " + emp.getId() + "</p>");
                } catch (RuntimeException e) {
                    out.println("<p style='color:red;'>Erro ao cadastrar: " + e.getMessage() + " (Verifique se os IDs informados realmente existem no banco).</p>");
                }

            } else if ("alterar".equals(acao)) {
                try {
                    Long usuarioId = parseLong(request.getParameter("usuarioId"));
                    Long livroId = parseLong(request.getParameter("livroId"));
                    Long revistaId = parseLong(request.getParameter("revistaId"));

                    if (usuarioId == null) {
                        throw new RuntimeException("O ID do Usuário é obrigatório.");
                    }
                    if (livroId == null && revistaId == null) {
                        throw new RuntimeException("É necessário informar o ID de pelo menos um Livro ou Revista.");
                    }

                    Emprestimo emp = new Emprestimo(
                            parseDate(request.getParameter("dataEmprestimo")),
                            parseDate(request.getParameter("dataDevolucao")),
                            usuarioId,
                            livroId,
                            revistaId);
                    emp.setId(parseLong(request.getParameter("id")));
                    
                    dao.atualizar(emp);
                    out.println("<p>Emprestimo de ID " + emp.getId() + " alterado.</p>");
                } catch (RuntimeException e) {
                    out.println("<p style='color:red;'>Erro ao atualizar: " + e.getMessage() + " (Verifique se os IDs informados realmente existem no banco).</p>");
                }

            } else if ("consultar".equals(acao)) {
                try {
                    Emprestimo emp = dao.buscarPorId(parseLong(request.getParameter("id")));
                    if (emp != null) {
                        out.println("<p>ID: " + emp.getId() + "</p>");
                        out.println("<p>Data do emprestimo: " + emp.getDataEmprestimo() + "</p>");
                        out.println("<p>Data de devolucao: " + emp.getDataDevolucao() + "</p>");
                        out.println("<p>Usuario (ID): " + emp.getUsuarioId() + "</p>");
                        out.println("<p>Livro (ID): " + (emp.getLivroId() != null ? emp.getLivroId() : "N/A") + "</p>");
                        out.println("<p>Revista (ID): " + (emp.getRevistaId() != null ? emp.getRevistaId() : "N/A") + "</p>");
                    } else {
                        out.println("<p>Nenhum emprestimo encontrado com esse ID.</p>");
                    }
                } catch (RuntimeException e) {
                    out.println("<p style='color:red;'>Erro ao consultar: " + e.getMessage() + "</p>");
                }

            } else if ("remover".equals(acao)) {
                Long id = parseLong(request.getParameter("id"));
                try {
                    dao.deletar(id);
                    out.println("<p>Emprestimo de ID " + id + " removido.</p>");
                } catch (RuntimeException e) {
                    out.println("<p style='color:red;'>Erro ao deletar: Verifique se o ID está correto.</p>");
                }
            }
        } catch (Exception e) {
            out.println("<p style='color:red;'>Erro inesperado ao processar a requisição: " + e.getMessage() + "</p>");
        }

        out.println("<br><a href='emprestimo.html'>Voltar</a>");
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