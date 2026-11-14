package servlets;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Date;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import dao.UsuarioDAO;
import entidade.Usuario;

@WebServlet("/usuario")
public class UsuarioServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    private final UsuarioDAO dao = new UsuarioDAO();

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
        out.println("<title>Usuario</title></head><body>");

        try {
            if ("cadastrar".equals(acao)) {
                try {
                    Usuario usuario = new Usuario(
                            request.getParameter("nome"),
                            parseDate(request.getParameter("dataNascimento")),
                            request.getParameter("email"),
                            request.getParameter("telefone"));
                    
                    dao.inserir(usuario);
                    out.println("<p>Usuario cadastrado com sucesso! ID gerado: " + usuario.getId() + "</p>");
                } catch (RuntimeException e) {
                    out.println("<p style='color:red;'>Erro ao cadastrar: Verifique se os dados estão corretos.</p>");
                }

            } else if ("alterar".equals(acao)) {
                try {
                    Usuario usuario = new Usuario(
                            request.getParameter("nome"),
                            parseDate(request.getParameter("dataNascimento")),
                            request.getParameter("email"),
                            request.getParameter("telefone"));
                    usuario.setId(parseLong(request.getParameter("id")));
                    
                    dao.atualizar(usuario);
                    out.println("<p>Usuario de ID " + usuario.getId() + " alterado.</p>");
                } catch (RuntimeException e) {
                    out.println("<p style='color:red;'>Erro ao atualizar: Verifique se os dados estão corretos.</p>");
                }

            } else if ("consultar".equals(acao)) {
                try {
                    Usuario usuario = dao.buscarPorId(parseLong(request.getParameter("id")));
                    if (usuario != null) {
                        out.println("<p>ID: " + usuario.getId() + "</p>");
                        out.println("<p>Nome: " + usuario.getNome() + "</p>");
                        out.println("<p>Data de nascimento: " + usuario.getDataNascimento() + "</p>");
                        out.println("<p>E-mail: " + usuario.getEmail() + "</p>");
                        out.println("<p>Telefone: " + usuario.getTelefone() + "</p>");
                    } else {
                        out.println("<p>Nenhum usuario encontrado com esse ID.</p>");
                    }
                } catch (RuntimeException e) {
                    out.println("<p style='color:red;'>Erro ao consultar: " + e.getMessage() + "</p>");
                }

            } else if ("remover".equals(acao)) {
                Long id = parseLong(request.getParameter("id"));
                try {
                    dao.deletar(id);
                    out.println("<p>Usuario de ID " + id + " removido.</p>");
                } catch (RuntimeException e) {
                    out.println("<p style='color:red;'>Erro ao deletar: Verifique se o ID está correto.</p>");
                }
            }
        } catch (Exception e) {
            out.println("<p style='color:red;'>Erro inesperado ao processar a requisição: " + e.getMessage() + "</p>");
        }

        out.println("<br><a href='usuario.html'>Voltar</a>");
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