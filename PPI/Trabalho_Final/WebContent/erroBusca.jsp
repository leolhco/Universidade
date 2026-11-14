<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%-- Pagina de ERRO. Le a mensagem que o Servlet colocou na requisicao. --%>

<jsp:include page="componentes/header.jsp">
    <jsp:param name="titulo" value="Busca sem resultado"/>
</jsp:include>

<jsp:include page="componentes/menu.jsp"/>

<h2 class="msg-erro">Nao foi possivel concluir a busca</h2>

<p class="msg-erro">${empty mensagemErro ? "Ocorreu um erro na busca." : mensagemErro}</p>

<p><a href="busca.jsp">Tentar novamente</a></p>

<jsp:include page="componentes/footer.jsp"/>
