-- Criação Tabelas Linha: 7
-- Inserção Tuplas Linha: 138
-- Consultas Linha: 222
-- Trigger Linha: 306
-- Utilização do Trigger: 331
-- Procedimento Armazenado Linha: 336

--Criação Tabelas
-- USUARIO
CREATE TABLE USUARIO (
    cpf CHAR(11) UNIQUE NOT NULL,
    nome VARCHAR(100) NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    telefone VARCHAR(20),
    endereco TEXT,
    data_nascimento DATE,
    nome_usuario VARCHAR(50) PRIMARY KEY,
    senha TEXT NOT NULL
);

-- CONTA_PESSOAL
CREATE TABLE CONTA_PESSOAL (
    nome_usuario VARCHAR(50) PRIMARY KEY REFERENCES USUARIO(nome_usuario),
    nro_amigos INT DEFAULT 0
);

-- CONTA_EMPRESARIAL
CREATE TABLE CONTA_EMPRESARIAL (
    nome_usuario VARCHAR(50) PRIMARY KEY REFERENCES USUARIO(nome_usuario),
    nome_empresa VARCHAR(100) NOT NULL,
    cnpj CHAR(14) UNIQUE NOT NULL
);

-- PACOTE
CREATE TABLE PACOTE (
    codigo SERIAL PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
    preco NUMERIC(10,2) NOT NULL,
    funcionalidades TEXT
);

-- SELECIONA
CREATE TABLE SELECIONA (
    nome_usuario VARCHAR(50),
    codigo_pacote INT,
    data_selecao DATE DEFAULT CURRENT_DATE,
    PRIMARY KEY (nome_usuario, codigo_pacote),
    FOREIGN KEY (nome_usuario) REFERENCES CONTA_EMPRESARIAL(nome_usuario),
    FOREIGN KEY (codigo_pacote) REFERENCES PACOTE(codigo)
);

-- REQ_AMIZADE
CREATE TABLE REQ_AMIZADE (
    requerente VARCHAR(50),
    requerida VARCHAR(50),
    aceito BOOLEAN DEFAULT FALSE,
    PRIMARY KEY (requerente, requerida),
    FOREIGN KEY (requerente) REFERENCES USUARIO(nome_usuario),
    FOREIGN KEY (requerida) REFERENCES USUARIO(nome_usuario)
);

-- GRUPO_AMIGOS
CREATE TABLE GRUPO_AMIGOS (
    codigo SERIAL PRIMARY KEY,
    nome VARCHAR(100),
    descricao TEXT
);

-- PARTICIPA
CREATE TABLE PARTICIPA (
    nome_usuario VARCHAR(50),
    codigo_grupo INT,
    PRIMARY KEY (nome_usuario, codigo_grupo),
    FOREIGN KEY (nome_usuario) REFERENCES CONTA_PESSOAL(nome_usuario),
    FOREIGN KEY (codigo_grupo) REFERENCES GRUPO_AMIGOS(codigo)
);

-- POSSUI
CREATE TABLE POSSUI (
    nome_usuario VARCHAR(50),
    codigo_grupo INT,
    PRIMARY KEY (nome_usuario, codigo_grupo),
    FOREIGN KEY (nome_usuario) REFERENCES CONTA_PESSOAL(nome_usuario),
    FOREIGN KEY (codigo_grupo) REFERENCES GRUPO_AMIGOS(codigo)
);

-- PAGINA
CREATE TABLE PAGINA (
    nome_usuario VARCHAR(50),
    nome_pagina VARCHAR(100),
    nro_acessos INT DEFAULT 0,
    PRIMARY KEY (nome_usuario, nome_pagina),
    FOREIGN KEY (nome_usuario) REFERENCES USUARIO(nome_usuario)
);

-- PODEVER
CREATE TABLE PODEVER (
    codigo_grupo INT,
    nome_usuario VARCHAR(50),
    nome_pagina VARCHAR(100),
    PRIMARY KEY (codigo_grupo, nome_usuario, nome_pagina),
    FOREIGN KEY (codigo_grupo) REFERENCES GRUPO_AMIGOS(codigo),
    FOREIGN KEY (nome_usuario, nome_pagina) REFERENCES PAGINA(nome_usuario, nome_pagina)
);

