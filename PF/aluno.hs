{-
Trabalho de Haskell - Manipulador de Arquivos
Professor: Dr. Alexsandro Santos Soares
Alunos: Igor Oliveira Souza E. Silva (12311BCC017) || Leonardo H. C. Oliveira (12311BCC003)
-}

{- Instruções de como compilar e executar no Linux Ubuntu:
Tendo o GHC instalado na maquina, abra o terminal no diretório que consta este arquivo.hs, digite "ghci",sem as aspas, para abrir o ambiente de programação Haskell, para compilar digite: " :load a.hs " sem as aspas. Para executa-lo, basta digitar no terminal, estando no diretorio deste arquivo o comando: " ./programa.exe " sem as aspas, neste último caso deverá ter o arquivo compilado e gerado este arquivo.
-}

------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------
import System.IO
import System.Directory
import Data.List (find, sort)
import Text.Printf

{-| A seguir esta a definiçao da estrutura de dados Estudante, com campos como nome, matrícula, notas e faltas, e o tipo Turma, que é uma lista de estudantes.|-}



data Estudante = Estudante {
    nome :: String,
    matricula :: String,
    notasProva :: [Int],
    notasTrabalho :: [Int],
    faltas :: Int,
    notaFinal :: Int,
    situacaoFinal :: Char
} deriving (Show, Eq)  


type Turma = [Estudante]


------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------
{-| Aqui temos a funçao main. Ela e do tipo IO. Ela tem funçao de chamar o menu. -}
main :: IO ()
main = menuprincipal Nothing

------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------
{-Funçao Menu - Fizemos ela no intuito de ser o menu de nosso programa. Para lidar com as varias opçoes, utilizamos a funçao case of que usara o input lido por getLine para saber qual opçao de manipulaçao de arquivo ele tratara. No caso, sao 7 opçoes no nosso programa, variando de 1 a 7. Tambem no nosso menu, colocamos um caso em que o usuario nao digita uma opçao correspondente com o nosso menu. Com isso, uma mensagem sera mostrada e o menu, novamente, sera chamado. Por fim, destacamos que a funçao menu è do tipo IO, ou seja, ela realiza operaçoes de entrada e saida.
-}

menuprincipal :: Maybe Turma -> IO ()
menuprincipal turma = do
    putStrLn "========================================="
    putStrLn "            Menu Principal               "
    putStrLn "========================================="
    putStrLn "Opções:"
    putStrLn "1 - Ler turma de estudantes do arquivo"
    putStrLn "2 - Imprimir turma de estudantes"
    putStrLn "3 - Imprimir estatísticas da turma"
    putStrLn "4 - Cadastrar novo estudante"
    putStrLn "5 - Editar informações de um estudante"
    putStrLn "6 - Reler turma de estudantes do arquivo"
    putStrLn "7 - Salvar e Sair"
    putStrLn "Digite uma opção: "
    opcao <- getLine
    case opcao of
        "1" -> menulerturma
        "2" -> do
                case turma of
                  Just t -> printfm t
                  Nothing -> putStrLn "Nenhuma turma lida ainda. Por favor, leia uma turma primeiro."
                menuprincipal turma
        "3" -> do
                case turma of
                  Just t -> imprimirEstatisticas t
                  Nothing -> putStrLn "Nenhuma turma lida ainda. Por favor, leia uma turma primeiro."
                menuprincipal turma
        "4" -> do
                case turma of
                  Just t -> novoestudante (Just t)
                  Nothing -> novoestudante Nothing
        "5" -> do
                case turma of
                  Just t -> menuee t
                  Nothing -> putStrLn "Nenhuma turma lida ainda. Por favor, leia uma turma primeiro."
        "6" -> menurelerturma
        "7" -> menuss turma
        _ -> putStrLn "Opção inválida"

------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------
{-| 1 OPÇAO DO MENU PRINCIPAL |-}
{-| MENU SECUNDARIO DA 1 OPÇAO DO MENU PRINCIPAL |-}


