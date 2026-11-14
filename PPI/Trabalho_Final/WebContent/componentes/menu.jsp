<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@ page import="entidade.Conta" %>
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
<%
    Conta contaLogada = (Conta) session.getAttribute("contaLogada");
%>

<style>
    /* Estilos Modernos para o Menu de Navegação */
    .menu-nav {
        background: #ffffff;
        padding: 0 30px;
        box-shadow: 0 2px 8px rgba(0,0,0,0.05);
        display: flex;
        align-items: center;
        border-bottom: 1px solid #eaeaea;
        margin: -30px -30px 30px -30px; /* Expande o menu pelas laterais do <main> */
    }
    
    .menu-links {
        display: flex;
        gap: 10px;
        flex-grow: 1; /* Empurra as informações do usuário para a direita */
    }

    .menu-nav a, .dropdown-btn {
        text-decoration: none;
        color: #4a5568;
        padding: 16px 20px;
        font-size: 15px;
        font-weight: 500;
        display: inline-block;
        transition: all 0.2s ease;
        cursor: pointer;
        border-bottom: 3px solid transparent; /* Preparação para o efeito hover */
    }

    .menu-nav a:hover, .dropdown:hover .dropdown-btn {
        color: #1f3a5f;
        border-bottom: 3px solid #1f3a5f;
        background-color: #f8f9fa;
    }

    /* Estrutura do Dropdown */
    .dropdown { position: relative; }
    
    .dropdown-content {
        display: none;
        position: absolute;
        background-color: #ffffff;
        min-width: 190px;
        box-shadow: 0px 10px 25px rgba(0,0,0,0.1);
        z-index: 100;
        top: 100%;
        left: 0;
        border-radius: 0 0 8px 8px;
        border: 1px solid #eaeaea;
        border-top: none;
        overflow: hidden;
    }

    .dropdown-content a {
        padding: 12px 20px;
        border-bottom: none;
        display: block;
        font-weight: 400;
        width: 100%;
        box-sizing: border-box;
    }

    .dropdown-content a:hover {
        background-color: #f0f4f8;
        color: #1f3a5f;
        padding-left: 25px; /* Leve recuo que dá sensação de interatividade */
    }

    /* Exibição animada do dropdown */
    .dropdown:hover .dropdown-content {
        display: block;
        animation: slideDown 0.2s ease-in-out;
    }

    /* Área do Usuário à Direita */
    .user-info {
        font-size: 14px;
        color: #4a5568;
        display: flex;
        align-items: center;
        gap: 15px;
    }

    .btn-sair {
        background: #ffebe6;
        color: #d93025 !important;
        border-radius: 20px;
        padding: 6px 16px !important;
        border: none !important;
        font-weight: 600;
    }

    .btn-sair:hover {
        background: #fce8e6 !important;
        color: #a50e0e !important;
    }

    @keyframes slideDown {
        from { opacity: 0; transform: translateY(-5px); }
        to { opacity: 1; transform: translateY(0); }
    }
</style>

<nav class="menu-nav">
    <div class="menu-links">
        <a href="${pageContext.request.contextPath}/index.jsp">Início</a>

        <div class="dropdown">
            <span class="dropdown-btn">Cadastros &#9662;</span>
            <div class="dropdown-content">
                <a href="${pageContext.request.contextPath}/usuario.jsp">Usuários</a>
                <a href="${pageContext.request.contextPath}/autor.jsp">Autores</a>
                <a href="${pageContext.request.contextPath}/livro.jsp">Livros</a>
                <a href="${pageContext.request.contextPath}/revista.jsp">Revistas</a>
                <a href="${pageContext.request.contextPath}/emprestimo.jsp">Empréstimos</a>
            </div>
        </div>

        <a href="${pageContext.request.contextPath}/busca.jsp">Busca</a>

        <div class="dropdown">
            <span class="dropdown-btn">Listar Todos &#9662;</span>
            <div class="dropdown-content">
                <a href="${pageContext.request.contextPath}/listarUsuarios.jsp">Usuários</a>
                <a href="${pageContext.request.contextPath}/listarAutores.jsp">Autores</a>
                <a href="${pageContext.request.contextPath}/listarLivros.jsp">Livros</a>
                <a href="${pageContext.request.contextPath}/listarRevistas.jsp">Revistas</a>
                <a href="${pageContext.request.contextPath}/listarEmprestimos.jsp">Empréstimos</a>
            </div>
        </div>
    </div>

    <% if (contaLogada != null) { %>
        <div class="user-info">
            <span>👤 <%= esc(contaLogada.getNome()) %></span>
            <a href="${pageContext.request.contextPath}/logout" class="btn-sair">Sair</a>
        </div>
    <% } %>
</nav>