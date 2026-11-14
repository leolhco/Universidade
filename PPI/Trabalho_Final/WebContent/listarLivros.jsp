<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" errorPage="erro.jsp" %>
<%@ page import="java.util.List" %>
<%@ page import="entidade.Livro" %>
<%@ page import="dao.LivroDAO" %>
<%-- Importando o Autor para traduzir o ID --%>
<%@ page import="entidade.Autor" %>
<%@ page import="dao.AutorDAO" %>

<jsp:include page="componentes/header.jsp">
    <jsp:param name="titulo" value="Lista de Livros"/>
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

<h2 style="color: var(--cor-primaria);">Livros Cadastrados</h2>

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
            <th>Editora</th>
            <th>Autor</th>
        </tr>
    </thead>
    <tbody>
        <% 
            @SuppressWarnings("unchecked")
            List<Livro> lista = (List<Livro>) request.getAttribute("listaLivros");
            
            if (lista == null) {
                LivroDAO dao = new LivroDAO();
                lista = dao.listarTodos();
            }
            
            if (lista != null && !lista.isEmpty()) {
                // Instancia o DAO de Autor fora do laço para não sobrecarregar o sistema
                AutorDAO autorDao = new AutorDAO(); 
                
                for (Livro livro : lista) { 
                    // Pega o nome do Autor baseado no ID
                    Autor autor = autorDao.buscarPorId(livro.getAutorId());
                    String nomeAutor = (autor != null) ? autor.getNomeReal() : "Autor não encontrado";
        %>
                    <tr>
                        <td><strong><%= livro.getId() %></strong></td>
                        <td><%= livro.getNome() %></td>
                        <td><%= livro.getEditora() %></td>
                        <td><%= livro.getAutorId() %> - <%= nomeAutor %></td>
                    </tr>
        <% 
                }
            } else { 
        %>
                <tr>
                    <td colspan="4" style="text-align: center; color: #888;">Nenhum livro encontrado na base de dados.</td>
                </tr>
        <% 
            }
        %>
    </tbody>
</table>

<jsp:include page="componentes/footer.jsp"/>