import random
import math

def populacao_inicial(tamanho_pop, num_cidades):
    populacao = []
    individuo_base = []
    for i in range(num_cidades):
        individuo_base.append(i)
        
    for _ in range(tamanho_pop):
        individuo_embaralhado = individuo_base[:]
        random.shuffle(individuo_embaralhado)
        populacao.append(individuo_embaralhado)
        
    return populacao


def fitness(individuo, matriz_inicial):
    distancia_total = 0
    num_cidades = len(individuo)
    
    for i in range(num_cidades):
        cidade_atual = individuo[i]
        
        if i == num_cidades - 1:
            proxima_cidade = individuo[0]
        else:
            proxima_cidade = individuo[i + 1]
            
        distancia_total += matriz_inicial[cidade_atual][proxima_cidade]
    
    if distancia_total == 0:
        fitness = 9999999 
    else:
        fitness = 1.0 / distancia_total
        
    return fitness, distancia_total


def order_crossover(pai1, pai2):
    tamanho = len(pai1)
    
    ponto1 = random.randint(0, tamanho - 1)
    ponto2 = random.randint(0, tamanho - 1)
    
    if ponto1 > ponto2:
        inicio = ponto2
        fim = ponto1
    else:
        inicio = ponto1
        fim = ponto2

    filho = [None] * tamanho
    cidades_copiadas = []
    
    for i in range(inicio, fim + 1):
        filho[i] = pai1[i]
        cidades_copiadas.append(pai1[i])
    
    k = (fim + 1) % tamanho
    
    for passo in range(tamanho):
        idx_p2 = (fim + 1 + passo) % tamanho
        c = pai2[idx_p2]
        
        if c not in cidades_copiadas:
            filho[k] = c
            k = (k + 1) % tamanho 
            
    return filho


def mutacao_swap(individuo, taxa_mutacao):
    chance = random.random()
    
    if chance < taxa_mutacao:
        idx1 = random.randint(0, len(individuo) - 1)
        idx2 = random.randint(0, len(individuo) - 1)
        
        temp = individuo[idx1]
        individuo[idx1] = individuo[idx2]
        individuo[idx2] = temp
        
    return individuo


def mutacao_inversao(individuo, taxa_mutacao):
    if random.random() < taxa_mutacao:
        i, j = sorted(random.sample(range(len(individuo)), 2))
        individuo[i:j+1] = reversed(individuo[i:j+1])
    return individuo

def selecao_roleta(populacao, scores_fitness):
    soma_fitness = sum(scores_fitness)
    valor_sorteado = random.uniform(0, soma_fitness)
    
    soma_acumulada = 0
    for i, fitness_ind in enumerate(scores_fitness):
        soma_acumulada += fitness_ind
        if soma_acumulada >= valor_sorteado:
            return populacao[i]
            
    return populacao[-1]


def ag(lista_arestas, tamanho_pop, geracoes, taxa_cruzamento, taxa_mutacao):
    num_cidades = 0
    for origem, destino, peso in lista_arestas:
        num_cidades = max(num_cidades, origem, destino)
    num_cidades += 1 
    
    matriz_distancias = [[0] * num_cidades for _ in range(num_cidades)]
    for origem, destino, peso in lista_arestas:
        matriz_distancias[origem][destino] = peso
        matriz_distancias[destino][origem] = peso
        
    populacao = populacao_inicial(tamanho_pop, num_cidades)
    
    melhor_individuo_global = None
    menor_distancia_global = float('inf')
    
    for geracao in range(geracoes):
        resultados = [fitness(ind, matriz_distancias) for ind in populacao]
        scores_fitness = [res[0] for res in resultados]
        distancias = [res[1] for res in resultados]
        
        menor_dist_atual = min(distancias)
        melhor_idx_atual = distancias.index(menor_dist_atual)
        
        if menor_dist_atual < menor_distancia_global:
            menor_distancia_global = menor_dist_atual
            melhor_individuo_global = populacao[melhor_idx_atual][:]
            
        nova_populacao = []
        
        nova_populacao.append(populacao[melhor_idx_atual][:])
        
        while len(nova_populacao) < tamanho_pop:
            pai1 = selecao_roleta(populacao, scores_fitness)
            pai2 = selecao_roleta(populacao, scores_fitness)
            
            if random.random() < taxa_cruzamento:
                filho = order_crossover(pai1, pai2)
            else:
                filho = pai1[:] 

            filho = mutacao_inversao(filho, taxa_mutacao) 
            
            if fitness(pai1, matriz_distancias)[1] < fitness(pai2, matriz_distancias)[1]:
                melhor_pai = pai1
            else:
                melhor_pai = pai2

            if fitness(melhor_pai, matriz_distancias)[1] < fitness(filho, matriz_distancias)[1]:
                nova_populacao.append(melhor_pai)
            else:
                nova_populacao.append(filho)
            
        populacao = nova_populacao
        
        if (geracao + 1) % 100 == 0:
            print("Geração", geracao + 1, "| Menor Distância Encontrada:", menor_distancia_global)
            
    print("\n--- Concluído ---")
    print("Rota Final:", melhor_individuo_global)
    print("Distância Final:", menor_distancia_global)
    
    return melhor_individuo_global, menor_distancia_global


if __name__ == "__main__":
    coordenadas = [
        (565.0, 575.0),
        (25.0, 185.0),
        (345.0, 750.0),
        (945.0, 685.0),
        (845.0, 655.0),
        (880.0, 660.0),
        (25.0, 230.0),
        (525.0, 1000.0),
        (580.0, 1175.0),
        (650.0, 1130.0),
        (1605.0, 620.0) ,
        (1220.0, 580.0),
        (1465.0, 200.0),
        (1530.0, 5.0),
        (845.0, 680.0),
        (725.0, 370.0),
        (145.0, 665.0),
        (415.0, 635.0),
        (510.0, 875.0) ,
        (560.0, 365.0),
        (300.0, 465.0),
        (520.0, 585.0),
        (480.0, 415.0),
        (835.0, 625.0),
        (975.0, 580.0),
        (1215.0, 245.0),
        (1320.0, 315.0),
        (1250.0, 400.0),
        (660.0, 180.0),
        (410.0, 250.0),
        (420.0, 555.0),
        (575.0, 665.0),
        (1150.0, 1160.0),
        (700.0, 580.0),
        (685.0, 595.0),
        (685.0, 610.0),
        (770.0, 610.0),
        (795.0, 645.0),
        (720.0, 635.0),
        (760.0, 650.0),
        (475.0, 960.0),
        (95.0, 260.0),
        (875.0, 920.0),
        (700.0, 500.0),
        (555.0, 815.0),
        (830.0, 485.0),
        (1170.0, 65.0),
        (830.0, 610.0),
        (605.0, 625.0),
        (595.0, 360.0),
        (1340.0, 725.0),
        (1740.0, 245.0)
    ]

    lista_arestas = []

    for i in range(len(coordenadas)):
        for j in range(i + 1, len(coordenadas)):
            x1, y1 = coordenadas[i]
            x2, y2 = coordenadas[j]

            distancia = int(math.sqrt((x1 - x2) ** 2 + (y1 - y2) ** 2))
            lista_arestas.append((i, j, distancia))

    ag(lista_arestas, 50, 7500, 0.85, 0.15)