-- PAGINA_EMPRESARIAL
CREATE TABLE PAGINA_EMPRESARIAL (
    nome_usuario VARCHAR(50),
    nome_pagina VARCHAR(100),
    cnpj CHAR(14),
    tx_rejeicao NUMERIC(5,2),
    tx_cliques NUMERIC(5,2),
    tx_conversao NUMERIC(5,2),
    PRIMARY KEY (nome_usuario, nome_pagina),
    FOREIGN KEY (nome_usuario, nome_pagina) REFERENCES PAGINA(nome_usuario, nome_pagina),
    FOREIGN KEY (cnpj) REFERENCES CONTA_EMPRESARIAL(cnpj)
);

-- PRODUTO
CREATE TABLE PRODUTO (
    nome VARCHAR(100) PRIMARY KEY,
    custo NUMERIC(10,2),
    modelo VARCHAR(50),
    estado VARCHAR(50)
);

-- ANUNCIO
CREATE TABLE ANUNCIO (
    id SERIAL PRIMARY KEY,
    produto VARCHAR(100),
    custo NUMERIC(10,2),
    publico_alvo TEXT,
    nome_usuario VARCHAR(50),
    nome_pagina VARCHAR(100),
    FOREIGN KEY (produto) REFERENCES PRODUTO(nome),
    FOREIGN KEY (nome_usuario, nome_pagina) REFERENCES PAGINA(nome_usuario, nome_pagina)
);

--Inserção Tuplas:
-- USUARIOS
INSERT INTO USUARIO VALUES 
('11111111111', 'João Silva', 'joao@email.com', '11999990000', 'Rua A, 100', '1990-05-15', 'joaosilva', 'senha123'),
('22222222222', 'Maria Oliveira', 'maria@email.com', '11999991111', 'Rua B, 200', '1985-10-20', 'mariaoliveira', 'senha456'),
('33333333333', 'Empresa ABC', 'empresa@email.com', '11999992222', 'Av. Empresarial, 1000', '1980-01-01', 'abcempresa', 'senhaempresa'),
('44444444444', 'Carlos Mendes', 'carlos@email.com', '11988887777', 'Rua C, 300', '1992-08-10', 'carlitos', 'senha789'),
('55555555555', 'Luciana Braga', 'luciana@email.com', '11977776666', 'Rua D, 400', '1995-03-22', 'lucibraga', 'senha321'),
('66666666666', 'Empresa XYZ', 'contato@xyz.com', '11333334444', 'Av. Central, 900', '1983-12-01', 'xyzcorp', 'senhaemp');
-- CONTA_PESSOAL
INSERT INTO CONTA_PESSOAL VALUES 
('joaosilva', 2),
('mariaoliveira', 1),
('carlitos', 1),
('lucibraga', 0);
-- CONTA_EMPRESARIAL
INSERT INTO CONTA_EMPRESARIAL VALUES 
('abcempresa', 'Empresa ABC Ltda', '12345678000199'),
('xyzcorp', 'XYZ Soluções Ltda', '98765432000155');
-- PACOTES
INSERT INTO PACOTE (nome, preco, funcionalidades) VALUES 
('Pacote Básico', 99.90, 'Análises simples, suporte limitado'),
('Pacote Premium', 299.90, 'Análises avançadas, suporte 24h, personalização'),
('Pacote Starter', 49.90, 'Funções básicas e anúncios limitados'),
('Pacote Master', 499.90, 'Todas funcionalidades, suporte premium e consultoria');
-- SELECIONA
INSERT INTO SELECIONA VALUES 
('abcempresa', 1),
('abcempresa', 2),
('xyzcorp', 3),
('xyzcorp', 4);
-- REQ_AMIZADE
INSERT INTO REQ_AMIZADE VALUES 
('joaosilva', 'mariaoliveira', TRUE),
('mariaoliveira', 'joaosilva', TRUE),
('carlitos', 'joaosilva', FALSE),
('lucibraga', 'mariaoliveira', TRUE);
-- GRUPO_AMIGOS
INSERT INTO GRUPO_AMIGOS (nome, descricao) VALUES 
('Amigos do João', 'Amigos pessoais de João'),
('Colegas da Maria', 'Grupo da faculdade'),
('Grupo dos Devs', 'Pessoas que programam juntas'),
('Turma de 2015', 'Amigos da faculdade de 2015');
-- PARTICIPA
INSERT INTO PARTICIPA VALUES 
('joaosilva', 1),
('mariaoliveira', 2),
('carlitos', 3),
('lucibraga', 4),
('mariaoliveira', 4);
-- POSSUI
INSERT INTO POSSUI VALUES 
('joaosilva', 1),
('mariaoliveira', 2),
('carlitos', 3),
('lucibraga', 4);
-- PAGINAS
INSERT INTO PAGINA VALUES 
('joaosilva', 'Blog do João', 50),
('abcempresa', 'Promoções ABC', 300),
('xyzcorp', 'Soluções XYZ', 100),
('mariaoliveira', 'Diário da Maria', 80);
-- PODEVER
INSERT INTO PODEVER VALUES 
(1, 'joaosilva', 'Blog do João'),
(2, 'abcempresa', 'Promoções ABC'),
(3, 'xyzcorp', 'Soluções XYZ'),
(4, 'mariaoliveira', 'Diário da Maria');
-- PAGINA_EMPRESARIAL
INSERT INTO PAGINA_EMPRESARIAL VALUES 
('abcempresa', 'Promoções ABC', '12345678000199', 5.5, 350.0, 15.2),
('xyzcorp', 'Soluções XYZ', '98765432000155', 7.0, 420.0, 18.0);
-- PRODUTOS
INSERT INTO PRODUTO VALUES 
('Notebook Lenovo', 3500.00, 'IdeaPad 3', 'novo'),
('Smartphone Samsung', 2400.00, 'Galaxy S21', 'novo'),
('Impressora Epson', 899.00, 'L3250', 'usado'),
('Monitor LG', 1200.00, 'UltraWide 29"', 'semi-novo');
-- ANUNCIO
INSERT INTO ANUNCIO (produto, custo, publico_alvo, nome_usuario, nome_pagina) VALUES 
('Notebook Lenovo', 100.00, 'Estudantes e Profissionais', 'abcempresa', 'Promoções ABC'),
('Smartphone Samsung', 120.00, 'Jovens conectados', 'xyzcorp', 'Soluções XYZ'),
('Impressora Epson', 80.00, 'Escritórios pequenos', 'abcempresa', 'Promoções ABC'),
('Monitor LG', 90.00, 'Designers e Gamers', 'xyzcorp', 'Soluções XYZ');

