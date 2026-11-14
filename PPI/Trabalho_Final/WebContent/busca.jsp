<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<jsp:include page="componentes/header.jsp">
    <jsp:param name="titulo" value="Pesquisa Avançada"/>
</jsp:include>
<jsp:include page="componentes/menu.jsp"/>

<style>
    .busca-container { 
        display: grid; 
        grid-template-columns: repeat(auto-fit, minmax(320px, 1fr)); 
        gap: 25px; 
        margin-top: 20px; 
    }
    .busca-card { 
        background: var(--cor-branco); 
        padding: 30px 25px; 
        border-radius: 8px; 
        box-shadow: 0 4px 12px rgba(0,0,0,0.05); 
        border: 1px solid #eaeaea; 
        transition: transform 0.2s, box-shadow 0.2s;
    }
    .busca-card:hover {
        transform: translateY(-3px);
        box-shadow: 0 8px 15px rgba(0,0,0,0.1);
        border-color: var(--cor-secundaria);
    }
    .busca-card h3 { 
        margin-top: 0; 
        color: var(--cor-primaria); 
        font-size: 18px; 
        border-bottom: 2px solid #f0f4f8; 
        padding-bottom: 12px; 
        margin-bottom: 20px; 
        display: flex; 
        align-items: center; 
        gap: 10px; 
    }
    .form-group { margin-bottom: 18px; }
    .form-group label { display: block; font-size: 14px; font-weight: 500; margin-bottom: 8px; color: #4a5568; }
    .form-group input, .form-group select { 
        width: 100%; 
        padding: 12px; 
        border: 1px solid #cbd5e1; 
        border-radius: 6px; 
        box-sizing: border-box; 
        transition: border-color 0.2s; 
        font-family: inherit;
        font-size: 14px;
    }
    .form-group input:focus, .form-group select:focus { outline: none; border-color: var(--cor-secundaria); box-shadow: 0 0 0 3px rgba(58, 99, 156, 0.1); }
    .btn-submit { 
        background: var(--cor-primaria); 
        color: #fff; 
        border: none; 
        padding: 12px 15px; 
        border-radius: 6px; 
        cursor: pointer; 
        width: 100%; 
        font-weight: 600; 
        font-size: 15px;
        transition: background 0.2s; 
        margin-top: 5px; 
    }
    .btn-submit:hover { background: var(--cor-secundaria); }
</style>

<h2 style="color: var(--cor-primaria); margin-bottom: 5px;">Pesquisa no Acervo</h2>
<p style="color: #64748b; margin-top: 0; margin-bottom: 30px;">Selecione a categoria e o critério desejado para realizar a busca.</p>

<div class="busca-container">
    
    <%-- BUSCA DE USUÁRIO --%>
    <div class="busca-card">
        <h3>👥 Buscar Usuário</h3>
        <form action="buscaUsuario" method="get">
            <input type="hidden" name="acao" value="pesquisaAvancada"/>
            <div class="form-group">
                <label>Critério de Busca:</label>
                <select name="criterio" required>
                    <option value="nome">Nome</option>
                    <option value="email">E-mail</option>
                    <option value="id">ID</option>
                </select>
            </div>
            <div class="form-group">
                <label>O que deseja encontrar?</label>
                <input type="text" name="termo" placeholder="Digite o termo da busca..." required/>
            </div>
            <button type="submit" class="btn-submit">Pesquisar Usuário</button>
        </form>
    </div>

    <%-- BUSCA DE REVISTA --%>
    <div class="busca-card">
        <h3>📰 Buscar Revista</h3>
        <form action="buscaRevista" method="get">
            <input type="hidden" name="acao" value="pesquisaAvancada"/>
            <div class="form-group">
                <label>Critério de Busca:</label>
                <select name="criterio" required>
                    <option value="titulo">Título (Nome)</option>
                    <option value="ano_publicacao">Ano de Publicação</option>
                    <option value="issn">ISSN</option>
                    <option value="editora">Editora</option>
                </select>
            </div>
            <div class="form-group">
                <label>O que deseja encontrar?</label>
                <input type="text" name="termo" placeholder="Digite o termo da busca..." required/>
            </div>
            <button type="submit" class="btn-submit">Pesquisar Revista</button>
        </form>
    </div>

    <%-- BUSCA DE LIVRO --%>
    <div class="busca-card">
        <h3>📚 Buscar Livro</h3>
        <form action="buscaLivro" method="get">
            <input type="hidden" name="acao" value="pesquisaAvancada"/>
            <div class="form-group">
                <label>Critério de Busca:</label>
                <select name="criterio" required>
                    <option value="nome">Nome do Livro</option>
                    <option value="editora">Editora</option>
                </select>
            </div>
            <div class="form-group">
                <label>O que deseja encontrar?</label>
                <input type="text" name="termo" placeholder="Digite o termo da busca..." required/>
            </div>
            <button type="submit" class="btn-submit">Pesquisar Livro</button>
        </form>
    </div>

    <%-- BUSCA DE AUTOR --%>
    <div class="busca-card">
        <h3>✍️ Buscar Autor</h3>
        <form action="buscaAutor" method="get">
            <input type="hidden" name="acao" value="pesquisaAvancada"/>
            <div class="form-group">
                <label>Critério de Busca:</label>
                <select name="criterio" required>
                    <option value="nomeReal">Nome Real</option>
                    <option value="nomeArtistico">Nome Artístico</option>
                    <option value="dataNascimento">Ano de Nascimento</option>
                </select>
            </div>
            <div class="form-group">
                <label>O que deseja encontrar?</label>
                <input type="text" name="termo" placeholder="Digite o termo da busca..." required/>
            </div>
            <button type="submit" class="btn-submit">Pesquisar Autor</button>
        </form>
    </div>

</div>

<jsp:include page="componentes/footer.jsp"/>