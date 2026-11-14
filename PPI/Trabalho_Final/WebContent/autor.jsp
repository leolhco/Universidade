<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" errorPage="erro.jsp" %>
<%@ page import="java.util.List" %>
<%@ page import="dao.AutorDAO" %>
<%@ page import="entidade.Autor" %>

<jsp:include page="componentes/header.jsp">
    <jsp:param name="titulo" value="Gerenciar Autores"/>
</jsp:include>
<jsp:include page="componentes/menu.jsp"/>

<%
    // Busca todos os autores
    AutorDAO dao = new AutorDAO();
    List<Autor> listaAutores = dao.listarTodos();
%>

<style>
    .crud-container { display: grid; grid-template-columns: repeat(auto-fit, minmax(300px, 1fr)); gap: 20px; margin-top: 20px; }
    .crud-card { background: var(--cor-branco); padding: 25px; border-radius: 8px; box-shadow: 0 4px 12px rgba(0,0,0,0.05); border: 1px solid #eaeaea; }
    .crud-card h3 { margin-top: 0; color: var(--cor-primaria); font-size: 18px; border-bottom: 2px solid #f0f4f8; padding-bottom: 10px; margin-bottom: 15px; }
    .form-group { margin-bottom: 15px; }
    .form-group label { display: block; font-size: 14px; font-weight: 500; margin-bottom: 5px; color: #4a5568; }
    .form-group input, .form-group select { width: 100%; padding: 10px; border: 1px solid #cbd5e1; border-radius: 6px; box-sizing: border-box; transition: border-color 0.2s; font-family: inherit; font-size: 14px; background-color: #fff; }
    .form-group input:focus, .form-group select:focus { outline: none; border-color: var(--cor-secundaria); box-shadow: 0 0 0 3px rgba(58, 99, 156, 0.1); }
    .btn-submit { background: var(--cor-primaria); color: #fff; border: none; padding: 10px 15px; border-radius: 6px; cursor: pointer; width: 100%; font-weight: 600; transition: background 0.2s; }
    .btn-submit:hover { background: var(--cor-secundaria); }
    .btn-danger { background: #d93025; }
    .btn-danger:hover { background: #a50e0e; }
</style>

<h2 style="color: var(--cor-primaria);">Painel de Autores</h2>

<div class="crud-container">
    <div class="crud-card">
        <h3>Cadastrar</h3>
        <form action="autor" method="post">
            <input type="hidden" name="acao" value="cadastrar"/>
            <div class="form-group"><label>Nome real:</label><input type="text" name="nomeReal" required/></div>
            <div class="form-group"><label>Nome artístico:</label><input type="text" name="nomeArtistico"/></div>
            <div class="form-group"><label>Data de nascimento:</label><input type="date" name="dataNascimento" required/></div>
            <button type="submit" class="btn-submit">Cadastrar Autor</button>
        </form>
    </div>

    <div class="crud-card">
        <h3>Alterar</h3>
        <form action="autor" method="post">
            <input type="hidden" name="acao" value="alterar"/>
            <div class="form-group">
                <label>Selecione o Autor:</label>
                <select name="id" required>
                    <option value="">Escolha o autor...</option>
                    <% if (listaAutores != null) { for (Autor a : listaAutores) { %>
                        <option value="<%= a.getId() %>"><%= a.getId() %> - <%= a.getNomeReal() %></option>
                    <% } } %>
                </select>
            </div>
            <div class="form-group"><label>Novo Nome real:</label><input type="text" name="nomeReal"/></div>
            <div class="form-group"><label>Novo Nome artístico:</label><input type="text" name="nomeArtistico"/></div>
            <div class="form-group"><label>Nova Data de nascimento:</label><input type="date" name="dataNascimento"/></div>
            <button type="submit" class="btn-submit">Salvar Alterações</button>
        </form>
    </div>

    <div class="crud-card">
        <h3>Remover</h3>
        <form action="autor" method="post">
            <input type="hidden" name="acao" value="remover"/>
            <div class="form-group">
                <label>Selecione o Autor:</label>
                <select name="id" required>
                    <option value="">Escolha para remover...</option>
                    <% if (listaAutores != null) { for (Autor a : listaAutores) { %>
                        <option value="<%= a.getId() %>"><%= a.getId() %> - <%= a.getNomeReal() %></option>
                    <% } } %>
                </select>
            </div>
            <button type="submit" class="btn-submit btn-danger">Remover Permanentemente</button>
        </form>
    </div>
</div>

<jsp:include page="componentes/footer.jsp"/>