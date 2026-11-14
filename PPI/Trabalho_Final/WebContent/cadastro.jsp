<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%--
    Criacao de conta de acesso.
    Envia os dados para o Servlet /cadastro (CadastroServlet).
--%>
<%!
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
    <jsp:param name="titulo" value="Criar conta"/>
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
    .cartao input {
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
    .dica { font-size: 12px; color: #5b6c80; margin: -8px 0 12px; }
</style>

<div class="cartao">
    <h2>Criar conta</h2>

    <% if (request.getAttribute("mensagemErro") != null) { %>
        <p class="msg-erro"><%= esc(request.getAttribute("mensagemErro")) %></p>
    <% } %>

    <form action="cadastro" method="post">
        <label>
            Nome
            <input type="text" name="nome" maxlength="100"
                   value="<%= esc(request.getAttribute("nome")) %>" required autofocus/>
        </label>

        <label>
            E-mail
            <input type="email" name="email" maxlength="100"
                   value="<%= esc(request.getAttribute("email")) %>" required/>
        </label>

        <label>
            Senha
            <input type="password" name="senha" minlength="6" required/>
        </label>
        <p class="dica">Minimo de 6 caracteres.</p>

        <label>
            Repita a senha
            <input type="password" name="confirmacao" minlength="6" required/>
        </label>

        <button type="submit">Criar conta</button>
    </form>

    <p class="rodape-cartao">
        Ja tem conta?
        <a href="${pageContext.request.contextPath}/login.jsp">Entrar</a>
    </p>
</div>

<jsp:include page="componentes/footer.jsp"/>
