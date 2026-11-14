CREATE TABLE autor (
    id BIGINT AUTO_INCREMENT PRIMARY KEY,
    nomeReal VARCHAR(100) NOT NULL,
    nomeArtistico VARCHAR(100),
    dataNascimento DATE
);

CREATE TABLE livro (
    id BIGINT AUTO_INCREMENT PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
    editora VARCHAR(100),
    autor_id BIGINT,
    FOREIGN KEY (autor_id) REFERENCES autor(id)
);

CREATE TABLE usuario (
    id BIGINT AUTO_INCREMENT PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
    dataNascimento DATE,
    email VARCHAR(100),
    telefone VARCHAR(20)
);

CREATE TABLE revista (
    id BIGINT AUTO_INCREMENT PRIMARY KEY,
    titulo VARCHAR(100) NOT NULL,
    editora VARCHAR(100),
    numero_edicao INT,
    ano_publicacao INT,
    mes_publicacao VARCHAR(20),
    issn VARCHAR(20),
    periodicidade VARCHAR(50)
);

CREATE TABLE emprestimo (
    id BIGINT AUTO_INCREMENT PRIMARY KEY,
    data_emprestimo DATE NOT NULL,
    data_devolucao DATE,
    usuario_id BIGINT,
    livro_id BIGINT,
    revista_id BIGINT,
    FOREIGN KEY (usuario_id) REFERENCES usuario(id),
    FOREIGN KEY (livro_id) REFERENCES livro(id),
    FOREIGN KEY (revista_id) REFERENCES revista(id)
);

