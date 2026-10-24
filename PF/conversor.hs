{-Trabalho de Haskell - Conversor

Professor: Dr. Alexsandro Santos Soares
Alunos: Igor Oliveira Souza E. Silva (12311BCC017) || Leonardo H. C. Oliveira (12311BCC003)
-}

{- Instruções de como compilar e executar no Linux Ubuntu:
Tendo o GHC instalado na maquina, abra o terminal no diretório que consta este arquivo.hs, digite "ghci",sem as aspas, para abrir o ambiente de programação Haskell, para compilar digite: " :load conversor.hd " sem as aspas. Para executa-lo, basta digitar no terminal, estando no diretorio deste arquivo o comando: " ./programa.exe " sem as aspas, neste último caso deverá ter o arquivo compilado e gerado este arquivo.
-}
----------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------

{-Funçao Menu - Fizemos ela no intuito de ser o menu de nosso programa. Para lidar com as varias opçoes, utilizamos a funçao case of que usara o input lido por getLine para saber qual opçao de conversao ele tratara. No caso, essas opçoes sao conhecidas no nosso programa como op's, variando de 1 a 9 e, a opçao 0 para sair do programa. Tambem no nosso menu, colocamos um caso em que o usuario nao digita uma opçao correspondente com o nosso menu. Com isso, uma mensagem sera mostrada e o menu, novamente, sera chamado. Por fim, destacamos que a funçao menu è do tipo IO, ou seja, ela realiza operaçoes de entrada e saida.
-}

menu :: IO ()
menu = do 
  putStrLn ""
  putStrLn "****************************************************"
  putStrLn "*                C o n v e r s o r                 *"
  putStrLn "****************************************************"
  putStrLn ""
  putStrLn "Opcoes:"
  putStrLn ""
  putStrLn "1 - converter de binario para decimal"
  putStrLn "2 - converter de hexadecimal para decimal"
  putStrLn "3 - converter de decimal para binario"
  putStrLn "4 - converter de decimal para hexadecimal"
  putStrLn "5 - converter de binario para hexadecimal"
  putStrLn "6 - converter de hexadecimal para binario"
  putStrLn "7 - converter de fracao binaria para decimal"
  putStrLn "8 - converter de fracao decimal para binario"
  putStrLn "9 - somar dois binarios sem sinal"
  putStrLn "0 - sair"
  putStrLn ""
  putStrLn "Digite uma opção:"
  input <- getLine
  case input of
    "1" -> op1 
    "2" -> op2
    "3" -> op3
    "4" -> op4
    "5" -> op5
    "6" -> op6
    "7" -> op7
    "8" -> op8
    "9" -> op9
    "0" -> putStrLn "Saindo do programa."
    _ -> do
      putStrLn "Opção inválida. Por favor, escolha novamente."
      menu  
-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------
{-|Aqui temos a primeira opçao, a op1 , que tem a finalidade de converter  numeros binarios inteiros para numeros decimais inteiros. A funçao op1 usa duas funçoes auxiliares, bin e bindec. A funçao bin e usada para verificar se o numero entrado è um binario valido. Ela faz isso a partir de recursao em que uma lista vazia e a condiçao de True e ela analisara o numero da seguinte maneira: o primeiro digito sera testado como sendo igual a uma das condiçoes impostas, se ele for verdadeiro sera chamada a funçao bin novamente para o restante da funçao ate chegar na condiçao de parada se o numero for binario. Se nao for, ela para no erro e retorna falso. A outra funçao auxiliar de op1 e bindec que realiza o calculo de conversao por recursividade em que o primeiro digito sera read(Funçao que transforma um tipo em outro tipo, no caso de String para Double). Esse calculo e realizado multiplicando o primeiro digito por 2 elevado ao comprimento da string e, em seguida, e somado com bindec do restante da string.
-} 

bin :: String -> Bool
bin [] = True  
bin (h:t)
  | h == '0' || h == '1' || h == '.' = bin t  
  | otherwise = False

bindec :: String -> Double
bindec [] = 0
bindec (h:t) = digit * 2^(length t) + bindec t
  where
    digit = read [h] :: Double

