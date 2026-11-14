<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%--
    Componente reutilizavel: FOOTER
    - Fecha a estrutura HTML aberta pelo header.jsp (</main>, </body>, </html>).
--%>
</main>
    
    <%-- Rodape estilizado, fixo na base e com sombra superior --%>
    <footer style="position: fixed; bottom: 0; left: 0; width: 100%; box-sizing: border-box; background:#1f3a5f; color:#ffffff; padding:15px 24px; font-size:13px; text-align: center; z-index: 10; box-shadow: 0 -2px 10px rgba(0,0,0,0.15);">
        <p style="margin:0; font-weight: 300; letter-spacing: 0.5px;">
            <strong>Sistema Gerenciador de Biblioteca</strong> &mdash; Programação Para Internet &copy; <%= new java.text.SimpleDateFormat("yyyy").format(new java.util.Date()) %>
        </p>
    </footer>
</body>
</html>