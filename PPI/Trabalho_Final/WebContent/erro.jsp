<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" isErrorPage="true" %>
<jsp:include page="componentes/header.jsp">
    <jsp:param name="titulo" value="Ocorreu um Erro"/>
</jsp:include>
<jsp:include page="componentes/menu.jsp"/>

<style>
    .card-erro {
        max-width: 500px;
        margin: 40px auto;
        padding: 25px;
        border: 1px solid #f5c6cb;
        background-color: #f8d7da;
        color: #721c24;
        border-radius: 8px;
        box-shadow: 0 4px 10px rgba(0,0,0,0.05);
        text-align: center;
    }
    .card-erro h2 {
        margin-top: 0;
        color: #721c24;
    }
    .card-erro p {
        font-size: 15px;
        margin-bottom: 20px;
    }
    .btn-voltar {
        background-color: #1f3a5f;
        color: #ffffff;
        border: none;
        padding: 10px 20px;
        border-radius: 6px;
        font-size: 14px;
        font-weight: bold;
        cursor: pointer;
        transition: background 0.2s;
    }
    .btn-voltar:hover {
        background-color: #2b4d7c;
    }
</style>

<div class="card-erro">
    <h2>Ops! Ocorreu um Erro</h2>

    <p>
        <% 
            String mensagem = (String) request.getAttribute("mensagemErro");
            if (mensagem != null && !mensagem.trim().isEmpty()) {
                out.print(mensagem);
            } else if (exception != null && exception.getMessage() != null) {
                out.print(exception.getMessage());
            } else {
                out.print("Não foi possível concluir a ação desejada.");
            }
        %>
    </p>

    <!-- Esse botão faz o navegador voltar exatamente para a tela que gerou o erro -->
    <button type="button" class="btn-voltar" onclick="window.history.back()">
        &larr; Voltar para a página anterior
    </button>
</div>

<jsp:include page="componentes/footer.jsp"/>