menulerturma :: IO ()
menulerturma = do
    putStrLn "========================================="
    putStrLn "              Ler Turma                 "
    putStrLn "========================================="
    putStrLn "Opções:"
    putStrLn "1 - Ler turma existente"
    putStrLn "2 - Criar nova turma"
    putStrLn "3 - Voltar ao menu principal"
    putStrLn "Digite uma opção: "
    opcao <- getLine
    case opcao of
        "1" -> lerturmaexistente
        "2" -> criarnovaturma
        "3" -> main 
        _ -> do
            putStrLn "Opção inválida"
            menulerturma
------------------------------------------------------------------------------------------------------------------------------------------------------------
{-| 1 OPÇAO DO MENU SECUNDARIO DA 1 OPÇAO DO MENU PRINCIPAL |-}
{-| Para essa opçao utilizamos 4 funçoes auxiliares. Essas funções lidam com a leitura, manipulação e escrita de dados de uma turma de estudantes. lerturmaexistente verifica a existência de um arquivo de turma, lerarqturma lê e organiza os dados em uma estrutura de turma, sl divide uma lista em grupos, toestudante converte dados de estudantes em objetos. Juntas, essas funções permitem um sistema completo de gerenciamento de turma em.|-}


lerturmaexistente :: IO ()
lerturmaexistente = do
    putStrLn "Digite o nome do arquivo com a turma: "
    nomearq <- getLine
    existe <- doesFileExist nomearq
    if existe
        then do
            turma <- lerarqturma nomearq
            putStrLn "Turma lida com sucesso!"
            menuprincipal (Just turma)
        else do
            putStrLn $ "Arquivo " ++ nomearq ++ " não existe!"
            menulerturma


lerarqturma :: String -> IO Turma
lerarqturma nomearq = do
    conteudo <- readFile nomearq
    let linhas = lines conteudo
        grupos = sl 10 linhas  
    return $ map toestudante grupos


sl :: Int -> [a] -> [[a]]
sl _ [] = []
sl n xs = take n xs : sl n (drop n xs)



toestudante :: [String] -> Estudante
toestudante [n, m, np1, np2, np3, nt1, nt2, f, nf, sf] = Estudante {
    nome = n,
    matricula = m,
    notasProva = map read [np1, np2, np3],
    notasTrabalho = map read [nt1, nt2],
    faltas = read f,
    notaFinal = read nf,
    situacaoFinal = head sf
}
toestudante _ = error "Formato de dados incorreto"


------------------------------------------------------------------------------------------------------------------------------------------------------------
{-| 2 OPÇAO DO MENU SECUNDARIO DA 1 OPÇAO DO MENU PRINCIPAL |-}
{-|A função criarnovaturma  permite ao usuário criar um novo arquivo para uma turma. Ela verifica se o arquivo já existe e, se sim, pergunta se deseja sobrescrevê-lo. Se a resposta for positiva, chama a função criararq para criar o arquivo; caso contrário, volta para o menu de leitura de turma. A função criararq cria o arquivo vazio e informa ao usuário sobre o sucesso da operação.|-}

criarnovaturma :: IO ()
criarnovaturma = do
    putStrLn "Digite o nome do arquivo para a nova turma: "
    nomearq <- getLine
    existe <- doesFileExist nomearq
    if existe
        then do
            putStrLn $ "Arquivo " ++ nomearq ++ " já existe. Deseja sobrescrevê-lo? (S/N)"
            resposta <- getLine
            if resposta == "S" || resposta == "s"
                then criararq nomearq
                else menulerturma
        else criararq nomearq


criararq :: String -> IO ()
criararq nomearq = do
    writeFile nomearq ""
    putStrLn $ "Arquivo " ++ nomearq ++ " criado com sucesso."
    main

