<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%-- Pagina de SUCESSO. Le o usuario que o Servlet colocou na requisicao. --%>

<jsp:include page="componentes/header.jsp">
    <jsp:param name="titulo" value="Usuario encontrado"/>
</jsp:include>

<jsp:include page="componentes/menu.jsp"/>

<h2 class="msg-ok">Usuario encontrado com sucesso!</h2>

<p><strong>ID:</strong> ${usuario.id}</p>
<p><strong>Nome:</strong> ${usuario.nome}</p>
<p><strong>Data de nascimento:</strong> ${usuario.dataNascimento}</p>
<p><strong>E-mail:</strong> ${usuario.email}</p>
<p><strong>Telefone:</strong> ${usuario.telefone}</p>

<p><a href="busca.jsp">Fazer nova busca</a></p>

<jsp:include page="componentes/footer.jsp"/>
