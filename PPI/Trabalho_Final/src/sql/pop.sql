USE ppi04;

-- ==========================================
-- 1. INSERINDO 15 AUTORES
-- ==========================================
INSERT INTO autor (nomeReal, nomeArtistico, dataNascimento) VALUES
('Joaquim Maria Machado de Assis', 'Machado de Assis', '1839-06-21'),
('Clarice Lispector', 'Clarice Lispector', '1920-12-10'),
('Stephen Edwin King', 'Stephen King', '1947-09-21'),
('Joanne Rowling', 'J. K. Rowling', '1965-07-31'),
('George Raymond Richard Martin', 'George R. R. Martin', '1948-09-20'),
('John Ronald Reuel Tolkien', 'J. R. R. Tolkien', '1892-01-03'),
('Agatha Mary Clarissa Christie', 'Agatha Christie', '1890-09-15'),
('Gabriel José García Márquez', 'Gabriel García Márquez', '1927-03-06'),
('Jorge Francisco Isidoro Luis Borges', 'Jorge Luis Borges', '1899-08-24'),
('José Martiniano de Alencar', 'José de Alencar', '1829-05-01'),
('João Guimarães Rosa', 'Guimarães Rosa', '1908-06-27'),
('Aluísio Tancredo Belo Gonçalves de Azevedo', 'Aluísio Azevedo', '1857-04-14'),
('Isaac Asimov', 'Isaac Asimov', '1920-01-02'),
('Arthur Ignatius Conan Doyle', 'Arthur Conan Doyle', '1859-05-22'),
('Richard Russell Riordan Jr.', 'Rick Riordan', '1964-06-05');

-- ==========================================
-- 2. INSERINDO 15 LIVROS (Vinculados aos Autores de 1 a 15)
-- ==========================================
INSERT INTO livro (nome, editora, autor_id) VALUES
('Dom Casmurro', 'Editora Garnier', 1),
('A Hora da Estrela', 'Editora Rocco', 2),
('O Iluminado', 'Suma de Letras', 3),
('Harry Potter e a Pedra Filosofal', 'Rocco', 4),
('A Guerra dos Tronos', 'Leya', 5),
('O Senhor dos Anéis: A Sociedade do Anel', 'HarperCollins', 6),
('O Assassinato no Expresso do Oriente', 'Globo Livros', 7),
('Cem Anos de Solidão', 'Editora Record', 8),
('Ficções', 'Companhia das Letras', 9),
('O Guarani', 'Editora Ática', 10),
('Grande Sertão: Veredas', 'Nova Fronteira', 11),
('O Cortiço', 'Martin Claret', 12),
('Eu, Robô', 'Editora Aleph', 13),
('Um Estudo em Vermelho', 'Editora Zahar', 14),
('Percy Jackson e o Ladrão de Raios', 'Intrínseca', 15);

-- ==========================================
-- 3. INSERINDO 15 USUÁRIOS
-- ==========================================
INSERT INTO usuario (nome, dataNascimento, email, telefone) VALUES
('Carlos Silva', '1990-05-15', 'carlos.silva@email.com', '(11) 98765-4321'),
('Ana Souza', '1985-08-22', 'ana.souza@email.com', '(21) 99887-7665'),
('Marcos Oliveira', '2001-02-10', 'marcos.oliveira@email.com', '(31) 97766-5544'),
('Juliana Costa', '1995-11-30', 'juliana.costa@email.com', '(41) 96655-4433'),
('Fernanda Lima', '1988-04-18', 'fernanda.lima@email.com', '(51) 95544-3322'),
('Pedro Santos', '1992-07-12', 'pedro.santos@email.com', '(61) 91234-5678'),
('Maria Oliveira', '1980-03-25', 'maria.oliveira@email.com', '(71) 92345-6789'),
('Lucas Pereira', '2005-09-18', 'lucas.pereira@email.com', '(81) 93456-7890'),
('Camila Rodrigues', '1998-12-05', 'camila.rodrigues@email.com', '(91) 94567-8901'),
('Rafael Gomes', '1987-06-20', 'rafael.gomes@email.com', '(11) 95678-9012'),
('Beatriz Martins', '2002-01-15', 'beatriz.martins@email.com', '(21) 96789-0123'),
('Thiago Almeida', '1995-04-30', 'thiago.almeida@email.com', '(31) 97890-1234'),
('Amanda Carvalho', '1991-10-10', 'amanda.carvalho@email.com', '(41) 98901-2345'),
('Diego Ribeiro', '1983-02-28', 'diego.ribeiro@email.com', '(51) 99012-3456'),
('Letícia Fernandes', '2000-08-08', 'leticia.fernandes@email.com', '(61) 90123-4567');

