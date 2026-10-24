import json
import random
import time

def gerar_dados_mochila(num_itens, capacidade, valor_min=1, valor_max=50, peso_min=1, peso_max=30, arquivo="dados_mochila.json", seed=None):
    """Gera itens aleatórios e salva em JSON"""
    if seed is not None:
        random.seed(seed)

    itens = []
    for i in range(num_itens):
        itens.append({
            "id": i+1,
            "valor": random.randint(valor_min, valor_max),
            "peso": random.randint(peso_min, peso_max)
        })

    dados = {"capacidade": capacidade, "itens": itens}

    with open(arquivo, "w", encoding="utf-8") as f:
        json.dump(dados, f, indent=2, ensure_ascii=False)

    return dados

def carregar_dados_mochila(arquivo="dados_mochila.json"):
    """Carrega os dados do JSON para listas de valores e pesos"""
    with open(arquivo, "r", encoding="utf-8") as f:
        dados = json.load(f)

    capacidade = dados["capacidade"]
    valores = [item["valor"] for item in dados["itens"]]
    pesos = [item["peso"] for item in dados["itens"]]

    return capacidade, valores, pesos

def medir_tempo_execucao(funcao, *args):
    inicio = time.time()
    resultado = funcao(*args)
    fim = time.time()
    return resultado, fim - inicio