------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------
{-| 2 OPÇAO DO MENU PRINCIPAL |-}
{-| A função printfm é responsável por imprimir na tela os dados de uma turma de estudantes de forma formatada e organizada. Ela verifica se a turma está vazia e, caso contrário, imprime os dados de cada estudante usando a função printft. A função printft formata os dados de um estudante de acordo com um layout específico e a largura de cada coluna, usando a função auxiliar todir para alinhar os dados corretamente.|-}


printfm :: Turma -> IO ()
printfm [] = putStrLn "A turma está vazia."
printfm turma = do
    putStrLn "====================================================================================="
    putStrLn "          Turma de Estudantes             "
    putStrLn "====================================================================================="
    putStrLn $ "Nome\t\t    Matrícula      N1 N2 N3     T1 T2   Faltas\tNota Final   Situação"
    mapM_ printft turma
    putStrLn "====================================================================================="
    putStrLn ""
    putStrLn ""
    


printft :: Estudante -> IO ()
printft estudante = do
    let notasprovastr = unwords $ map show $ notasProva estudante
    let notastrabalhostr = unwords $ map show $ notasTrabalho estudante
    putStrLn (todir 20 (nome estudante) ++
              todir 15 (matricula estudante) ++
              todir 13 notasprovastr ++
              todir 10 notastrabalhostr ++
              todir 10 (show (faltas estudante)) ++
              todir 11 (show (notaFinal estudante)) ++
              [situacaoFinal estudante])


todir :: Int -> String -> String
todir len str = str ++ replicate (len - length str) ' '
------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------
{-| 3 OPÇAO DO MENU PRINCIPAL |-}
{-| A função imprimirEstatisticas é responsável por mostrar na tela diversas estatísticas relacionadas aos estudantes de uma turma. Ela calcula(atraves de varias funçoes auxiliares, utilizando aritmetica basica dos comandos do Haskell) e exibe as maiores e menores notas em cada tipo de avaliação, as médias e medianas das notas, um histograma de notas finais em grupos de 10 pontos, além do número e porcentagem de estudantes aprovados e reprovados por nota e por falta.|-}