-- ==========================================
-- 4. INSERINDO 15 REVISTAS (Com Periodicidade Padronizada)
-- ==========================================
INSERT INTO revista (titulo, editora, numero_edicao, ano_publicacao, mes_publicacao, issn, periodicidade) VALUES
('Superinteressante', 'Editora Abril', 400, 2023, 'Janeiro', '0103-166X', 'Mensal'),
('Veja', 'Editora Abril', 2800, 2023, 'Fevereiro', '0100-7122', 'Semanal'),
('National Geographic', 'Editora Abril', 250, 2022, 'Março', '1513-3342', 'Mensal'),
('Mundo Estranho', 'Editora Abril', 150, 2015, 'Julho', '1676-904X', 'Mensal'),
('Galileu', 'Editora Globo', 300, 2021, 'Dezembro', '1415-0322', 'Mensal'),
('Época', 'Editora Globo', 1100, 2021, 'Maio', '1415-5494', 'Semanal'),
('Piauí', 'Editora Alvinegra', 190, 2022, 'Agosto', '1980-1750', 'Mensal'),
('Quatro Rodas', 'Editora Abril', 750, 2023, 'Setembro', '0033-5908', 'Mensal'),
('Ciência Hoje', 'Instituto CH', 300, 2014, 'Novembro', '0103-4634', 'Trimestral'),
('Claudia', 'Editora Abril', 680, 2023, 'Outubro', '0009-8485', 'Mensal'),
('Exame', 'Editora Abril', 1200, 2023, 'Abril', '0014-4628', 'Bimestral'),
('Aventuras na História', 'Editora Caras', 215, 2021, 'Janeiro', '1679-4119', 'Mensal'),
('Saúde', 'Editora Abril', 450, 2022, 'Junho', '0104-3481', 'Mensal'),
('Guia do Estudante', 'Editora Abril', 50, 2023, 'Julho', '1999-2222', 'Semestral'),
('Almanaque Abril', 'Editora Abril', 45, 2023, 'Fevereiro', '1888-3333', 'Anual');

-- ==========================================
-- 5. INSERINDO 15 EMPRÉSTIMOS
-- ==========================================
INSERT INTO emprestimo (data_emprestimo, data_devolucao, usuario_id, livro_id, revista_id) VALUES
('2023-10-01', '2023-10-15', 1, 1, NULL),
('2023-10-05', '2023-10-20', 2, NULL, 1),
('2023-10-10', NULL, 3, 2, 2),
('2023-10-12', '2023-10-26', 4, 3, NULL),
('2023-10-15', NULL, 5, NULL, 3),
('2024-01-10', '2024-01-24', 6, 6, NULL),
('2024-01-15', NULL, 7, NULL, 7),
('2024-02-01', '2024-02-15', 8, 8, 8),
('2024-02-20', NULL, 9, 9, NULL),
('2024-03-05', '2024-03-19', 10, NULL, 10),
('2024-03-10', NULL, 11, 11, NULL),
('2024-04-01', '2024-04-15', 12, 12, 12),
('2024-04-20', '2024-05-04', 13, 13, NULL),
('2024-05-10', NULL, 14, NULL, 14),
('2024-05-15', '2024-05-29', 15, 14, 15);