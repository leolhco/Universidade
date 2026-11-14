<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%--
    Tela de entrada do sistema.
    Envia os dados para o Servlet /login (LoginServlet).
    Nao inclui o menu de proposito: quem esta aqui ainda nao tem acesso.
--%>
<%!
    /* Escapa o texto antes de jogar no HTML (evita quebrar a pagina e XSS). */
    private String esc(Object valor) {
        if (valor == null) return "";
        return valor.toString()
                    .replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;");
    }
%>

<jsp:include page="componentes/header.jsp">
    <jsp:param name="titulo" value="Entrar"/>
</jsp:include>

<style>
    .cartao {
        max-width: 380px;
        margin: 40px auto;
        border: 1px solid #d6dee8;
        border-radius: 6px;
        padding: 24px;
    }
    .cartao h2 { margin-top: 0; }
    .cartao label { display: block; margin-bottom: 12px; font-size: 14px; }
    .cartao input[type=email],
    .cartao input[type=password] {
        width: 100%;
        box-sizing: border-box;
        padding: 8px;
        margin-top: 4px;
        border: 1px solid #b9c5d4;
        border-radius: 4px;
        font-size: 14px;
    }
    .cartao button {
        width: 100%;
        background: #1f3a5f;
        color: #fff;
        border: 0;
        border-radius: 4px;
        padding: 10px;
        font-size: 15px;
        cursor: pointer;
    }
    .cartao button:hover { background: #2b4d7c; }
    .rodape-cartao { margin: 16px 0 0; font-size: 13px; text-align: center; }
</style>

<div class="cartao">
    <h2>Entrar</h2>

    <% if (request.getAttribute("mensagemErro") != null) { %>
        <p class="msg-erro"><%= esc(request.getAttribute("mensagemErro")) %></p>
    <% } else if ("1".equals(request.getParameter("exigeLogin"))) { %>
        <p class="msg-erro">Entre na sua conta para acessar o sistema.</p>
    <% } else if ("1".equals(request.getParameter("saiu"))) { %>
        <p class="msg-ok">Voce saiu do sistema.</p>
    <% } else if ("1".equals(request.getParameter("criada"))) { %>
        <p class="msg-ok">Conta criada. Entre com seu e-mail e senha.</p>
    <% } %>

    <form action="login" method="post">
        <label>
            E-mail
            <input type="email" name="email" value="<%= esc(request.getAttribute("email")) %>"
                   required autofocus/>
        </label>

        <label>
            Senha
            <input type="password" name="senha" required/>
        </label>

        <button type="submit">Entrar</button>
    </form>

    <p class="rodape-cartao">
        Ainda nao tem conta?
        <a href="${pageContext.request.contextPath}/cadastro.jsp">Criar conta</a>
    </p>
</div>

<jsp:include page="componentes/footer.jsp"/>
