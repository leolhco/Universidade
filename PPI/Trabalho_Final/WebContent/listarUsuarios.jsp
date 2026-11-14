<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@ page import="java.util.List" %>
<%@ page import="entidade.Usuario" %>
<%@ page import="dao.UsuarioDAO" %>

<jsp:include page="componentes/header.jsp">
    <jsp:param name="titulo" value="Lista de Usuários"/>
</jsp:include>
<jsp:include page="componentes/menu.jsp"/>

<style>
    .table-moderna { width: 100%; border-collapse: collapse; background: var(--cor-branco); box-shadow: 0 4px 12px rgba(0,0,0,0.05); border-radius: 8px; overflow: hidden; margin-top: 20px; }
    .table-moderna thead { background-color: var(--cor-primaria); color: #ffffff; text-align: left; }
    .table-moderna th, .table-moderna td { padding: 15px; border-bottom: 1px solid #eaeaea; }
    .table-moderna th { font-weight: 600; font-size: 15px; }
    .table-moderna tbody tr:hover { background-color: #f8f9fa; }
    .table-moderna tbody tr:last-child td { border-bottom: none; }
</style>

<h2 style="color: var(--cor-primaria);">Usuários Cadastrados</h2>

<% 
    String erro = (String) request.getAttribute("mensagemErro");
    if (erro != null) { 
%>
    <div class="msg-erro" style="margin-bottom: 20px;"><%= erro %></div>
<% } %>

<table class="table-moderna">
    <thead>
        <tr>
            <th>ID</th>
            <th>Nome</th>
            <th>Data de Nascimento</th>
            <th>E-mail</th>
            <th>Telefone</th>
        </tr>
    </thead>
    <tbody>
        <% 
            // 1. Tenta pegar a lista que veio da busca
            @SuppressWarnings("unchecked")
            List<Usuario> lista = (List<Usuario>) request.getAttribute("listaUsuarios");
            
            // 2. Se a lista estiver nula (veio do menu Listar Todos), busca no banco
            if (lista == null) {
                UsuarioDAO dao = new UsuarioDAO();
                lista = dao.listarTodos();
            }
            
            if (lista != null && !lista.isEmpty()) {
                for (Usuario usuario : lista) { 
        %>
                    <tr>
                        <td><strong><%= usuario.getId() %></strong></td>
                        <td><%= usuario.getNome() %></td>
                        <td><%= usuario.getDataNascimento() %></td>
                        <td><%= usuario.getEmail() %></td>
                        <td><%= usuario.getTelefone() %></td>
                    </tr>
        <% 
                }
            } else { 
        %>
                <tr>
                    <td colspan="5" style="text-align: center; color: #888;">Nenhum usuário encontrado na base de dados.</td>
                </tr>
        <% 
            }
        %>
    </tbody>
</table>


<jsp:include page="componentes/footer.jsp"/>