--Consultas:
--1°:
--Consulta da quantidade de requisoções de amizades os usuários possuem
select requerida as usuario, count(requerente) as quantidade_solicitacoes_amizade
from REQ_AMIZADE
group by requerida

--2°:
-- Ordernar as páginas empresáriais mais rentáveis, (tx de cliques * tx_conversao)/taxa_rejeicao
-- (tx de cliques * tx_conversao)/taxa_rejeicao -> representa um valor especulativo de uma página
-- com alta taxa de acesso, alta taxa de conversao e baixa taxa de rejeicao
select nome_pagina, cnpj, nome_usuario, ROUND((tx_cliques * tx_conversao) / tx_rejeicao, 2) as rentabilidade
from PAGINA_EMPRESARIAL
order by rentabilidade desc

--3°:
-- Estatísica publico alvo das páginas empresarias
select pagina_empresarial.nome_pagina, publico_alvo, count(publico_alvo)
from pagina_empresarial
join anuncio on pagina_empresarial.nome_usuario = anuncio.nome_usuario
group by rollup (pagina_empresarial.nome_pagina, publico_alvo)
having publico_alvo is not NULL


-- 4°:
-- Usuários com mais de 18 anos
select nome_usuario, nome, extract (year from age(current_date, data_nascimento)) AS idade
from usuario
where extract (year from age(current_date, data_nascimento)) >= 18

--5°:
-- Quais os pacotes mais vendidos
Select pacote.nome, pacote.preco, count(codigo_pacote) as qtd_vendas_pacote
from seleciona
join pacote on seleciona.codigo_pacote = pacote.codigo
group by pacote.nome, pacote.preco
order by qtd_vendas_pacote

