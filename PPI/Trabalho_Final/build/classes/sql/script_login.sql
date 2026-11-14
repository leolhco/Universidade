-- ============================================================
-- Tabela de contas de acesso ao sistema (login / cadastro)
-- Execute DEPOIS do script.sql principal.
-- ============================================================

USE ppi04;

CREATE TABLE conta (
    id BIGINT AUTO_INCREMENT PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
    email VARCHAR(100) NOT NULL UNIQUE,
    senha VARCHAR(255) NOT NULL,          -- guarda "salt:hash", nunca a senha em texto puro
    criado_em TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Observacao: nao ha INSERT de usuario inicial de proposito.
-- A primeira conta deve ser criada pela tela cadastro.jsp, para que
-- a senha passe pelo hash da classe util.Senha.