op1 :: IO ()
op1 = do
  putStrLn ""
  putStrLn ""
  putStrLn "Digite um binário:"
  binario <- getLine
  putStrLn ""
  if bin binario
    then do
      let decimal = bindec binario
      putStrLn $ binario ++"_(2)"++ " = " ++ show decimal ++ "_(10)"
      putStrLn ""
      putStrLn "Deseja converter outro binário (s/n)?"
      resposta <- getLine
      if resposta == "s" || resposta == "S"
        then op1
        else menu
    else do
      putStrLn "Erro: Entrada inválida. Por favor, insira apenas '0's e '1's."
      op1  
-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------
{-| Aqui temos a segunda opçao, a op2, que tem a finalidade de converter numeros hexadecimal em decimais. A funçao op2 usa 3 funçoes auxiliares, hex, hd e hexdec. A funçao hex e usada para validaçao da string lida. Ela usa recursividade para tal e, tambem, a funçao elem, incluida na biblioteca padrao do Haskell, que verifica se um item esta incluso numa lista e, se sim, chama o restante por recursividade. A funçao hd, tambem, utiliza elem para determinar qual caracter(c) esta sendo analisado. Apos isso ele utiliza a funçao fromEnum, tambem incluida na biblioteca padrao, que transforma um valor de um tipo enumerado para o seu valor numerico, utilizando a tabela ASCII como parametro e, apos isso, utiliza uma aritmetica simples para chegar nos equivalentes de decimais em hexadecimais. Por fim, a funçao hexdec realiza a conversao por recursividade. Ela utiliza a funçao fromIntegral, incluida na biblioteca padrao, que converte um resultado inteiro para o tipo numerico Double. A seguir esse resultado e multiplicado por 16 elevado ao comprimento da cauda e, depois, e somado com hexdec da cauda
-}

hex :: String -> Bool
hex [] = True
hex (h:t)
  | h `elem` ['0'..'9'] || h `elem` ['A'..'F'] || h `elem` ['a'..'f'] = hex t
  | otherwise = False

hd :: Char -> Int
hd c
  | c `elem` ['0'..'9'] = fromEnum c - fromEnum '0'
  | c `elem` ['A'..'F'] = fromEnum c - fromEnum 'A' + 10
  | c `elem` ['a'..'f'] = fromEnum c - fromEnum 'a' + 10
  | otherwise = error "Caractere hexadecimal inválido"

hexdec :: String -> Double
hexdec [] = 0
hexdec (h:t) = fromIntegral (hd h) * 16^(length t) + hexdec t


op2 :: IO ()
op2 = do
  putStrLn ""
  putStrLn "__"
  putStrLn "Digite um hexadecimal:"
  hexadecimal <- getLine
  putStrLn ""
  if hex hexadecimal
    then do
      let decimal = hexdec hexadecimal
      putStrLn $ hexadecimal ++"_(16)"++ " = " ++ show decimal ++ "_(10)"
      putStrLn ""
      putStrLn "Deseja converter outro número hexadecimal (s/n)?"
      resposta <- getLine
      if resposta == "s" || resposta == "S"
        then op2
        else menu
    else do
      putStrLn "Erro: Entrada inválida. Por favor, insira apenas dígitos hexadecimais."
      op2
-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------
{-| Aqui temos a terceira opçao, a op3, que tem o intuito de transformar um numero decimal inteiro em um numero binario inteiro. A funçao op3 utiliza duas funçoes auxiliares, decbin e dbh. Antes de chamar as funçoes auxiliares, em op3 usamos read para transformar a String em Int. Apos isso, temos duas funçoes que realizam a logica da conversao de decimal para binario, sendo que essa logica pega o resto do numero dividido por 2 e continua esse processo com o quociente ate chegar a 0. Depois, inverte a string formada.
-}

decbin :: Int -> String
decbin n
  | n == 0 = "0"
  | otherwise = reverse (dbh n)


dbh :: Int -> String
dbh n
  | n == 0    = ""
  | otherwise = show (n `mod` 2) ++ dbh (n `div` 2)

