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
    (0, 16),
    (0, 19),
    (0, 22),
    (0, 25),
    (0, 28),
    (0, 31),
    (0, 34),
    (0, 37),
    (0, 4),
    (0, 40),
    (0, 7),
    (2, 10),
    (2, 12),
    (2, 14),
    (2, 16),
    (2, 21),
    (2, 23),
    (2, 25),
    (2, 27),
    (2, 34),
    (5, 20),
    (5, 8),
    (6, 42),
    (8, 17),
    (8, 28),
    (9, 10),
    (9, 21),
    (11, 18),
    (12, 17),
    (12, 28),
    (12, 5),
    (15, 17),
    (15, 28),
    (15, 8),
    (18, 34),
    (25, 10),
    (25, 12),
    (25, 14),
    (25, 16),
    (25, 25),
    (25, 27),
    (25, 29),
    (25, 31),
    (25, 6),
    (28, 19),
    (28, 21),
    (28, 34),
    (31, 17),
    (31, 32),
    (32, 10),
    (32, 25),
    (34, 18),
    (34, 33),
    (35, 17),
    (35, 32),
    (38, 17),
    (38, 19),
    (38, 21),
    (38, 32),
    (38, 34),
    (40, 6),
    (48, 10),
    (48, 12),
    (48, 13),
    (48, 14),
    (48, 21),
    (48, 23),
    (48, 24),
    (48, 25),
    (48, 28),
    (48, 35),
    (51, 18),
    (51, 8),
    (55, 12),
    (55, 23),
    (57, 11),
    (57, 16),
    (57, 22),
    (58, 5),
    (61, 14),
    (61, 25),
    (61, 8),
    (63, 28),
    (64, 35),
    (71, 15),
    (71, 17),
    (71, 18),
    (71, 19),
    (71, 21),
    (71, 23),
    (71, 24),
    (71, 25),
    (71, 34),
    (71, 36),
    (74, 11),
    (74, 29),
    (74, 6),
    (74, 9),
    (78, 17),
    (78, 21),
    (80, 16),
    (80, 23),
    (80, 27),
    (80, 30),
    (80, 5),
    (80, 8),
    (84, 11),
    (84, 19),
    (84, 6),
    (84, 9),
    (93, 0),
    (94, 10),
    (94, 14),
    (94, 16),
    (94, 18),
    (94, 20),
    (94, 23),
    (94, 25),
    (94, 27),
    (94, 29),
    (94, 31),
    (97, 34),
    (97, 36),
    (100, 21),
    (100, 32),
    (101, 14),
    (101, 25),
    (103, 33),
    (104, 21),
    (104, 32),
    (107, 21),
    (107, 32),
    (107, 34),
    (107, 36),
    (109, 23),
    (110, 10),
    (117, 10),
    (117, 12),
    (117, 13),
    (117, 14),
    (117, 33),
    (117, 35),
    (120, 19),
    (120, 23),
    (120, 27),
    (120, 6),
    (124, 12),
    (124, 20),
    (124, 23),
    (124, 27),
    (125, 21),
    (125, 25),
    (126, 11),
    (126, 29),
    (126, 5),
    (127, 16),
    (130, 14),
    (130, 19),
    (130, 22),
    (130, 26),
    (130, 6),
    (140, 20),
    (140, 22),
    (140, 24),
    (140, 26),
    (140, 28),
    (140, 6),
    (143, 10),
    (143, 13),
    (143, 17),
    (143, 21),
    (143, 31),
    (143, 34),
    (143, 36),
    (146, 29),
    (147, 22),
    (148, 20),
    (149, 11),
    (149, 20),
    (149, 30),
    (149, 33),
    (149, 42),
    (149, 8),
    (150, 29),
    (153, 21),
    (153, 29),
    (153, 31),
    (153, 34),
    (153, 36),
    (155, 6),
    (163, 10),
    (163, 12),
    (163, 14),
    (163, 16),
    (163, 18),
    (163, 20),
    (163, 22),
    (163, 24),
    (166, 28),
    (166, 31),
    (166, 35),
    (166, 8),
    (169, 17),
    (169, 25),
    (170, 10),
    (170, 18),
    (172, 26),
    (172, 29),
    (173, 17),
    (173, 25),
    (173, 5),
    (176, 17),
    (176, 25),
    (176, 8),
    (186, 10),
    (186, 14),
    (186, 16),
    (186, 18),
    (186, 20),
    (186, 26),
    (189, 23),
    (195, 14),
    (195, 21),
    (195, 22),
    (195, 32),
    (199, 21),
    (199, 23),
    (201, 26),
    (202, 10),
    (209, 10),
    (209, 11),
    (209, 12),
    (209, 15),
    (209, 17),
    (209, 19),
    (209, 21),
    (209, 23),
    (209, 25),
    (209, 27),
    (209, 29),
    (209, 32),
    (209, 34),
    (209, 37),
    (212, 16),
    (212, 20),
    (212, 24),
    (212, 28),
    (212, 33),
    (212, 37),
    (212, 8),
    (216, 14),
    (216, 31),
    (217, 14),
    (217, 31),
    (218, 14),
    (218, 31),
    (219, 5),
    (222, 8),
    (224, 11),
    (224, 12),
    (232, 13),
    (232, 21),
    (232, 23),
    (232, 25),
    (232, 27),
    (232, 29),
    (232, 31),
    (232, 6),
    (235, 18),
    (235, 22),
    (235, 26),
    (235, 30),
    (235, 34),
    (235, 36),
    (239, 20),
    (240, 20),
    (241, 16),
    (241, 20),
    (241, 33),
    (245, 34),
    (245, 36),
    (247, 6),
    (248, 13),
    (255, 10),
    (255, 12),
    (255, 13),
    (255, 15),
    (255, 31),
    (255, 32),
    (255, 34),
    (255, 36),
    (258, 12),
    (258, 14),
    (258, 16),
    (258, 20),
    (258, 24),
    (258, 28),
    (258, 6),
    (262, 10),
    (262, 21),
    (262, 24),
    (262, 28),
    (263, 10),
    (263, 13),
    (263, 15),
    (263, 22),
    (263, 26),
    (264, 10),
    (264, 13),
    (264, 15),
    (264, 30),
    (264, 5),
    (265, 17),
    (268, 14),
    (268, 16),
    (268, 20),
    (268, 23),
    (268, 27),
    (268, 6),
    (278, 10),
    (278, 12),
    (278, 13),
    (278, 19),
    (278, 35),
    (281, 12),
    (281, 14),
    (281, 16),
    (281, 7),
    (285, 10),
    (286, 10),
    (286, 13),
    (287, 10),
    (287, 13),
    (287, 15),
    (287, 25),
    (287, 5),
    (291, 14),
    (291, 16),
    (293, 19),
    (294, 35),
    (299, 16),
    (299, 21),
]

    lista_arestas = []

    for i in range(len(coordenadas)):
        for j in range(i + 1, len(coordenadas)):
            x1, y1 = coordenadas[i]
            x2, y2 = coordenadas[j]

            distancia = int(math.sqrt((x1 - x2) ** 2 + (y1 - y2) ** 2))
            lista_arestas.append((i, j, distancia))

    ag(lista_arestas, 50, 4000, 0.85, 0.15)