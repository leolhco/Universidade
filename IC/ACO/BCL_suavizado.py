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
    (0, 108),
    (0, 20),
    (0, 21),
    (0, 22),
    (0, 23),
    (0, 24),
    (0, 28),
    (0, 33),
    (0, 49),
    (0, 60),
    (0, 71),
    (0, 97),
    (2, 103),
    (2, 104),
    (2, 11),
    (2, 12),
    (2, 137),
    (2, 139),
    (2, 150),
    (2, 18),
    (2, 20),
    (2, 22),
    (2, 29),
    (2, 32),
    (2, 35),
    (2, 46),
    (2, 49),
    (2, 52),
    (2, 62),
    (2, 70),
    (2, 85),
    (2, 87),
    (2, 89),
    (2, 90),
    (2, 93),
    (3, 19),
    (3, 30),
    (3, 47),
    (3, 63),
    (5, 108),
    (5, 112),
    (5, 116),
    (5, 121),
    (5, 127),
    (5, 131),
    (5, 142),
    (5, 145),
    (5, 147),
    (5, 75),
    (5, 78),
    (5, 8),
    (5, 82),
    (8, 113),
    (9, 10),
    (9, 124),
    (9, 127),
    (9, 131),
    (10, 125),
    (10, 129),
    (10, 92),
    (11, 106),
    (11, 133),
    (11, 141),
    (11, 144),
    (11, 156),
    (11, 73),
    (11, 76),
    (11, 92),
    (12, 109),
    (12, 5),
    (14, 167),
    (15, 11),
    (15, 112),
    (15, 116),
    (15, 121),
    (15, 126),
    (15, 130),
    (15, 142),
    (15, 145),
    (15, 147),
    (15, 30),
    (15, 47),
    (15, 64),
    (15, 8),
    (17, 104),
    (17, 150),
    (17, 20),
    (17, 32),
    (17, 49),
    (17, 85),
    (17, 87),
    (17, 90),
    (18, 38),
    (18, 55),
    (18, 70),
    (25, 100),
    (25, 104),
    (25, 105),
    (25, 108),
    (25, 109),
    (25, 11),
    (25, 110),
    (25, 115),
    (25, 12),
    (25, 14),
    (25, 17),
    (25, 21),
    (25, 25),
    (25, 28),
    (25, 35),
    (25, 37),
    (25, 40),
    (25, 52),
    (25, 54),
    (25, 6),
    (25, 60),
    (25, 62),
    (25, 74),
    (25, 75),
    (25, 78),
    (25, 79),
    (25, 83),
    (25, 84),
    (25, 87),
    (25, 88),
    (25, 89),
    (25, 94),
    (25, 96),
    (25, 99),
    (26, 102),
    (26, 53),
    (26, 81),
    (28, 123),
    (28, 127),
    (28, 131),
    (28, 135),
    (28, 141),
    (28, 145),
    (28, 150),
    (28, 156),
    (28, 160),
    (28, 65),
    (28, 68),
    (28, 70),
    (31, 142),
    (32, 10),
    (32, 153),
    (32, 156),
    (32, 160),
    (33, 154),
    (33, 158),
    (34, 117),
    (34, 121),
    (34, 52),
    (34, 56),
    (34, 64),
    (34, 67),
    (35, 128),
    (35, 132),
    (38, 11),
    (38, 131),
    (38, 135),
    (38, 141),
    (38, 145),
    (38, 150),
    (38, 155),
    (38, 159),
    (38, 24),
    (38, 36),
    (38, 53),
    (38, 65),
    (38, 68),
    (38, 70),
    (40, 105),
    (40, 108),
    (40, 115),
    (40, 14),
    (40, 25),
    (40, 37),
    (40, 54),
    (40, 6),
    (40, 75),
    (40, 78),
    (40, 84),
    (40, 87),
    (40, 94),
    (40, 96),
    (40, 99),
    (41, 103),
    (41, 109),
    (41, 43),
    (41, 82),
    (41, 88),
    (42, 167),
    (48, 10),
    (48, 105),
    (48, 106),
    (48, 107),
    (48, 108),
    (48, 132),
    (48, 133),
    (48, 137),
    (48, 138),
    (48, 141),
    (48, 142),
    (48, 143),
    (48, 148),
    (48, 150),
    (48, 153),
    (48, 17),
    (48, 18),
    (48, 22),
    (48, 23),
    (48, 26),
    (48, 27),
    (48, 28),
    (48, 33),
    (48, 35),
    (48, 38),
    (48, 39),
    (48, 43),
    (48, 44),
    (48, 47),
    (48, 48),
    (48, 49),
    (48, 54),
    (48, 56),
    (48, 79),
    (48, 80),
    (48, 90),
    (48, 91),
    (48, 93),
    (49, 135),
    (49, 20),
    (49, 41),
    (49, 94),
    (51, 7),
    (54, 0),
    (54, 167),
    (55, 124),
    (56, 152),
    (56, 9),
    (57, 124),
    (57, 152),
    (57, 5),
    (57, 58),
    (57, 9),
    (62, 10),
    (63, 105),
    (63, 107),
    (63, 132),
    (63, 138),
    (63, 141),
    (63, 148),
    (63, 150),
    (63, 17),
    (63, 23),
    (63, 26),
    (63, 33),
    (63, 35),
    (63, 38),
    (63, 44),
    (63, 47),
    (63, 54),
    (63, 56),
    (63, 79),
    (64, 108),
    (64, 136),
    (64, 142),
    (64, 21),
    (64, 27),
    (64, 42),
    (64, 48),
    (64, 78),
    (64, 89),
    (64, 95),
    (70, 167),
    (71, 101),
    (71, 103),
    (71, 126),
    (71, 127),
    (71, 141),
    (71, 157),
    (71, 25),
    (71, 28),
    (71, 29),
    (71, 35),
    (71, 37),
    (71, 39),
    (71, 40),
    (71, 64),
    (71, 65),
    (71, 69),
    (71, 70),
    (71, 73),
    (71, 74),
    (71, 75),
    (71, 80),
    (71, 82),
    (71, 85),
    (71, 86),
    (71, 9),
    (71, 90),
    (71, 91),
    (71, 94),
    (71, 95),
    (71, 96),
    (72, 67),
    (72, 88),
    (74, 107),
    (74, 111),
    (74, 115),
    (74, 119),
    (74, 125),
    (74, 131),
    (74, 133),
    (74, 136),
    (74, 138),
    (74, 162),
    (74, 45),
    (74, 50),
    (74, 56),
    (74, 6),
    (74, 60),
    (77, 42),
    (78, 53),
    (78, 56),
    (78, 60),
    (79, 54),
    (79, 58),
    (80, 105),
    (80, 129),
    (80, 132),
    (80, 135),
    (80, 147),
    (80, 15),
    (80, 160),
    (80, 31),
    (80, 5),
    (81, 112),
    (81, 116),
    (84, 115),
    (84, 119),
    (84, 125),
    (84, 133),
    (84, 136),
    (84, 138),
    (84, 45),
    (84, 50),
    (84, 55),
    (84, 59),
    (84, 6),
    (86, 101),
    (86, 103),
    (86, 127),
    (86, 141),
    (86, 29),
    (86, 40),
    (86, 64),
    (86, 70),
    (86, 73),
    (86, 80),
    (86, 82),
    (86, 85),
    (86, 9),
    (86, 91),
    (86, 94),
    (87, 157),
    (87, 25),
    (87, 68),
    (87, 74),
    (87, 89),
    (87, 95),
    (99, 102),
    (99, 104),
    (99, 17),
    (99, 34),
    (99, 51),
    (99, 68),
    (99, 85),
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