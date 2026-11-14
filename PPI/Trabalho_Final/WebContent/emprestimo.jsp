<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" errorPage="erro.jsp" %>
<%@ page import="java.util.List" %>
<%@ page import="dao.UsuarioDAO" %>
<%@ page import="entidade.Usuario" %>
<%@ page import="dao.LivroDAO" %>
<%@ page import="entidade.Livro" %>
<%@ page import="dao.RevistaDAO" %>
<%@ page import="entidade.Revista" %>
<%@ page import="dao.EmprestimoDAO" %>
<%@ page import="entidade.Emprestimo" %>

<jsp:include page="componentes/header.jsp">
    <jsp:param name="titulo" value="Gerenciar Empréstimos"/>
</jsp:include>
<jsp:include page="componentes/menu.jsp"/>

<%
    // Puxando todos os dados necessários para os menus
    UsuarioDAO usuarioDao = new UsuarioDAO();
    List<Usuario> listaUsuarios = usuarioDao.listarTodos();
    
    LivroDAO livroDao = new LivroDAO();
    List<Livro> listaLivros = livroDao.listarTodos();
    
    RevistaDAO revistaDao = new RevistaDAO();
    List<Revista> listaRevistas = revistaDao.listarTodos();

    EmprestimoDAO emprestimoDao = new EmprestimoDAO();
    List<Emprestimo> listaEmprestimos = emprestimoDao.listarTodos();
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

<h2 style="color: var(--cor-primaria);">Painel de Empréstimos</h2>

<div class="crud-container">
    <div class="crud-card">
        <h3>Cadastrar</h3>
        <form action="emprestimo" method="post">
            <input type="hidden" name="acao" value="cadastrar"/>
            <div class="form-group"><label>Data do empréstimo:</label><input type="date" name="dataEmprestimo" required/></div>
            <div class="form-group"><label>Data de devolução:</label><input type="date" name="dataDevolucao" required/></div>
            
            <div class="form-group">
                <label>Usuário:</label>
                <select name="usuarioId" required>
                    <option value="">Selecione o leitor...</option>
                    <% if (listaUsuarios != null) { for (Usuario u : listaUsuarios) { %>
                        <option value="<%= u.getId() %>"><%= u.getId() %> - <%= u.getNome() %></option>
                    <% } } %>
                </select>
            </div>
            <div class="form-group">
                <label>Livro (Opcional):</label>
                <select name="livroId">
                    <option value="">Nenhum livro...</option>
                    <% if (listaLivros != null) { for (Livro l : listaLivros) { %>
                        <option value="<%= l.getId() %>"><%= l.getId() %> - <%= l.getNome() %></option>
                    <% } } %>
                </select>
            </div>
            <div class="form-group">
                <label>Revista (Opcional):</label>
                <select name="revistaId">
                    <option value="">Nenhuma revista...</option>
                    <% if (listaRevistas != null) { for (Revista r : listaRevistas) { %>
                        <option value="<%= r.getId() %>"><%= r.getId() %> - <%= r.getTitulo() %></option>
                    <% } } %>
                </select>
            </div>
            <button type="submit" class="btn-submit">Registrar Empréstimo</button>
        </form>
    </div>

    <div class="crud-card">
        <h3>Alterar</h3>
        <form action="emprestimo" method="post">
            <input type="hidden" name="acao" value="alterar"/>
            <div class="form-group">
                <label>Selecione o Empréstimo:</label>
                <select name="id" required>
                    <option value="">Escolha o registro...</option>
                    <% if (listaEmprestimos != null) { for (Emprestimo e : listaEmprestimos) { %>
                        <option value="<%= e.getId() %>"><%= e.getId() %> - Retirado em <%= e.getDataEmprestimo() %></option>
                    <% } } %>
                </select>
            </div>
            <div class="form-group"><label>Nova Data de empréstimo:</label><input type="date" name="dataEmprestimo"/></div>
            <div class="form-group"><label>Nova Data de devolução:</label><input type="date" name="dataDevolucao"/></div>
            
            <div class="form-group">
                <label>Novo Usuário:</label>
                <select name="usuarioId">
                    <option value="">Manter o mesmo (ou selecione)...</option>
                    <% if (listaUsuarios != null) { for (Usuario u : listaUsuarios) { %>
                        <option value="<%= u.getId() %>"><%= u.getId() %> - <%= u.getNome() %></option>
                    <% } } %>
                </select>
            </div>
            <div class="form-group">
                <label>Novo Livro:</label>
                <select name="livroId">
                    <option value="">Manter o mesmo (ou selecione)...</option>
                    <% if (listaLivros != null) { for (Livro l : listaLivros) { %>
                        <option value="<%= l.getId() %>"><%= l.getId() %> - <%= l.getNome() %></option>
                    <% } } %>
                </select>
            </div>
            <div class="form-group">
                <label>Nova Revista:</label>
                <select name="revistaId">
                    <option value="">Manter o mesmo (ou selecione)...</option>
                    <% if (listaRevistas != null) { for (Revista r : listaRevistas) { %>
                        <option value="<%= r.getId() %>"><%= r.getId() %> - <%= r.getTitulo() %></option>
                    <% } } %>
                </select>
            </div>
            <button type="submit" class="btn-submit">Salvar Alterações</button>
        </form>
    </div>

    <div class="crud-card">
        <h3>Consultar (Busca Rápida)</h3>
        <form action="emprestimo" method="get">
            <input type="hidden" name="acao" value="consultar"/>
            <div class="form-group">
                <label>Selecione o Empréstimo:</label>
                <select name="id" required>
                    <option value="">Escolha o registro...</option>
                    <% if (listaEmprestimos != null) { for (Emprestimo e : listaEmprestimos) { %>
                        <option value="<%= e.getId() %>"><%= e.getId() %> - Retirado em <%= e.getDataEmprestimo() %></option>
                    <% } } %>
                </select>
            </div>
            <button type="submit" class="btn-submit">Buscar</button>
        </form>
    </div>

    <div class="crud-card">
        <h3>Remover</h3>
        <form action="emprestimo" method="post">
            <input type="hidden" name="acao" value="remover"/>
            <div class="form-group">
                <label>Selecione o Empréstimo:</label>
                <select name="id" required>
                    <option value="">Escolha para remover...</option>
                    <% if (listaEmprestimos != null) { for (Emprestimo e : listaEmprestimos) { %>
                        <option value="<%= e.getId() %>"><%= e.getId() %> - Retirado em <%= e.getDataEmprestimo() %></option>
                    <% } } %>
                </select>
            </div>
            <button type="submit" class="btn-submit btn-danger">Remover Permanentemente</button>
        </form>
    </div>
</div>

<jsp:include page="componentes/footer.jsp"/>