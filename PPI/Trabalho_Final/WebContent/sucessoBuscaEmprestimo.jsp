<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" errorPage="erro.jsp" %>
<%@ page import="entidade.Emprestimo" %>
<%-- Importando classes para traduzir os IDs --%>
<%@ page import="entidade.Usuario" %>
<%@ page import="dao.UsuarioDAO" %>
<%@ page import="entidade.Livro" %>
<%@ page import="dao.LivroDAO" %>
<%@ page import="entidade.Revista" %>
<%@ page import="dao.RevistaDAO" %>

<jsp:include page="componentes/header.jsp">
    <jsp:param name="titulo" value="Detalhes do Empréstimo"/>
</jsp:include>

<jsp:include page="componentes/menu.jsp"/>

<style>
    .cartao-sucesso {
        max-width: 500px;
        margin: 40px auto;
        background: var(--cor-branco);
        padding: 30px;
        border-radius: 8px;
        box-shadow: 0 4px 12px rgba(0,0,0,0.05);
        border: 1px solid #eaeaea;
    }
    .cartao-sucesso h2 {
        margin-top: 0;
        color: var(--cor-primaria);
        border-bottom: 2px solid #f0f4f8;
        padding-bottom: 10px;
        margin-bottom: 20px;
    }
    .info-grupo {
        margin-bottom: 15px;
        font-size: 15px;
        color: #4a5568;
    }
    .info-grupo strong {
        color: var(--cor-primaria);
    }
    .btn-voltar {
        display: inline-block;
        background: var(--cor-primaria);
        color: #fff;
        text-decoration: none;
        padding: 10px 20px;
        border-radius: 6px;
        font-weight: 600;
        margin-top: 20px;
        transition: background 0.2s;
    }
    .btn-voltar:hover {
        background: var(--cor-secundaria);
    }
</style>

<%
    Emprestimo emp = (Emprestimo) request.getAttribute("emprestimo");
    
    // Variáveis para armazenar os nomes traduzidos
    String nomeUsuario = "Desconhecido";
    String nomeLivro = "Nenhum";
    String nomeRevista = "Nenhuma";
    
    if (emp != null) {
        // 1. Busca o Nome do Usuário
        UsuarioDAO usuarioDao = new UsuarioDAO();
        Usuario usuario = usuarioDao.buscarPorId(emp.getUsuarioId());
        if (usuario != null) {
            nomeUsuario = usuario.getNome();
        }
        
        // 2. Busca o Nome do Livro (se houver)
        if (emp.getLivroId() != null && emp.getLivroId() != 0) {
            LivroDAO livroDao = new LivroDAO();
            Livro livro = livroDao.buscarPorId(emp.getLivroId());
            nomeLivro = emp.getLivroId() + " - " + ((livro != null) ? livro.getNome() : "Livro excluído");
        }
        
        // 3. Busca o Nome da Revista (se houver)
        if (emp.getRevistaId() != null && emp.getRevistaId() != 0) {
            RevistaDAO revistaDao = new RevistaDAO();
            Revista revista = revistaDao.buscarPorId(emp.getRevistaId());
            nomeRevista = emp.getRevistaId() + " - " + ((revista != null) ? revista.getTitulo() : "Revista excluída");
        }
    }
%>

<div class="cartao-sucesso">
    <h2>Empréstimo Localizado</h2>
    
    <% if (emp != null) { %>
        <div class="info-grupo"><strong>ID do Registro:</strong> #<%= emp.getId() %></div>
        <div class="info-grupo"><strong>Data do Empréstimo:</strong> <%= emp.getDataEmprestimo() %></div>
        <div class="info-grupo"><strong>Data de Devolução:</strong> <%= emp.getDataDevolucao() %></div>
        <div class="info-grupo"><strong>Usuário (Leitor):</strong> <%= emp.getUsuarioId() %> - <%= nomeUsuario %></div>
        <div class="info-grupo"><strong>Livro Emprestado:</strong> <%= nomeLivro %></div>
        <div class="info-grupo"><strong>Revista Emprestada:</strong> <%= nomeRevista %></div>
    <% } else { %>
        <p style="color: red;">Nenhum dado encontrado para este empréstimo.</p>
    <% } %>

    <br>
    <a href="emprestimo.jsp" class="btn-voltar">&larr; Voltar para o Painel</a>
</div>

<jsp:include page="componentes/footer.jsp"/>