imprimirEstatisticas :: Turma -> IO ()
imprimirEstatisticas turma = do
    putStrLn "-------------------------------------------------------------------------"
    putStrLn "            Estatísticas            "
    putStrLn "-------------------------------------------------------------------------"
    putStrLn "                             N1      N2      N3      T1      T2    Final"
    putStrLn "-------------------------------------------------------------------------"
    let totalEstudantes :: Double
        totalEstudantes = fromIntegral (length turma)
        (maiorN1, maiorN2, maiorN3, maiorT1, maiorT2, maiorFinal) = (notaMaiorProva1 turma, notaMaiorProva2 turma, notaMaiorProva3 turma, notaMaiorTrabalho1 turma, notaMaiorTrabalho2 turma, notaMaiorFinal turma)
        (menorN1, menorN2, menorN3, menorT1, menorT2, menorFinal) = (notaMenorProva1 turma, notaMenorProva2 turma, notaMenorProva3 turma, notaMenorTrabalho1 turma, notaMenorTrabalho2 turma, notaMenorFinal turma)
        (mediaN1, mediaN2, mediaN3, mediaT1, mediaT2, mediaFinal) = (mediaNotaProva1 turma, mediaNotaProva2 turma, mediaNotaProva3 turma, mediaNotaTrabalho1 turma, mediaNotaTrabalho2 turma, mediaNotaFinal turma)
        (medianaN1, medianaN2, medianaN3, medianaT1, medianaT2, medianaFinal) = (medianaNotaProva1 turma, medianaNotaProva2 turma, medianaNotaProva3 turma, medianaNotaTrabalho1 turma, medianaNotaTrabalho2 turma, medianaNotaFinal turma)
        histograma = calcularHistograma turma
    putStrLn $ printf "Maiores notas da turma:      %2d      %2d      %2d      %2d      %2d      %2d" maiorN1 maiorN2 maiorN3 maiorT1 maiorT2 maiorFinal
    putStrLn $ printf "Menores notas da turma:      %2d      %2d      %2d      %2d      %2d      %2d" menorN1 menorN2 menorN3 menorT1 menorT2 menorFinal
    putStrLn $ printf "Notas médias da turma:    %5.1f   %5.1f   %5.1f   %5.1f   %5.1f   %5.1f" mediaN1 mediaN2 mediaN3 mediaT1 mediaT2 mediaFinal
    putStrLn $ printf "Notas medianas da turma:  %5.1f   %5.1f   %5.1f   %5.1f   %5.1f   %5.1f" medianaN1 medianaN2 medianaN3 medianaT1 medianaT2 medianaFinal
    putStrLn "-------------------------------------------------------------------------"

  
    putStrLn "Histograma de notas finais em grupos de 10 pontos:"
    putStrLn "Nota  Frequência"
    putStrLn "-----------------"
    mapM_ (\(intervalo, freq) -> putStrLn $ intervalo ++ "  " ++ replicate freq '*') histograma

 
    let aprovadosNota = length $ filter (\x -> notaFinal x >= 60 && faltas x <= 17) turma
        reprovadosNota = length $ filter (\x -> notaFinal x < 60 && faltas x <= 17) turma
        reprovadosFalta = length $ filter (\x -> faltas x > 18) turma

  
    putStrLn "-------------------------------------------------------------------------"
    putStrLn $ printf "Número de estudantes aprovados por nota: %d (%.1f%%)" aprovadosNota (fromIntegral aprovadosNota / totalEstudantes * 100)
    putStrLn $ printf "Número de estudantes reprovados por nota: %d (%.1f%%)" reprovadosNota (fromIntegral reprovadosNota / totalEstudantes * 100)
    putStrLn $ printf "Número de estudantes reprovados por falta: %d (%.1f%%)" reprovadosFalta (fromIntegral reprovadosFalta / totalEstudantes * 100)
    putStrLn "-------------------------------------------------------------------------"


calcularHistograma :: Turma -> [(String, Int)]
calcularHistograma turma = map (\inicio -> (show inicio ++ " - " ++ show (inicio + 10), length $ filter (\nota -> nota >= inicio && nota < inicio + 10) notasFinais)) [0 ,10..90] 
    where
        notasFinais = map notaFinal turma




notaMaiorProva1, notaMenorProva1, notaMaiorProva2, notaMenorProva2, notaMaiorProva3, notaMenorProva3 :: Turma -> Int
notaMaiorProva1 = maximum . map (head . notasProva)
notaMenorProva1 = minimum . map (head . notasProva)
notaMaiorProva2 = maximum . map (head . tail . notasProva)
notaMenorProva2 = minimum . map (head . tail . notasProva)
notaMaiorProva3 = maximum . map (last . notasProva)
notaMenorProva3 = minimum . map (last . notasProva)

notaMaiorTrabalho1, notaMenorTrabalho1, notaMaiorTrabalho2, notaMenorTrabalho2 :: Turma -> Int
notaMaiorTrabalho1 = maximum . map (head . notasTrabalho)
notaMenorTrabalho1 = minimum . map (head . notasTrabalho)
notaMaiorTrabalho2 = maximum . map (last . notasTrabalho)
notaMenorTrabalho2 = minimum . map (last . notasTrabalho)

notaMaiorFinal, notaMenorFinal :: Turma -> Int
notaMaiorFinal = maximum . map notaFinal
notaMenorFinal = minimum . map notaFinal

mediaNotaProva1, mediaNotaProva2, mediaNotaProva3 :: Turma -> Float
mediaNotaProva1 turma = fromIntegral (sum (map (head . notasProva) turma)) / fromIntegral (length turma)
mediaNotaProva2 turma = fromIntegral (sum (map (head . tail . notasProva) turma)) / fromIntegral (length turma)
mediaNotaProva3 turma = fromIntegral (sum (map (last . notasProva) turma)) / fromIntegral (length turma)