op3 :: IO ()
op3 = do
  putStrLn ""
  putStrLn "__"
  putStrLn "Digite um natural:"
  decimal1 <- getLine
  putStrLn ""
  let decimal = read decimal1 :: Int
  if decimal >= 0
    then do
      let binario = decbin decimal
      
      putStrLn $ show decimal ++"_(10)" ++ " = " ++ binario ++ "_(2)"
      putStrLn ""
      putStrLn "Deseja converter outro natural (s/n)?"
      resposta <- getLine
      if resposta == "s" || resposta == "S"
        then op3
        else menu
    else do
      putStrLn "Erro: Entrada inválida. Por favor, insira um número decimal não negativo."
      op3
-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------
{-| Aqui temos a quarta opçao, op4, que tem o intuito de converter de decimal para hexadecimal. A funçao Op4 utiliza duas funçoes auxiliares, dh e tohex. Antes de chamar as funçoes auxiliares, em op4 usamos read para transformar a String em Int. Apos isso, temos duas funçoes que realizam a logica da conversao de decimal para hexadecimal, com divisoes suscessivas por 16 e com o resto dessas contas verificando se sao menores que 10(se for, os mantem) e se nao forem menores que 10 fazem a conversao. Essas conversoes sao feitas com base na tabela ASCII(fromEnum e toEnum) -}


dh :: Int -> String
dh n
  | n == 0    = ""
  | otherwise = dh (n `div` 16) ++ tohex (n `mod` 16)




tohex :: Int -> String
tohex d
  | d < 10 = show d
  
  | otherwise = [toEnum (d + fromEnum 'A' - 10)]
  
  

op4 :: IO ()
op4 = do
  putStrLn ""
  putStrLn "__"
  putStrLn "Digite um natural:"
  decimal2 <- getLine
  putStrLn ""
  let decimal = read decimal2 :: Int
  
  let hexadecimal = dh decimal
  
  
  putStrLn $ show decimal ++ "_(10)" ++ " = " ++ hexadecimal ++ "_(16)"
  putStrLn ""
  putStrLn "Deseja converter outro natural (s/n)?"
  resposta <- getLine
  if resposta == "s" || resposta == "S"
    then op4
    else menu

-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------
{-| Aqui temos a quinta opçao, a op5, que tem a finalidade de converter um numero binario em um numero hexadecimal. A funçao op5 utiliza 5 funçoes auxiliares, binhex, grupos, multiplode4, gruposde4 e bintohex. A funçao binhex utiliza a funçao de verificaçao (ja criada e explicada) bin para validar o numero. Se for valido, chama a funçao grupos para a funçao multiplode4 do nosso numero binario. A funçao grupos faz a conversao propriamente dita por recursao, auxiliada pela funçao tabela bintohex. A funçao multiplode4 verifica se a string e divisivel por 4, se for chama a funçao gruposde4. Se a string nao for divisivel por 4, ela utiliza aritmetica aliada a funçao da biblioteca padrao, replicate no intuito de adicionar 0's a esquerda, e, apos isso, chama a funçao gruposde4 para a string. A funçao gruposde4 divide a string em grupos de 4 caracteres.
-} 

binhex :: String -> String
binhex binario
  | bin binario = grupos(multiplode4 binario)
  | otherwise = error "VALOR INVALIDO! INSIRA APENAS 0's E 1's"
  

grupos :: [String] -> String
grupos [] = ""
grupos (h:t)
  | null t = bintohex h
  | otherwise = bintohex h ++ grupos t


multiplode4:: String -> [String]
multiplode4 str
  | length str `mod` 4 == 0 = gruposde4 str
  | otherwise = gruposde4 (replicate (4 - length str `mod` 4) '0' ++ str)
  

gruposde4 :: String -> [String]
gruposde4 [] = []
gruposde4 str = take 4 str : gruposde4 (drop 4 str)

bintohex :: String -> String
bintohex "0000" = "0"
bintohex "0001" = "1"
bintohex "0010" = "2"
bintohex "0011" = "3"
bintohex "0100" = "4"
bintohex "0101" = "5"
bintohex "0110" = "6"
bintohex "0111" = "7"
bintohex "1000" = "8"
bintohex "1001" = "9"
bintohex "1010" = "A"
bintohex "1011" = "B"
bintohex "1100" = "C"
bintohex "1101" = "D"
bintohex "1110" = "E"
bintohex "1111" = "F"
bintohex _      = error "Entrada inválida para conversão binário-hexadecimal"

