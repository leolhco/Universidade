<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" errorPage="erro.jsp" %>
<%@ page import="java.util.List" %>
<%@ page import="dao.RevistaDAO" %>
<%@ page import="entidade.Revista" %>

<jsp:include page="componentes/header.jsp">
    <jsp:param name="titulo" value="Gerenciar Revistas"/>
</jsp:include>
<jsp:include page="componentes/menu.jsp"/>

<%
    // Busca todas as revistas para o menu suspenso de Alterar/Remover
    RevistaDAO dao = new RevistaDAO();
    List<Revista> listaRevistas = dao.listarTodos();
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

<h2 style="color: var(--cor-primaria);">Painel de Revistas</h2>

<div class="crud-container">
    <div class="crud-card">
        <h3>Cadastrar</h3>
        <form action="revista" method="post">
            <input type="hidden" name="acao" value="cadastrar"/>
            <div class="form-group"><label>Título:</label><input type="text" name="titulo" required/></div>
            <div class="form-group"><label>Editora:</label><input type="text" name="editora" required/></div>
            <div class="form-group"><label>Número da edição:</label><input type="number" name="numeroEdicao" required/></div>
            <div class="form-group"><label>Ano de publicação:</label><input type="number" name="anoPublicacao" required/></div>
            <div class="form-group"><label>Mês de publicação:</label><input type="text" name="mesPublicacao" required/></div>
            <div class="form-group"><label>ISSN:</label><input type="text" name="issn"/></div>
            
            <%-- Novo menu suspenso para Periodicidade --%>
            <div class="form-group">
                <label>Periodicidade:</label>
                <select name="periodicidade" required>
                    <option value="Semanal">Semanal</option>
                    <option value="Mensal">Mensal</option>
                    <option value="Bimestral">Bimestral</option>
                    <option value="Trimestral">Trimestral</option>
                    <option value="Semestral">Semestral</option>
                    <option value="Anual">Anual</option>
                </select>
            </div>
            
            <button type="submit" class="btn-submit">Cadastrar Revista</button>
        </form>
    </div>

    <div class="crud-card">
        <h3>Alterar</h3>
        <form action="revista" method="post">
            <input type="hidden" name="acao" value="alterar"/>
            <div class="form-group">
                <label>Selecione a Revista:</label>
                <select name="id" required>
                    <option value="">Escolha a revista...</option>
                    <% if (listaRevistas != null) { for (Revista r : listaRevistas) { %>
                        <option value="<%= r.getId() %>"><%= r.getId() %> - <%= r.getTitulo() %></option>
                    <% } } %>
                </select>
            </div>
            <div class="form-group"><label>Novo Título:</label><input type="text" name="titulo"/></div>
            <div class="form-group"><label>Nova Editora:</label><input type="text" name="editora"/></div>
            <div class="form-group"><label>Nova Edição:</label><input type="number" name="numeroEdicao"/></div>
            <div class="form-group"><label>Novo Ano:</label><input type="number" name="anoPublicacao"/></div>
            <div class="form-group"><label>Novo Mês:</label><input type="text" name="mesPublicacao"/></div>
            <div class="form-group"><label>Novo ISSN:</label><input type="text" name="issn"/></div>
            
            <%-- Novo menu suspenso para Periodicidade --%>
            <div class="form-group">
                <label>Nova Periodicidade:</label>
                <select name="periodicidade" required>
                    <option value="Semanal">Semanal</option>
                    <option value="Mensal">Mensal</option>
                    <option value="Bimestral">Bimestral</option>
                    <option value="Trimestral">Trimestral</option>
                    <option value="Semestral">Semestral</option>
                    <option value="Anual">Anual</option>
                </select>
            </div>
            
            <button type="submit" class="btn-submit">Salvar Alterações</button>
        </form>
    </div>

    <div class="crud-card">
        <h3>Remover</h3>
        <form action="revista" method="post">
            <input type="hidden" name="acao" value="remover"/>
            <div class="form-group">
                <label>Selecione a Revista:</label>
                <select name="id" required>
                    <option value="">Escolha para remover...</option>
                    <% if (listaRevistas != null) { for (Revista r : listaRevistas) { %>
                        <option value="<%= r.getId() %>"><%= r.getId() %> - <%= r.getTitulo() %></option>
                    <% } } %>
                </select>
            </div>
            <button type="submit" class="btn-submit btn-danger">Remover Permanentemente</button>
        </form>
    </div>
</div>

<jsp:include page="componentes/footer.jsp"/>