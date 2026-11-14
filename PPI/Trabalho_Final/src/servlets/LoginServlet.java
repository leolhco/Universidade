package servlets;

import java.io.IOException;

import dao.ContaDAO;
import entidade.Conta;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;
import util.Senha;

/**
 * Autentica a conta e abre a sessao.
 *
 * Segue o padrao MVC das tarefas 7 e 8: o Servlet nao gera HTML, apenas
 * processa e encaminha (forward) para o JSP, ou redireciona para o index
 * quando o login da certo.
 */
@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    private final ContaDAO dao = new ContaDAO();

    /** Se alguem acessar /login pela URL, mostra o formulario. */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        request.getRequestDispatcher("/login.jsp").forward(request, response);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        request.setCharacterEncoding("UTF-8");

        String email = request.getParameter("email");
        String senha = request.getParameter("senha");

        if (email == null || email.isBlank() || senha == null || senha.isBlank()) {
            reexibirFormulario(request, response, email, "Informe o e-mail e a senha.");
            return;
        }

        try {
            Conta conta = dao.buscarPorEmail(email.trim());

            // Mensagem generica de proposito: nao revela se o e-mail existe.
            if (conta == null || !Senha.conferir(senha, conta.getSenha())) {
                reexibirFormulario(request, response, email, "E-mail ou senha incorretos.");
                return;
            }

            // Sessao nova a cada login (protecao contra session fixation).
            HttpSession sessaoAntiga = request.getSession(false);
            if (sessaoAntiga != null) {
                sessaoAntiga.invalidate();
            }

            HttpSession sessao = request.getSession(true);
            conta.setSenha(null); // nao guardar o hash na sessao
            sessao.setAttribute("contaLogada", conta);

            response.sendRedirect(request.getContextPath() + "/index.jsp");

        } catch (RuntimeException e) {
            reexibirFormulario(request, response, email, "Erro ao acessar: " + e.getMessage());
        }
    }

    private void reexibirFormulario(HttpServletRequest request, HttpServletResponse response,
                                    String email, String mensagem)
            throws ServletException, IOException {

        request.setAttribute("mensagemErro", mensagem);
        request.setAttribute("email", email); // devolve o e-mail digitado
        request.getRequestDispatcher("/login.jsp").forward(request, response);
    }
}