op5 :: IO ()
op5 = do
  putStrLn ""
  putStrLn "__"
  putStrLn "Digite um binário:"
  binario <- getLine
  putStrLn ""
  if bin binario
    then do
      let hexadecimal = binhex binario
      putStrLn $ binario ++ "_(2)" ++ " = " ++ hexadecimal ++ "_(16)"
      putStrLn ""
      putStrLn "Deseja converter outro binário (s/n)?"
      resposta <- getLine
      if resposta == "s" || resposta == "S"
        then op5
        else menu
    else do
      putStrLn "Erro: Entrada inválida. Por favor, insira apenas '0's e '1's."
      op5  
-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------
{-| Aqui temos a sexta opçao, a op6, que tem o intuito de transformar um numero hexadecimal em um numero binario. A funçao op6 utiliza 3 funçoes auxiliares, hexbin, hex e hextobin. Nesse sentido, hex e usado para verificar se o numero hexadecimal e valido. A funçao hextobin faz a conversao baseada na tabela abaixo e, por fim, hexbin. Nela usamos dropWhile e concatMap, funçoes da biblioteca padrao de haskell. Enquanto a primeira removera os 0's a esquerda, a segunda aplicara a funçao hextobin aos digitos e, depois, concatenara em uma lista o resultado. Aqui tambem utilizamos o operador '$' para aplicar funçoes a argumentos de forma mais legivel e concisa.
-}

hexbin :: String -> String
hexbin hexadecimal
  | hex hexadecimal = dropWhile (== '0') $ concatMap hextobin hexadecimal
  | otherwise = error "VALOR INVALIDO! INSIRA APENAS DÍGITOS HEXADECIMAIS (0-9, A-F)"



hextobin :: Char -> String
hextobin '0' = "0000"
hextobin '1' = "0001"
hextobin '2' = "0010"
hextobin '3' = "0011"
hextobin '4' = "0100"
hextobin '5' = "0101"
hextobin '6' = "0110"
hextobin '7' = "0111"
hextobin '8' = "1000"
hextobin '9' = "1001"
hextobin 'A' = "1010"
hextobin 'B' = "1011"
hextobin 'C' = "1100"
hextobin 'D' = "1101"
hextobin 'E' = "1110"
hextobin 'F' = "1111"
hextobin  _   = error "Entrada inválida para conversão hexadecimal-binário"

op6 :: IO ()
op6 = do
  putStrLn ""
  putStrLn "__"
  putStrLn "Digite um hexadecimal:"
  hexadecimal <- getLine
  putStrLn ""
  if hex hexadecimal
    then do
      let binario = hexbin hexadecimal
      putStrLn $ hexadecimal ++"_(16)" ++ " = " ++ binario ++ "_(2)"
      putStrLn ""
      putStrLn "Deseja converter outro número hexadecimal (s/n)?"
      resposta <- getLine
      if resposta == "s" || resposta == "S"
        then op6
        else menu
    else do
      putStrLn "Erro: Entrada inválida. Por favor, insira apenas dígitos hexadecimais (0-9, A-F)."
      op6
-------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------
{-| Aqui temos a setima opçao, a op7, que tem o intuito de transformar uma fraçao binaria em uma fraçao decimal. A funçao op7 utiliza duas funçoes auxiliares, bindecfrac e bfc. A funçao bindes usa a funçao break que separa mediante um parametro uma lista, aliada a funçao case of que gera possibilidades. A seguir temos um padrao de par de valores em que a primeira parte è a parte inteira e a segunda è a parte fracionaria. Depois separamos o padrao da expressao que sera avaliada caso o padrao corresponda. Se sim, usaremos a funçao bindec que converte binarios inteiros em decimais inteiros em inteiro e a segunda funçao auxiliar de op7, bfc em decimal.
bfc,por sua vez utiliza binfrac para utilizar a logica de conversao com o expoente inicializado como 1.
-}

bindecfrac :: String -> Double
bindecfrac str = case break (== '.') str of
    (inteiro, _:decimal) -> bindec inteiro + bfc decimal

