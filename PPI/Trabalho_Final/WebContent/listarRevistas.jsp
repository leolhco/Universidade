<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@ page import="java.util.List" %>
<%@ page import="entidade.Revista" %>
<%@ page import="dao.RevistaDAO" %>

<jsp:include page="componentes/header.jsp">
    <jsp:param name="titulo" value="Lista de Revistas"/>
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

<h2 style="color: var(--cor-primaria);">Revistas Cadastradas</h2>

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
            <th>Título</th>
            <th>Editora</th>
            <th>Edição</th>
            <th>Data Publ.</th>
            <th>ISSN</th>
            <th>Periodicidade</th>
        </tr>
    </thead>
    <tbody>
        <% 
            @SuppressWarnings("unchecked")
            List<Revista> lista = (List<Revista>) request.getAttribute("listaRevistas");
            
            if (lista == null) {
                RevistaDAO dao = new RevistaDAO();
                lista = dao.listarTodos();
            }
            
            if (lista != null && !lista.isEmpty()) {
                for (Revista revista : lista) { 
        %>
                    <tr>
                        <td><strong><%= revista.getId() %></strong></td>
                        <td><%= revista.getTitulo() %></td>
                        <td><%= revista.getEditora() %></td>
                        <td><%= revista.getNumeroEdicao() %></td>
                        <td><%= revista.getMesPublicacao() %>/<%= revista.getAnoPublicacao() %></td>
                        <td><%= revista.getIssn() %></td>
                        <td><%= revista.getPeriodicidade() %></td>
                    </tr>
        <% 
                }
            } else { 
        %>
                <tr>
                    <td colspan="7" style="text-align: center; color: #888;">Nenhuma revista encontrada na base de dados.</td>
                </tr>
        <% 
            }
        %>
    </tbody>
</table>

<jsp:include page="componentes/footer.jsp"/>