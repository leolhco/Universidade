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
 * Cria uma nova conta de acesso e ja deixa o visitante logado.
 */
@WebServlet("/cadastro")
public class CadastroServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    private final ContaDAO dao = new ContaDAO();

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        request.getRequestDispatcher("/cadastro.jsp").forward(request, response);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        request.setCharacterEncoding("UTF-8");

        String nome = valor(request.getParameter("nome"));
        String email = valor(request.getParameter("email"));
        String senha = request.getParameter("senha");
        String confirmacao = request.getParameter("confirmacao");

        try {
            if (nome.isEmpty() || email.isEmpty() || senha == null || senha.isEmpty()) {
                reexibirFormulario(request, response, nome, email, "Preencha todos os campos.");
                return;
            }

            if (senha.length() < 6) {
                reexibirFormulario(request, response, nome, email,
                        "A senha precisa ter pelo menos 6 caracteres.");
                return;
            }

            if (!senha.equals(confirmacao)) {
                reexibirFormulario(request, response, nome, email,
                        "As senhas nao conferem.");
                return;
            }

            if (dao.emailJaCadastrado(email)) {
                reexibirFormulario(request, response, nome, email,
                        "Ja existe uma conta com esse e-mail. Use a tela de entrar.");
                return;
            }

            Conta conta = new Conta(nome, email, Senha.gerarHash(senha));
            dao.inserir(conta);

            response.sendRedirect(request.getContextPath() + "/login.jsp?sucesso=1");

        } catch (RuntimeException e) {
            reexibirFormulario(request, response, nome, email,
                    "Erro ao criar a conta: " + e.getMessage());
        }
    }

    private String valor(String parametro) {
        return parametro == null ? "" : parametro.trim();
    }

    private void reexibirFormulario(HttpServletRequest request, HttpServletResponse response,
                                    String nome, String email, String mensagem)
            throws ServletException, IOException {

        request.setAttribute("mensagemErro", mensagem);
        request.setAttribute("nome", nome);
        request.setAttribute("email", email);
        request.getRequestDispatcher("/cadastro.jsp").forward(request, response);
    }
}
