<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" errorPage="erro.jsp" %>
<%@ page import="java.util.List" %>
<%@ page import="entidade.Emprestimo" %>
<%@ page import="dao.EmprestimoDAO" %>
<%-- Importando classes para traduzir os IDs --%>
<%@ page import="entidade.Usuario" %>
<%@ page import="dao.UsuarioDAO" %>
<%@ page import="entidade.Livro" %>
<%@ page import="dao.LivroDAO" %>
<%@ page import="entidade.Revista" %>
<%@ page import="dao.RevistaDAO" %>

<jsp:include page="componentes/header.jsp">
    <jsp:param name="titulo" value="Lista de Empréstimos"/>
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

<h2 style="color: var(--cor-primaria);">Empréstimos Cadastrados</h2>

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
            <th>Retirada</th>
            <th>Devolução</th>
            <th>Leitor (Usuário)</th>
            <th>Livro Emprestado</th>
            <th>Revista Emprestada</th>
        </tr>
    </thead>
    <tbody>
        <% 
            @SuppressWarnings("unchecked")
            List<Emprestimo> lista = (List<Emprestimo>) request.getAttribute("listaEmprestimos");
            
            if (lista == null) {
                EmprestimoDAO dao = new EmprestimoDAO();
                lista = dao.listarTodos();
            }
            
            if (lista != null && !lista.isEmpty()) {
                // Instancia os DAOs fora do laço principal
                UsuarioDAO usuarioDao = new UsuarioDAO();
                LivroDAO livroDao = new LivroDAO();
                RevistaDAO revistaDao = new RevistaDAO();
                
                for (Emprestimo emprestimo : lista) { 
                    // 1. Busca o Nome do Usuário
                    Usuario usuario = usuarioDao.buscarPorId(emprestimo.getUsuarioId());
                    String nomeUsuario = (usuario != null) ? usuario.getNome() : "Desconhecido";
                    
                    // 2. Busca o Nome do Livro (se houver)
                    String nomeLivro = "-";
                    if (emprestimo.getLivroId() != null && emprestimo.getLivroId() != 0) {
                        Livro livro = livroDao.buscarPorId(emprestimo.getLivroId());
                        nomeLivro = (livro != null) ? livro.getNome() : "Livro excluído";
                        nomeLivro = emprestimo.getLivroId() + " - " + nomeLivro;
                    }
                    
                    // 3. Busca o Nome da Revista (se houver)
                    String nomeRevista = "-";
                    if (emprestimo.getRevistaId() != null && emprestimo.getRevistaId() != 0) {
                        Revista revista = revistaDao.buscarPorId(emprestimo.getRevistaId());
                        nomeRevista = (revista != null) ? revista.getTitulo() : "Revista excluída";
                        nomeRevista = emprestimo.getRevistaId() + " - " + nomeRevista;
                    }
        %>
                    <tr>
                        <td><strong><%= emprestimo.getId() %></strong></td>
                        <td><%= emprestimo.getDataEmprestimo() %></td>
                        <td><%= emprestimo.getDataDevolucao() %></td>
                        <td><%= emprestimo.getUsuarioId() %> - <%= nomeUsuario %></td>
                        <td><%= nomeLivro %></td>
                        <td><%= nomeRevista %></td>
                    </tr>
        <% 
                }
            } else { 
        %>
                <tr>
                    <td colspan="6" style="text-align: center; color: #888;">Nenhum empréstimo encontrado na base de dados.</td>
                </tr>
        <% 
            }
        %>
    </tbody>
</table>

<jsp:include page="componentes/footer.jsp"/>