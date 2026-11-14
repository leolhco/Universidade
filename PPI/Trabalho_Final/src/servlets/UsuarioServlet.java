package servlets;

import java.io.IOException;
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
                Usuario usuario = new Usuario(
                        request.getParameter("nome"),
                        parseDate(request.getParameter("dataNascimento")),
                        request.getParameter("email"),
                        request.getParameter("telefone"));
                
                dao.inserir(usuario);
                response.sendRedirect("listarUsuarios.jsp");

            } else if ("alterar".equals(acao)) {
                Usuario usuario = new Usuario(
                        request.getParameter("nome"),
                        parseDate(request.getParameter("dataNascimento")),
                        request.getParameter("email"),
                        request.getParameter("telefone"));
                usuario.setId(parseLong(request.getParameter("id")));
                
                dao.atualizar(usuario);
                response.sendRedirect("listarUsuarios.jsp");

            } else if ("remover".equals(acao)) {
                Long id = parseLong(request.getParameter("id"));
                dao.deletar(id);
                response.sendRedirect("listarUsuarios.jsp");
                
            } else if ("consultar".equals(acao)) {
                response.sendRedirect("busca.jsp");
            }
            
        } catch (Exception e) {
            request.setAttribute("mensagemErro", "Erro ao processar usuário: " + e.getMessage());
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