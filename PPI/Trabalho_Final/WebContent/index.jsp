<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@ page import="entidade.Conta" %>
<%-- Pagina principal (home) que MONTA os componentes reutilizaveis.
     So e alcancada por quem esta logado (ver filtros.AutenticacaoFilter). --%>
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

<jsp:include page="componentes/header.jsp">
    <jsp:param name="titulo" value="Dashboard - Início"/>
</jsp:include>

<jsp:include page="componentes/menu.jsp"/>

<style>
    /* Estilos do Banner de Boas-Vindas */
    .welcome-banner {
        background: linear-gradient(135deg, #1f3a5f 0%, #3a639c 100%);
        color: #ffffff;
        padding: 30px;
        border-radius: 8px;
        margin-bottom: 30px;
        box-shadow: 0 4px 10px rgba(0,0,0,0.1);
        display: flex;
        align-items: center;
        justify-content: space-between;
    }
    .welcome-banner h2 {
        margin-top: 0;
        font-size: 28px;
    }
    .welcome-banner p {
        font-size: 16px;
        margin-bottom: 0;
        opacity: 0.9;
    }

    /* Estilos do Grid de Cards (Painel de Controle) */
    .dashboard-grid {
        display: flex;
        flex-wrap: wrap;
        gap: 20px;
    }
    
    /* Remove sublinhado dos links nos cards */
    .card-link {
        text-decoration: none;
        color: inherit;
        display: block;
        width: calc(33.333% - 14px); /* 3 cards por linha no desktop */
        min-width: 200px;
    }

    /* Estilo individual do Card */
    .card {
        background-color: #ffffff;
        border: 1px solid #d6dee8;
        border-radius: 8px;
        padding: 24px;
        text-align: center;
        box-shadow: 0 2px 4px rgba(0,0,0,0.05);
        transition: transform 0.2s ease, box-shadow 0.2s ease;
        height: 100%;
        box-sizing: border-box;
    }
    
    /* Efeito ao passar o mouse */
    .card:hover {
        transform: translateY(-5px);
        box-shadow: 0 8px 15px rgba(0,0,0,0.1);
        border-color: #1f3a5f;
    }

    .card-icon {
        font-size: 45px;
        margin-bottom: 15px;
    }

    .card-title {
        font-size: 18px;
        font-weight: bold;
        color: #1f3a5f;
        margin-bottom: 8px;
    }

    .card-desc {
        font-size: 13px;
        color: #5b6c80;
    }

    /* Responsividade para telas menores */
    @media (max-width: 768px) {
        .card-link { width: calc(50% - 10px); }
    }
    @media (max-width: 480px) {
        .card-link { width: 100%; }
        .welcome-banner { flex-direction: column; text-align: center; }
    }
</style>

<%-- Banner de Boas-Vindas --%>
<div class="welcome-banner">
    <div>
        <h2>Bem-vindo ao Sistema Biblioteca!</h2>
        <% if (contaLogada != null) { %>
            <p>Olá, <strong><%= esc(contaLogada.getNome()) %></strong>. Você está conectado como <em><%= esc(contaLogada.getEmail()) %></em>.</p>
        <% } %>
    </div>
    <div style="font-size: 60px;">📚</div>
</div>

<%-- Painel de Controle (Cards) --%>
<h3 style="color: #1f3a5f; margin-bottom: 15px;">Acesso Rápido</h3>

<div class="dashboard-grid">
    
    <a href="usuario.jsp" class="card-link">
        <div class="card">
            <div class="card-icon">👥</div>
            <div class="card-title">Usuários</div>
            <div class="card-desc">Gerencie os leitores cadastrados no sistema.</div>
        </div>
    </a>

    <a href="autor.jsp" class="card-link">
        <div class="card">
            <div class="card-icon">✍️</div>
            <div class="card-title">Autores</div>
            <div class="card-desc">Adicione e edite os autores do acervo.</div>
        </div>
    </a>

    <a href="livro.jsp" class="card-link">
        <div class="card">
            <div class="card-icon">📖</div>
            <div class="card-title">Livros</div>
            <div class="card-desc">Controle o catálogo de livros disponíveis.</div>
        </div>
    </a>

    <a href="revista.jsp" class="card-link">
        <div class="card">
            <div class="card-icon">📰</div>
            <div class="card-title">Revistas</div>
            <div class="card-desc">Cadastre e acompanhe periódicos e revistas.</div>
        </div>
    </a>

    <a href="emprestimo.jsp" class="card-link">
        <div class="card">
            <div class="card-icon">🤝</div>
            <div class="card-title">Empréstimos</div>
            <div class="card-desc">Registre saídas e devoluções de materiais.</div>
        </div>
    </a>

</div>

<jsp:include page="componentes/footer.jsp"/>