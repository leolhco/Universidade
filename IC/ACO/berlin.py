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
    (1605.0, 620.0),
    (1220.0, 580.0),
    (1465.0, 200.0),
    (1530.0, 5.0),
    (845.0, 680.0),
    (725.0, 370.0),
    (145.0, 665.0),
    (415.0, 635.0),
    (510.0, 875.0),
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