USE ppi04;

INSERT INTO autor (nomeReal, nomeArtistico, dataNascimento) VALUES
('Joaquim Maria Machado de Assis', 'Machado de Assis', '1839-06-21'),
('Clarice Lispector', 'Clarice Lispector', '1920-12-10'),
('Stephen Edwin King', 'Stephen King', '1947-09-21'),
('Joanne Rowling', 'J. K. Rowling', '1965-07-31'),
('George Raymond Richard Martin', 'George R. R. Martin', '1948-09-20');

INSERT INTO livro (nome, editora, autor_id) VALUES
('Dom Casmurro', 'Editora Garnier', 1),
('A Hora da Estrela', 'Editora Rocco', 2),
('O Iluminado', 'Suma de Letras', 3),
('Harry Potter e a Pedra Filosofal', 'Rocco', 4),
('A Guerra dos Tronos', 'Leya', 5);

INSERT INTO usuario (nome, dataNascimento, email, telefone) VALUES
('Carlos Silva', '1990-05-15', 'carlos.silva@email.com', '(11) 98765-4321'),
('Ana Souza', '1985-08-22', 'ana.souza@email.com', '(21) 99887-7665'),
('Marcos Oliveira', '2001-02-10', 'marcos.oliveira@email.com', '(31) 97766-5544'),
('Juliana Costa', '1995-11-30', 'juliana.costa@email.com', '(41) 96655-4433'),
('Fernanda Lima', '1988-04-18', 'fernanda.lima@email.com', '(51) 95544-3322');

INSERT INTO revista (titulo, editora, numero_edicao, ano_publicacao, mes_publicacao, issn, periodicidade) VALUES
('Superinteressante', 'Editora Abril', 400, 2023, 'Janeiro', '0103-166X', 'Mensal'),
('Veja', 'Editora Abril', 2800, 2023, 'Fevereiro', '0100-7122', 'Semanal'),
('National Geographic', 'Editora Abril', 250, 2022, 'Março', '1513-3342', 'Mensal'),
('Mundo Estranho', 'Editora Abril', 150, 2015, 'Julho', '1676-904X', 'Mensal'),
('Galileu', 'Editora Globo', 300, 2021, 'Dezembro', '1415-0322', 'Mensal');

INSERT INTO emprestimo (data_emprestimo, data_devolucao, usuario_id, livro_id, revista_id) VALUES
('2023-10-01', '2023-10-15', 1, 1, NULL),
('2023-10-05', '2023-10-20', 2, NULL, 1),
('2023-10-10', NULL, 3, 2, 2),
('2023-10-12', '2023-10-26', 4, 3, NULL),
('2023-10-15', NULL, 5, NULL, 3);