mediaNotaTrabalho1, mediaNotaTrabalho2 :: Turma -> Float
mediaNotaTrabalho1 turma = fromIntegral (sum (map (head . notasTrabalho) turma)) / fromIntegral (length turma)
mediaNotaTrabalho2 turma = fromIntegral (sum (map (last . notasTrabalho) turma)) / fromIntegral (length turma)

mediaNotaFinal :: Turma -> Float
mediaNotaFinal turma = fromIntegral (sum (map notaFinal turma)) / fromIntegral (length turma)

medianaNotaProva1, medianaNotaProva2, medianaNotaProva3 :: Turma -> Float
medianaNotaProva1 = mediana . map (fromIntegral . head . notasProva)
medianaNotaProva2 = mediana . map (fromIntegral . head . tail . notasProva)
medianaNotaProva3 = mediana . map (fromIntegral . last . notasProva)

medianaNotaTrabalho1, medianaNotaTrabalho2 :: Turma -> Float
medianaNotaTrabalho1 = mediana . map (fromIntegral . head . notasTrabalho)
medianaNotaTrabalho2 = mediana . map (fromIntegral . last . notasTrabalho)

medianaNotaFinal :: Turma -> Float
medianaNotaFinal = mediana . map fromIntegral . map notaFinal

mediana :: (Ord a, Fractional a) => [a] -> a
mediana xs
    | odd n = sort xs !! (fromIntegral (n `div` 2))
    | otherwise = (sort xs !! (fromIntegral (n `div` 2) - 1) + sort xs !! (fromIntegral (n `div` 2))) / 2
    where
        n = length xs
        




------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------
{-| OPÇAO 4 DO MENU PRINCIPAL |-} 
{-| A função novoestudante permite ao usuário cadastrar um novo estudante em uma turma existente, caso ela esteja carregada. Ela solicita informações como nome, matrícula, notas de provas e trabalhos, número de faltas, calcula a nota final e a situação final do estudante com base nas notas e faltas. Se não houver turma carregada, e exibida uma mensagem informando isso. A função leNota é utilizada para ler uma nota do usuário.|-}

novoestudante :: Maybe Turma -> IO ()
novoestudante (Just turma) = do
    putStrLn "Digite o nome do estudante: "
    nome <- getLine
    putStrLn "Digite a matrícula do estudante: "
    matricula <- getLine
    putStrLn "Digite as três notas das provas, pressionando Enter após cada uma:"
    notasProva <- sequence [leNota "prova 1", leNota "prova 2", leNota "prova 3"]
    putStrLn "Digite as duas notas dos trabalhos, pressionando Enter após cada uma:"
    notasTrabalho <- sequence [leNota "trabalho 1", leNota "trabalho 2"]
    putStrLn "Digite o número de faltas do estudante:"
    faltas <- readLn
    let notaFinal = sum notasProva + sum notasTrabalho
    let situacaoFinal = if faltas > 18
                        then 'F'
                        else if notaFinal >= 60
                             then 'A'
                             else 'R'
    let nwe = Estudante {
        nome = nome,
        matricula = matricula,
        notasProva = notasProva,
        notasTrabalho = notasTrabalho,
        faltas = faltas,
        notaFinal = notaFinal,
        situacaoFinal = situacaoFinal
    }
    let nwc = nwe : turma
    putStrLn "Estudante cadastrado com sucesso."
    menuprincipal (Just nwc)
novoestudante Nothing = do
    putStrLn "Não há turma carregada!"
    menuprincipal Nothing


leNota :: String -> IO Int
leNota xy = do
    putStrLn $ "Digite a nota de " ++ xy ++ ":"
    readLn