--6°:
-- Quantidade de Pessoas por grupo
select 
    grupo_amigos.nome,
    count(participa.nome_usuario) as total_usuarios
from grupo_amigos
left join participa on grupo_amigos.codigo = participa.codigo_grupo
group by grupo_amigos.nome
order by total_usuarios desc;

--7°:
-- código do grupo, nome do grupo
-- quantidade de usuários e a idade média deles em um determinado grupo
select participa.codigo_grupo,round(avg(extract(year from age(current_date, usuario.data_nascimento)))) as media_idade
from participa
join usuario on participa.nome_usuario = usuario.nome_usuario
group by participa.codigo_grupo

--8°:
--Quantidade total em R$ de um pacote vendido
select pacote.nome, sum(pacote.preco) as total_vendido_R$
from seleciona
join pacote on seleciona.codigo_pacote = pacote.codigo
group by pacote.nome
order by total_vendido_R$ desc

--9°:
--Media dos preços dos produtos por publico alvo
select anuncio.publico_alvo, round(avg (produto.custo),2) as media_preco
from anuncio
join produto on anuncio.produto = produto.nome
group by anuncio.publico_alvo

-- 10°:
-- Proporção de contas fantasmas na rede social
SELECT 
    ROUND(
        (SELECT COUNT(*) 
         FROM conta_pessoal 
         WHERE nro_amigos = 0) * 1.0
        / 
        (SELECT COUNT(*) 
         FROM conta_pessoal),
    4) AS proporcao_contas_fantasmas;
	

--Trigger:
-- impede inserção de páginas empresariais em grupo de amigos
CREATE OR REPLACE FUNCTION apenasPessoal()
RETURNS TRIGGER AS $$
BEGIN
    
    IF NOT EXISTS (
        SELECT 
        FROM CONTA_PESSOAL
        WHERE nome_usuario = NEW.nome_usuario
    ) THEN
        RAISE EXCEPTION 'Erro: O usuário % não é uma conta pessoal e não pode participar de grupos.', NEW.nome_usuario;
    END IF;

    
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER gatilhoApenasPessoal
BEFORE INSERT ON PARTICIPA
FOR EACH ROW
EXECUTE FUNCTION apenasPessoal();

--Utilização do Trigger:
INSERT INTO PARTICIPA(nome_usuario, codigo_grupo) VALUES('xyzcorp', 1);

-- Procedimento Armazenado:
-- Retorna o nome da pagina empresarial com maior taxa de conversão
CREATE OR REPLACE FUNCTION maiorConv()
RETURNS VARCHAR(100) AS $$
DECLARE
    nomePag VARCHAR(100);
BEGIN
    SELECT pe.nome_pagina 
    INTO nomePag
    FROM pagina_empresarial pe
    WHERE pe.tx_conversao = (SELECT MAX(tx_conversao) FROM pagina_empresarial)
    LIMIT 1;
    
    RETURN nomePag;
END;
$$ LANGUAGE plpgsql;


-- Utilizando o procedimento armazenado maiorConv
-- recebe como parametro nome de um anuncio, procura pagina com maior taxa de conversão
-- e insere esse anúncio nessa página.
CREATE OR REPLACE FUNCTION anuncioInteligente(produto_nome VARCHAR(100))
RETURNS VOID AS $$
DECLARE
    produto_registro PRODUTO%ROWTYPE;
    pagina_maior_conv VARCHAR(100);
    usuario_pagina VARCHAR(50);
BEGIN
    
    SELECT *
    INTO produto_registro
    FROM PRODUTO
    WHERE nome = produto_nome;

    pagina_maior_conv := maiorConv();

    SELECT nome_usuario 
    INTO usuario_pagina
    FROM PAGINA_EMPRESARIAL 
    WHERE nome_pagina = pagina_maior_conv;
   
    INSERT INTO ANUNCIO (produto, custo, publico_alvo, nome_usuario, nome_pagina) 
	VALUES (
        produto_registro.nome,
        produto_registro.custo,
        'Público Geral', 
        usuario_pagina,
        pagina_maior_conv
    );

END;
$$ LANGUAGE plpgsql;

SELECT anuncioInteligente('Notebook Lenovo');

SELECT * FROM ANUNCIO;