bfc :: String -> Double
bfc str = binfrac str 1
  where
    binfrac [] _ = 0
    binfrac (h:t) expoente = (read [h] :: Double) / (2 ^ expoente) + binfrac t (expoente + 1)


op7 :: IO ()
op7 = do
  putStrLn ""
  putStrLn "__"
  putStrLn "Digite um binário fracionário: "
  binario <- getLine
  putStrLn ""
  let decimal = bindecfrac binario
  putStrLn $ binario ++ "_(2)" ++ " = " ++ show decimal ++ "_(10)"
  putStrLn ""
  putStrLn "Deseja converter outro binário fracionário (s/n)?"
  resposta <- getLine
  if resposta == "s" || resposta == "S"
    then op7  
    else main
----------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------
{-| Aqui temos a oitava opçao, a op8, que tem a finalidade de converter um numero decimal fracionario em um numero binario fracionario. A funçao op8 utiliza duas funçoes auxiliares, decbinfrac e fracbin. A funçao decbinfrac separa para os calculos de conversao a parte inteira da parte fracionaria do numero binario. Para a parte inteira usara a funçao da biblioteca padrao, truncate para obtençao de tal, e, apos isso, chamara a ja criada e explicada funçao decbin para converter a parte inteira em fracionaria. Para a parte fracionaria, utilizamos a funçao fracbin para a conversao. Essa funçao e utilizada apos uma simples aritmetica para encontrar a parte fracionaria de um numero. A funçao fracbin faz multiplicaçoes suscessivas por 2 da parte fracionaria, concatenando as partes inteiras desses numeros na resposta.
-}

decbinfrac :: Double -> String
decbinfrac n
  | n == 0 = "0"
  | otherwise =  inter ++ "." ++ deci
  where
    inter = decbin (truncate n)
    deci = fracbin (n - fromIntegral (truncate n))

fracbin :: Double -> String
fracbin n
  | n == 0 = ""
  | otherwise = show (truncate (n * 2)) ++ fracbin (n * 2 - fromIntegral (truncate (n * 2)))

op8 :: IO ()
op8 = do
  putStrLn ""
  putStrLn "__"
  putStrLn "Digite um número decimal fracionário:"
  decimalStr <- getLine
  putStrLn ""
  let decimal = read decimalStr :: Double
  if decimal >= 0
    then do
      let binario = decbinfrac decimal
      putStrLn $ show decimal ++ "_(10)" ++ " = " ++ binario ++ "_(2)"
      putStrLn ""
      putStrLn "Deseja converter outro número decimal fracionário (s/n)?"
      resposta <- getLine
      if resposta == "s" || resposta == "S"
        then op8
        else menu
    else do
      putStrLn "Erro: Entrada inválida. Por favor, insira um número decimal fracionário não negativo."
      op8
----------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------
{-| Aqui temos a nona opçao, a op9, que tem o intuito de somar dois binarios sem sinais. A op9 utiliza duas funçoes auxiliares que ja foram criadas e explicadas no codigo. A finalidade delas e transformar os numeros binarios em decimais, somar esses numeros e transformar o resultado em binario.
-}
op9 :: IO ()
op9 = do
  putStrLn ""
  putStrLn "__"
  putStrLn "Digite o primeiro número binário:"
  binario1 <- getLine
  putStrLn ""
  putStrLn "Digite o segundo número binário:"
  binario2 <- getLine
  putStrLn ""
  if bin binario1 && bin binario2
    then do
      let decimal1 = bindecfrac binario1
      let decimal2 = bindecfrac binario2
      let somaDecimal = decimal1 + decimal2
      let resultadoBinario = decbinfrac somaDecimal
      putStrLn $ binario1 ++ " + " ++ binario2 ++ " = " ++ resultadoBinario ++ "_(2)"
      putStrLn ""
      putStrLn "Deseja somar outros dois números binários (s/n)?"
      resposta <- getLine
      if resposta == "s" || resposta == "S"
        then op9
        else menu
    else do
      putStrLn "Erro: Entrada inválida. Por favor, insira apenas '0's e '1's para ambos os números."
      op9
------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------

{-| Aqui temos a funçao main. Ela e do tipo IO. Ela tem funçao de chamar o menu. -}
main :: IO ()
main = do
  menu  

