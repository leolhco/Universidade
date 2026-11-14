<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@ page import="java.util.List" %>
<%@ page import="entidade.Autor" %>
<%@ page import="dao.AutorDAO" %>

<jsp:include page="componentes/header.jsp">
    <jsp:param name="titulo" value="Lista de Autores"/>
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

<h2 style="color: var(--cor-primaria);">Autores Cadastrados</h2>

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
            <th>Nome Real</th>
            <th>Nome Artístico</th>
            <th>Data de Nascimento</th>
        </tr>
    </thead>
    <tbody>
        <% 
            @SuppressWarnings("unchecked")
            List<Autor> lista = (List<Autor>) request.getAttribute("listaAutores");
            
            if (lista == null) {
                AutorDAO dao = new AutorDAO();
                lista = dao.listarTodos();
            }
            
            if (lista != null && !lista.isEmpty()) {
                for (Autor autor : lista) { 
        %>
                    <tr>
                        <td><strong><%= autor.getId() %></strong></td>
                        <td><%= autor.getNomeReal() %></td>
                        <td><%= autor.getNomeArtistico() %></td>
                        <td><%= autor.getDataNascimento() %></td>
                    </tr>
        <% 
                }
            } else { 
        %>
                <tr>
                    <td colspan="4" style="text-align: center; color: #888;">Nenhum autor encontrado na base de dados.</td>
                </tr>
        <% 
            }
        %>
    </tbody>
</table>

<jsp:include page="componentes/footer.jsp"/>