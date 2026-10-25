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
    alpha=1,
    beta=5,
    rho=0.5,
    Q=100
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

                probabilities = []
                total = 0.0

                for next_city in unvisited:

                    tau = (
                        pheromone[current_city][next_city]
                        ** alpha
                    )

                    distance = dist[current_city][next_city]

                    eta = (
                        1.0 / max(distance, 1e-10)
                    ) ** beta

                    probability = tau * eta

                    probabilities.append(
                        (next_city, probability)
                    )

                    total += probability

                random_value = random.random() * total
                accumulated = 0.0
                selected_city = None

                for city, probability in probabilities:

                    accumulated += probability

                    if accumulated >= random_value:
                        selected_city = city
                        break

                if selected_city is None:
                    selected_city = probabilities[-1][0]

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
    (2, 11),
    (2, 14),
    (2, 16),
    (2, 17),
    (2, 18),
    (2, 20),
    (2, 22),
    (2, 23),
    (2, 24),
    (2, 9),
    (5, 29),
    (5, 33),
    (9, 16),
    (9, 22),
    (9, 26),
    (9, 29),
    (9, 33),
    (10, 27),
    (10, 31),
    (11, 15),
    (11, 21),
    (11, 5),
    (15, 18),
    (15, 24),
    (15, 28),
    (15, 32),
    (25, 10),
    (25, 12),
    (25, 13),
    (25, 14),
    (25, 20),
    (25, 22),
    (25, 23),
    (25, 24),
    (25, 31),
    (28, 18),
    (28, 8),
    (32, 12),
    (32, 22),
    (34, 11),
    (34, 16),
    (34, 21),
    (35, 5),
    (38, 14),
    (38, 24),
    (38, 8),
    (41, 31),
    (48, 10),
    (48, 12),
    (48, 13),
    (48, 14),
    (48, 16),
    (48, 18),
    (48, 19),
    (48, 20),
    (48, 6),
    (51, 25),
    (51, 27),
    (51, 30),
    (51, 32),
    (55, 12),
    (55, 18),
    (57, 11),
    (57, 17),
    (57, 26),
    (57, 29),
    (58, 22),
    (61, 14),
    (61, 20),
    (61, 25),
    (61, 27),
    (61, 30),
    (61, 32),
    (63, 6),
    (71, 10),
    (71, 12),
    (71, 13),
    (71, 14),
    (71, 16),
    (71, 18),
    (71, 19),
    (71, 20),
    (71, 23),
    (71, 30),
    (74, 7),
    (78, 12),
    (78, 18),
    (80, 11),
    (80, 17),
    (80, 5),
    (84, 14),
    (84, 20),
    (86, 23),
    (87, 30),
    (89, 39),
    (94, 10),
    (94, 12),
    (94, 13),
    (94, 14),
    (94, 16),
    (94, 18),
    (94, 20),
    (94, 26),
    (94, 28),
    (97, 17),
    (97, 19),
    (97, 21),
    (97, 31),
    (97, 6),
    (97, 8),
    (101, 12),
    (102, 16),
    (102, 18),
    (102, 20),
    (103, 11),
    (103, 16),
    (103, 18),
    (103, 20),
    (103, 22),
    (103, 30),
    (103, 5),
    (107, 14),
    (107, 17),
    (107, 19),
    (107, 21),
    (107, 31),
    (107, 6),
    (107, 8),
    (117, 10),
    (117, 12),
    (117, 13),
    (117, 14),
    (120, 20),
    (120, 27),
    (120, 30),
    (120, 34),
    (120, 8),
    (123, 16),
    (123, 22),
    (124, 12),
    (124, 16),
    (124, 22),
    (125, 16),
    (125, 22),
    (126, 11),
    (126, 16),
    (126, 23),
    (126, 25),
    (126, 28),
    (127, 16),
    (127, 5),
    (130, 14),
    (130, 8),
    (133, 17),
    (133, 18),
    (133, 20),
    (133, 21),
    (133, 22),
    (140, 10),
    (140, 14),
    (140, 16),
    (140, 17),
    (140, 18),
    (140, 20),
    (140, 22),
    (140, 24),
    (143, 21),
    (143, 24),
    (145, 0),
    (146, 0),
    (147, 0),
    (147, 16),
    (147, 22),
    (148, 0),
    (148, 20),
    (148, 22),
    (149, 0),
    (149, 15),
    (149, 20),
    (149, 22),
    (149, 29),
    (150, 0),
    (151, 0),
    (152, 0),
    (153, 0),
    (153, 18),
    (153, 21),
    (154, 0),
    (156, 10),
    (163, 10),
    (163, 12),
    (163, 13),
    (163, 14),
    (163, 20),
    (163, 22),
    (163, 31),
    (163, 33),
    (163, 6),
    (166, 17),
    (166, 21),
    (166, 23),
    (166, 26),
    (170, 12),
    (171, 20),
    (171, 22),
    (172, 11),
    (172, 16),
    (172, 20),
    (172, 22),
    (172, 24),
    (172, 27),
    (176, 14),
    (176, 17),
    (176, 21),
    (176, 23),
    (178, 6),
    (186, 10),
    (186, 12),
    (186, 13),
    (186, 14),
    (186, 17),
    (186, 22),
    (186, 23),
    (186, 24),
    (186, 25),
    (186, 6),
    (189, 20),
    (189, 28),
    (189, 31),
    (189, 33),
    (192, 16),
    (193, 12),
    (193, 16),
    (194, 16),
    (195, 11),
    (195, 16),
    (195, 27),
    (195, 30),
    (196, 16),
    (199, 14),
    (199, 28),
    (199, 31),
    (199, 33),
    (201, 22),
    (201, 23),
    (201, 24),
    (201, 25),
    (201, 6),
    (202, 18),
    (202, 19),
    (209, 10),
    (209, 12),
    (209, 14),
    (209, 16),
    (209, 18),
    (209, 20),
    (209, 22),
    (212, 11),
    (212, 13),
    (212, 15),
    (212, 17),
    (212, 19),
    (212, 22),
    (212, 25),
    (212, 28),
    (212, 32),
    (212, 8),
    (216, 20),
    (217, 10),
    (217, 12),
    (217, 14),
    (217, 16),
    (217, 18),
    (217, 20),
    (218, 10),
    (218, 12),
    (218, 14),
    (218, 16),
    (218, 18),
    (218, 20),
    (218, 23),
    (218, 26),
    (219, 5),
    (222, 11),
    (222, 13),
    (222, 15),
    (222, 17),
    (222, 19),
    (222, 8),
    (232, 12),
    (232, 13),
    (232, 14),
    (232, 15),
    (232, 17),
    (232, 9),
    (235, 18),
    (235, 23),
    (235, 30),
    (235, 34),
    (235, 6),
    (238, 19),
    (238, 25),
    (239, 19),
    (239, 25),
    (240, 17),
    (240, 19),
    (240, 25),
    (241, 17),
    (241, 19),
    (241, 26),
    (241, 28),
    (241, 5),
    (242, 19),
    (242, 31),
    (245, 18),
    (245, 34),
    (245, 6),
    (247, 12),
    (247, 13),
    (247, 14),
    (247, 15),
    (247, 9),
    (248, 20),
    (248, 21),
    (248, 23),
    (248, 24),
    (248, 25),
    (255, 10),
    (255, 12),
    (255, 13),
    (255, 14),
    (255, 20),
    (255, 22),
    (255, 23),
    (255, 24),
    (255, 30),
    (255, 32),
    (255, 6),
    (258, 17),
    (262, 12),
    (262, 22),
    (264, 11),
    (264, 16),
    (264, 21),
    (264, 26),
    (268, 14),
    (268, 17),
    (268, 24),
    (270, 6),
    (278, 14),
    (278, 16),
    (278, 17),
    (278, 18),
    (278, 28),
    (278, 31),
    (281, 12),
    (281, 22),
    (281, 26),
    (281, 29),
    (281, 8),
    (285, 12),
    (285, 16),
    (285, 5),
    (285, 8),
    (286, 10),
    (286, 28),
    (286, 6),
    (287, 15),
    (287, 20),
    (287, 28),
    (288, 23),
    (291, 11),
    (291, 18),
    (291, 26),
    (291, 29),
    (291, 7),
    (293, 31),
    (299, 20),
    (299, 31),
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