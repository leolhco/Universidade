#Mochila 0/1 recursiva ingênua (sem memorização)
def mochila(C, valores, pesos):
    n = len(valores)
    return mochilaRec(C, valores, pesos, n)

def mochilaRec(C, valores, pesos, n):
    #Caso base
    if n == 0 or C == 0:
        return 0
    
    pegar = 0

    #Escolher o item se ele não exceder a capacidade
    if pesos[n-1] <= C:
        pegar = valores[n-1] + mochilaRec(C - pesos[n-1], valores, pesos, n-1)

    #Não escolher o item
    naoPegar = mochilaRec(C, valores, pesos, n-1)

    return max(pegar, naoPegar)

#Mochila ainda recursiva porém com memorização em matriz
def mochila_memorizacao(C, valores, pesos):
    n = len(valores)

    #Matriz de memorização
    # C+1 e n+1 = Capacidade e tamanho a partir de 0
    memo = [[-1] * (C+1) for _ in range(n+1)]

    return mochila_memo_rec(C, valores, pesos, n, memo)

def mochila_memo_rec(C, valores, pesos, n, memo):
    #Caso base
    if n==0 or C==0:
        return 0
    
    #Checar se problema foi calculado antes
    if memo[n][C] != -1:
        return memo[n][C]

    pegar = 0

    #Pegar o item se não exceder a capacidade
    if pesos[n-1] <= C:
        pegar = valores[n-1] + mochila_memo_rec(C - pesos[n-1], valores, pesos, n-1, memo)

    #Não pegar o item
    naoPegar = mochila_memo_rec(C, valores, pesos, n-1, memo)

    #Guardar o resultado na matriz
    memo[n][C] = max(pegar, naoPegar)
    return memo[n][C]

#Programação dinâmica - Mochila com iteratividade bottom-up e matriz de memorização
def mochila_PD(C, valores, pesos):
    n = len(valores)
    matriz = [[0 for _ in range(C+1)] for _ in range(n+1)]

    #Construir a tabela
    for i in range(n+1):
        for j in range(C+1):
            #Caso base
            if i==0 or j==0:
                matriz[i][j] = 0
            else:
                pegar = 0
                #Pegar o item se não exceder a capacidade
                if pesos[i-1] <= j:
                    pegar = valores[i-1] + matriz[i-1][j - pesos[i-1]]
                #Não pegar item
                naoPegar = matriz[i-1][j]
                
                matriz[i][j] = max(pegar, naoPegar)

    return matriz[n][C]