------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------
{-| 5 OPÇAO DO MENU PRINCIPAL |-}
{-| A função menuee permite selecionar e editar informações de estudantes em uma turma. Ela oferece opções para buscar estudantes por matrícula ou nome e posteriormente editar dados como nome, matrícula, notas, faltas, entre outros. Ela utiliza dois tipos de funçoes auxiliares. Enquanto as do primeiro tipo buscam o estudante com base em um parametro, as restantes realizam as alteraçoes nos dados do estudante. |-}

menuee :: Turma -> IO ()
menuee turma = do
    putStrLn "========================================="
    putStrLn "     Editar Informações de Estudante     "
    putStrLn "========================================="
    putStrLn "Opções:"
    putStrLn "1 - Selecionar por matrícula"
    putStrLn "2 - Selecionar por nome"
    putStrLn "3 - Voltar ao menu anterior"
    putStrLn "Digite uma opção: "
    opcao <- getLine
    case opcao of
        "1" -> pormatricula turma
        "2" -> pornome turma
        "3" -> menuprincipal (Just turma)
        _ -> do
            putStrLn "Opção inválida"
            menuee turma


pormatricula :: Turma -> IO ()
pormatricula turma = do
    putStrLn "Digite a matrícula do estudante: "
    matricula <- getLine
    let estudante = eepmatricula matricula turma
    case estudante of
        Just e -> menueo e turma
        Nothing -> do
            putStrLn "Estudante não encontrado."
            menuee turma


pornome :: Turma -> IO ()
pornome turma = do
    putStrLn "Digite o nome do estudante: "
    nome <- getLine
    let estudante = eepnome nome turma
    case estudante of
        Just e -> menueo e turma
        Nothing -> do
            putStrLn "Estudante não encontrado."
            menuee turma


eepmatricula :: String -> Turma -> Maybe Estudante
eepmatricula _ [] = Nothing
eepmatricula matriculabuscada (e:es)
    | matriculabuscada == matricula e = Just e
    | otherwise = eepmatricula matriculabuscada es



eepnome :: String -> Turma -> Maybe Estudante
eepnome _ [] = Nothing
eepnome nome (e:es)
    | nome == Main.nome e = Just e
    | otherwise = eepnome nome es





menueo :: Estudante -> Turma -> IO ()
menueo estudante turma = do
    putStrLn "========================================="
    putStrLn "       Editar Opções de Estudante        "
    putStrLn "========================================="
    putStrLn "Opções:"
    putStrLn "1 - Alterar nome"
    putStrLn "2 - Alterar matrícula"
    putStrLn "3 - Alterar nota da prova 1"
    putStrLn "4 - Alterar nota da prova 2"
    putStrLn "5 - Alterar nota da prova 3"
    putStrLn "6 - Alterar nota do trabalho 1"
    putStrLn "7 - Alterar nota do trabalho 2"
    putStrLn "8 - Alterar número de faltas"
    putStrLn "9 - Voltar ao menu principal"
    putStrLn "Digite uma opção: "
    opcao <- getLine
    case opcao of
        "1" -> novonome estudante turma
        "2" -> novamatricula estudante turma
        "3" -> novanotaprova1 estudante turma
        "4" -> novanotaprova2 estudante turma
        "5" -> novanotaprova3 estudante turma
        "6" -> novanotatrabalho1 estudante turma
        "7" -> novanotatrabalho2 estudante turma
        "8" -> novafaltas estudante turma
        "9" -> menuprincipal (Just turma)
        _ -> do
            putStrLn "Opção inválida"
            menueo estudante turma


novonome :: Estudante -> Turma -> IO ()
novonome estudante turma = do
    putStrLn "Digite o novo nome do estudante: "
    novoNome <- getLine
    let novoEstudante = estudante { nome = novoNome }
    let turmaAtualizada = subsestudante estudante novoEstudante turma
    putStrLn "Nome alterado com sucesso."
    menueo novoEstudante turmaAtualizada


