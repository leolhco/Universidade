package servlets;

import java.io.IOException;
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
                Long usuarioId = parseLong(request.getParameter("usuarioId"));
                Long livroId = parseLong(request.getParameter("livroId"));
                Long revistaId = parseLong(request.getParameter("revistaId"));

                if (usuarioId == null) throw new RuntimeException("O ID do Usuário é obrigatório.");
                if (livroId == null && revistaId == null) throw new RuntimeException("Informe o ID de pelo menos um Livro ou Revista.");

                Emprestimo emp = new Emprestimo(
                        parseDate(request.getParameter("dataEmprestimo")),
                        parseDate(request.getParameter("dataDevolucao")),
                        usuarioId, livroId, revistaId);
                
                dao.inserir(emp);
                response.sendRedirect("listarEmprestimos.jsp");

            } else if ("alterar".equals(acao)) {
                Long usuarioId = parseLong(request.getParameter("usuarioId"));
                Long livroId = parseLong(request.getParameter("livroId"));
                Long revistaId = parseLong(request.getParameter("revistaId"));

                Emprestimo emp = new Emprestimo(
                        parseDate(request.getParameter("dataEmprestimo")),
                        parseDate(request.getParameter("dataDevolucao")),
                        usuarioId, livroId, revistaId);
                emp.setId(parseLong(request.getParameter("id")));
                
                dao.atualizar(emp);
                response.sendRedirect("listarEmprestimos.jsp");

            } else if ("remover".equals(acao)) {
                Long id = parseLong(request.getParameter("id"));
                dao.deletar(id);
                response.sendRedirect("listarEmprestimos.jsp");
                
            } else if ("consultar".equals(acao)) {
                Long id = parseLong(request.getParameter("id"));
                Emprestimo emp = dao.buscarPorId(id);
                
                if (emp != null) {
                    request.setAttribute("emprestimo", emp);
                    request.getRequestDispatcher("sucessoBuscaEmprestimo.jsp").forward(request, response);
                } else {
                    throw new RuntimeException("Nenhum empréstimo encontrado com o ID informado.");
                }
            }
            
        } catch (Exception e) {
            request.setAttribute("mensagemErro", "Erro ao processar empréstimo: " + e.getMessage());
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