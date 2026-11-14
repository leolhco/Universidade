package filtros;

import java.io.IOException;
import java.util.Set;

import jakarta.servlet.DispatcherType;
import jakarta.servlet.Filter;
import jakarta.servlet.FilterChain;
import jakarta.servlet.ServletException;
import jakarta.servlet.ServletRequest;
import jakarta.servlet.ServletResponse;
import jakarta.servlet.annotation.WebFilter;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;

/**
 * Porteiro do sistema.
 *
 * Intercepta TODA requisicao. Se nao houver uma conta na sessao, manda o
 * visitante para a tela de entrada. Assim nenhuma pagina (index.jsp, os
 * CRUDs, o upload, os servlets) fica acessivel digitando a URL direto.
 *
 * Um Filter roda antes dos Servlets/JSPs, o que evita ter que repetir a
 * verificacao de login no topo de cada pagina.
 */
@WebFilter(urlPatterns = "/*",
           dispatcherTypes = { DispatcherType.REQUEST, DispatcherType.ERROR })
public class AutenticacaoFilter implements Filter {

    /** Enderecos que podem ser acessados sem estar logado. */
    private static final Set<String> LIVRES = Set.of(
            "/login.jsp",
            "/cadastro.jsp",
            "/login",
            "/cadastro"
    );

    @Override
    public void doFilter(ServletRequest req, ServletResponse res, FilterChain chain)
            throws IOException, ServletException {

        HttpServletRequest request = (HttpServletRequest) req;
        HttpServletResponse response = (HttpServletResponse) res;

        // Caminho sem o nome da aplicacao. Ex.: /atividade7e8/livro.jsp -> /livro.jsp
        String caminho = request.getRequestURI().substring(request.getContextPath().length());

        HttpSession sessao = request.getSession(false);
        boolean logado = sessao != null && sessao.getAttribute("contaLogada") != null;

        if (logado || LIVRES.contains(caminho)) {
            chain.doFilter(req, res);
            return;
        }

        // Nao esta logado: nao deixa o navegador guardar a pagina em cache
        // e manda para a tela de entrada.
        response.setHeader("Cache-Control", "no-store");
        response.sendRedirect(request.getContextPath() + "/login.jsp?exigeLogin=1");
    }
}