novamatricula :: Estudante -> Turma -> IO ()
novamatricula estudante turma = do
    putStrLn "Digite a nova matrícula do estudante: "
    novaMatricula <- getLine
    let novoEstudante = estudante { matricula = novaMatricula }
    let turmaAtualizada = subsestudante estudante novoEstudante turma
    putStrLn "Matrícula alterada com sucesso."
    menueo novoEstudante turmaAtualizada

novanotaprova1 :: Estudante -> Turma -> IO ()
novanotaprova1 estudante turma = do
    putStrLn "Digite a nova nota da prova 1: "
    novaNota <- readLn
    let novasNotasProva = novaNota : drop 1 (notasProva estudante)
    let novoEstudante = estudante { notasProva = novasNotasProva }
    let turmaAtualizada = subsestudante estudante novoEstudante turma
    putStrLn "Nota da prova 1 alterada com sucesso."
    menueo novoEstudante turmaAtualizada


novanotaprova2 :: Estudante -> Turma -> IO ()
novanotaprova2 estudante turma = do
    putStrLn "Digite a nova nota da prova 2: "
    novaNota <- readLn
    let novasNotasProva = take 1 (notasProva estudante) ++ [novaNota] ++ drop 2 (notasProva estudante)
    let novoEstudante = estudante { notasProva = novasNotasProva }
    let turmaAtualizada = subsestudante estudante novoEstudante turma
    putStrLn "Nota da prova 2 alterada com sucesso."
    menueo novoEstudante turmaAtualizada


novanotaprova3 :: Estudante -> Turma -> IO ()
novanotaprova3 estudante turma = do
    putStrLn "Digite a nova nota da prova 3: "
    novaNota <- readLn
    let novasNotasProva = take 2 (notasProva estudante) ++ [novaNota]
    let novoEstudante = estudante { notasProva = novasNotasProva }
    let turmaAtualizada = subsestudante estudante novoEstudante turma
    putStrLn "Nota da prova 3 alterada com sucesso."
    menueo novoEstudante turmaAtualizada


novanotatrabalho1 :: Estudante -> Turma -> IO ()
novanotatrabalho1 estudante turma = do
    putStrLn "Digite a nova nota do trabalho 1: "
    novaNota <- readLn
    let novasNotasTrabalho = novaNota : drop 1 (notasTrabalho estudante)
    let novoEstudante = estudante { notasTrabalho = novasNotasTrabalho }
    let turmaAtualizada = subsestudante estudante novoEstudante turma
    putStrLn "Nota do trabalho 1 alterada com sucesso."
    menueo novoEstudante turmaAtualizada


novanotatrabalho2 :: Estudante -> Turma -> IO ()
novanotatrabalho2 estudante turma = do
    putStrLn "Digite a nova nota do trabalho 2: "
    novaNota <- readLn
    let novasNotasTrabalho = take 1 (notasTrabalho estudante) ++ [novaNota]
    let novoEstudante = estudante { notasTrabalho = novasNotasTrabalho }
    let turmaAtualizada = subsestudante estudante novoEstudante turma
    putStrLn "Nota do trabalho 2 alterada com sucesso."
    menueo novoEstudante turmaAtualizada


novafaltas :: Estudante -> Turma -> IO ()
novafaltas estudante turma = do
    putStrLn "Digite o novo número de faltas do estudante: "
    novasFaltas <- readLn
    let novoEstudante = estudante { faltas = novasFaltas }
    let turmaAtualizada = subsestudante estudante novoEstudante turma
    putStrLn "Número de faltas alterado com sucesso."
    menueo novoEstudante turmaAtualizada


subsestudante :: Estudante -> Estudante -> Turma -> Turma
subsestudante estudanteAntigo estudanteNovo = map (\e -> if e == estudanteAntigo then estudanteNovo else e)

