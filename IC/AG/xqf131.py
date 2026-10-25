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
    (0, 13),
    (0, 26),
    (0, 27),
    (0, 39),
    (2, 0),
    (5, 13),
    (5, 19),
    (5, 25),
    (5, 31),
    (5, 37),
    (5, 43),
    (5, 8),
    (8, 0),
    (9, 10),
    (10, 10),
    (11, 10),
    (12, 10),
    (12, 5),
    (15, 13),
    (15, 19),
    (15, 25),
    (15, 31),
    (15, 37),
    (15, 43),
    (15, 8),
    (18, 11),
    (18, 13),
    (18, 15),
    (18, 17),
    (18, 19),
    (18, 21),
    (18, 23),
    (18, 25),
    (18, 27),
    (18, 29),
    (18, 31),
    (18, 33),
    (18, 35),
    (18, 37),
    (18, 39),
    (18, 41),
    (18, 42),
    (18, 44),
    (18, 45),
    (25, 11),
    (25, 15),
    (25, 22),
    (25, 23),
    (25, 24),
    (25, 26),
    (25, 28),
    (25, 29),
    (25, 9),
    (28, 16),
    (28, 20),
    (28, 28),
    (28, 30),
    (28, 34),
    (28, 40),
    (28, 43),
    (28, 47),
    (32, 26),
    (32, 31),
    (33, 15),
    (33, 26),
    (33, 29),
    (33, 31),
    (34, 15),
    (34, 26),
    (34, 29),
    (34, 31),
    (34, 38),
    (34, 41),
    (34, 5),
    (35, 17),
    (35, 31),
    (38, 16),
    (38, 20),
    (38, 30),
    (38, 34),
    (40, 22),
    (41, 23),
    (41, 32),
    (41, 34),
    (41, 35),
    (41, 36),
    (48, 22),
    (48, 27),
    (48, 6),
    (51, 45),
    (51, 47),
    (56, 25),
    (57, 12),
    (57, 25),
    (57, 44),
    (61, 45),
    (61, 47),
    (63, 6),
    (64, 22),
    (71, 11),
    (71, 13),
    (71, 16),
    (71, 45),
    (71, 47),
    (74, 12),
    (74, 16),
    (74, 20),
    (74, 24),
    (74, 29),
    (74, 35),
    (74, 39),
    (74, 6),
    (77, 21),
    (78, 10),
    (78, 32),
    (78, 35),
    (78, 39),
    (79, 10),
    (79, 33),
    (79, 37),
    (80, 10),
    (80, 41),
    (80, 5),
    (81, 17),
    (84, 20),
    (84, 24),
    (84, 29),
    (84, 34),
    (84, 38),
    (84, 6),
    (107, 27)
]

    lista_arestas = []

    for i in range(len(coordenadas)):
        for j in range(i + 1, len(coordenadas)):
            x1, y1 = coordenadas[i]
            x2, y2 = coordenadas[j]

            distancia = int(math.sqrt((x1 - x2) ** 2 + (y1 - y2) ** 2))
            lista_arestas.append((i, j, distancia))

    ag(lista_arestas, 50, 7500, 0.85, 0.15)