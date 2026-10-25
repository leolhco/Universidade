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