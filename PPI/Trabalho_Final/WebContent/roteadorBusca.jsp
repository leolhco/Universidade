<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%--
    TAREFA 2 - Roteador.
    Le o resultado que o Servlet colocou na requisicao e usa a action
    <jsp:forward> para encaminhar para paginas JSP DISTINTAS:
      - sucessoBusca.jsp  (usuario encontrado)
      - erroBusca.jsp     (nao encontrado / erro)
    Este JSP nao produz saida visivel: apenas decide o destino.
--%>
<%
    Boolean encontrado = (Boolean) request.getAttribute("encontrado");
    if (Boolean.TRUE.equals(encontrado)) {
%>
        <jsp:forward page="sucessoBusca.jsp"/>
<%
    } else {
%>
        <jsp:forward page="erroBusca.jsp"/>
<%
    }
%>