----------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------
{-| 6 OPÇAO DO MENU PRINCIPAL |-}
{-Responsável por permitir ao usuário ler uma turma de estudantes de um arquivo. Ela verifica se o arquivo existe . Se o arquivo existir, chamará o arquivo da turma especificado. Se a leitura for bem-sucedida, exibe uma mensagem indicando que o arquivo foi lido com sucesso e retorna ao menu principal, passando a turma lida como argumento. Se o arquivo não existir, mostra uma mensagem informando que o arquivo não existe e retorna ao menu principal com Nothing como argumento, indicando que não há turma carregada.
-}

menurelerturma :: IO ()
menurelerturma = do
    putStrLn "========================================="
    putStrLn "   Reler Turma de Estudantes do Arquivo  "
    putStrLn "========================================="
    putStrLn "Digite o nome do arquivo com a turma: "
    nomearq <- getLine
    existe <- doesFileExist nomearq
    if existe
        then do
            turma <- lerarqturma nomearq
            putStrLn $ "Arquivo " ++ nomearq ++ " lido com sucesso!"
            menuprincipal (Just turma)
        else do
            putStrLn $ "Arquivo " ++ nomearq ++ " não existe!"
            menuprincipal Nothing

------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------
{-| 7 OPÇAO DO MENU PRINCIPAL-}
{-Responsável por salvar uma turma em um arquivo e encerrar o programa. Ela primeiro verifica se há uma turma carregada. Se não houver, exibe uma mensagem indicando isso. Se houver, solicita ao usuário o nome do arquivo onde deseja salvar a turma. Em seguida, verifica se o arquivo já existe. Se existir, pergunta ao usuário se deseja sobrescrevê-lo ou não. Se o usuário optar por sobrescrever, a função salva a turma no arquivo e encerra o programa. Se não, apenas encerra o programa.Se o arquivo não existir, a função pergunta se o usuário deseja criar um novo arquivo. Se sim, salva a turma no arquivo e encerra o programa. Se não, apenas encerra o programa.|-}

menuss :: Maybe Turma -> IO ()
menuss Nothing = do
    putStrLn "Não há turma para salvar."
    putStrLn "Até a próxima."
    putStrLn "Programa encerrado."
menuss (Just turma) = do
    putStrLn "========================================="
    putStrLn "         Salvar e Sair                   "
    putStrLn "========================================="
    putStrLn "Verificando se há uma turma carregada..."
    putStrLn "Digite o nome do arquivo para salvar a turma: "
    nomearq <- getLine
    existe <- doesFileExist nomearq
    if existe
        then do
            putStrLn $ "Arquivo " ++ nomearq ++ " já existe."
            putStrLn "Deseja sobrescrevê-lo? (S/N)"
            resposta <- getLine
            if resposta == "S" || resposta == "s"
                then salvart nomearq turma >> putStrLn "Até a próxima." >> putStrLn "Programa encerrado."
                else putStrLn "Até a próxima." >> putStrLn "Programa encerrado."
        else do
            putStrLn $ "Arquivo " ++ nomearq ++ " não existe."
            putStrLn "Deseja criar um novo? (S/N)"
            resposta <- getLine
            if resposta == "S" || resposta == "s"
                then salvart nomearq turma >> putStrLn "Até a próxima." >> putStrLn "Programa encerrado." 
                else putStrLn "Até a próxima." >> putStrLn "Programa encerrado." 
                
                
salvart :: String -> Turma -> IO ()
salvart nomearq turma = do
    let conteudo = concatMap formatare turma
    writeFile nomearq conteudo
    putStrLn "Turma salva com sucesso."
    
formatare :: Estudante -> String
formatare estudante =
    nome estudante ++ "\n" ++ matricula estudante ++ "\n" ++
    unlines (map show $ notasProva estudante) ++
    unlines (map show $ notasTrabalho estudante) ++
    show (faltas estudante) ++ "\n" ++
    show (notaFinal estudante) ++ "\n" ++
    [situacaoFinal estudante] ++ "\n"
    


