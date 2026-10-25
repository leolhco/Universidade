import random
import math
import time

def two_opt(path, dist):
    melhor_rota = path.copy()
    melhorou = True

    while melhorou:
        melhorou = False

        for i in range(1, len(melhor_rota) - 2):
            for j in range(i + 1, len(melhor_rota) - 1):

                cidade_anterior = melhor_rota[i - 1]
                cidade_inicio = melhor_rota[i]

                cidade_fim = melhor_rota[j]
                cidade_seguinte = melhor_rota[j + 1]

                custo_atual = (
                    dist[cidade_anterior][cidade_inicio]
                    + dist[cidade_fim][cidade_seguinte]
                )

                novo_custo = (
                    dist[cidade_anterior][cidade_fim]
                    + dist[cidade_inicio][cidade_seguinte]
                )

                if novo_custo < custo_atual:
                    melhor_rota[i:j + 1] = reversed(
                        melhor_rota[i:j + 1]
                    )

                    melhorou = True

    return melhor_rota


def aco(
    dist,
    n_ants=20,
    n_iter=100,
    beta=5,
    rho=0.5,
    Q=100,
    r0=0.9
):
    n = len(dist)

    pheromone = [[1.0] * n for _ in range(n)]

    best_path = None
    best_cost = float("inf")

    for iteration in range(n_iter):

        solutions = []

        for _ in range(n_ants):

            start = random.randrange(n)

            path = [start]

            unvisited = set(range(n))
            unvisited.remove(start)

            while unvisited:

                current_city = path[-1]

                choices = []
                total = 0.0
                
                best_city_argmax = None
                max_value = -1.0

                for next_city in unvisited:

                    tau = pheromone[current_city][next_city]

                    distance = dist[current_city][next_city]

                    eta = (1.0 / max(distance, 1e-10)) ** beta

                    value = tau * eta

                    choices.append(
                        (next_city, value)
                    )

                    total += value

                    if value > max_value:
                        max_value = value
                        best_city_argmax = next_city

                r = random.random()

                if r <= r0:
                    selected_city = best_city_argmax
                
                else:
                    random_value = random.random() * total
                    accumulated = 0.0
                    selected_city = None

                    for city, value in choices:

                        accumulated += value

                        if accumulated >= random_value:
                            selected_city = city
                            break

                    if selected_city is None:
                        selected_city = choices[-1][0]

                path.append(selected_city)
                unvisited.remove(selected_city)

            path.append(start)

            path = two_opt(path, dist)

            cost = 0.0

            for i in range(len(path) - 1):

                city_a = path[i]
                city_b = path[i + 1]

                cost += dist[city_a][city_b]

            solutions.append((path, cost))

            if cost < best_cost:
                best_cost = cost
                best_path = path.copy()

        for i in range(n):
            for j in range(n):
                pheromone[i][j] *= 1 - rho

        for path, cost in solutions:

            delta = Q / max(cost, 1e-10)

            for i in range(len(path) - 1):

                city_a = path[i]
                city_b = path[i + 1]

                pheromone[city_a][city_b] += delta
                pheromone[city_b][city_a] += delta

        print(
            f"Iteração {iteration + 1}/{n_iter} "
            f"- melhor custo: {best_cost:.2f}"
        )

    return best_path, best_cost


def criar_matriz_distancias(coordenadas):
    n = len(coordenadas)

    distancias = [
        [0.0] * n
        for _ in range(n)
    ]

    for i in range(n):

        x1, y1 = coordenadas[i]

        for j in range(i + 1, n):

            x2, y2 = coordenadas[j]

            distancia = math.hypot(
                x2 - x1,
                y2 - y1
            )

            distancias[i][j] = distancia
            distancias[j][i] = distancia

    return distancias


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

distancias = criar_matriz_distancias(coordenadas)

inicio = time.perf_counter()

melhor_rota, melhor_custo = aco(distancias)

final = time.perf_counter()

print("\nResultado final")
print("Quantidade de cidades:", len(coordenadas))
print("Melhor custo:", melhor_custo)
print("Rota pelos índices:", melhor_rota)

tempo = final - inicio

print(f"Tempo de execução: {tempo:.2f} segundos")