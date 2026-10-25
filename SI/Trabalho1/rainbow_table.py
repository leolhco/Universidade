import hashlib
import os
import random
import sys
import time
import urllib.request
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

URL_DICEWARE = "https://theworld.com/~reinhold/diceware.wordlist.asc"
ARQUIVO_CACHE = "diceware.wordlist.asc"


def myHash(s: str) -> bytes:
    hash_object = hashlib.sha256()
    hash_object.update(b"GBC083")
    hash_object.update(s.encode("utf-8"))
    return hash_object.digest()


def carregar_diceware() -> list:
    if not os.path.exists(ARQUIVO_CACHE):
        urllib.request.urlretrieve(URL_DICEWARE, ARQUIVO_CACHE)
    palavras = []
    with open(ARQUIVO_CACHE, "r", encoding="utf-8") as f:
        for linha in f:
            partes = linha.strip().split()
            if len(partes) == 2 and len(partes[0]) == 5 and partes[0].isdigit():
                palavras.append(partes[1])
    return palavras


def reduzir_1_palavra(hash_bytes: bytes, cor: int, palavras: list) -> str:
    val = int.from_bytes(hash_bytes[:8], byteorder="big")
    mistura = val ^ ((cor + 1) * 0x9E3779B97F4A7C15)
    return palavras[mistura % len(palavras)]


def reduzir_2_palavras(hash_bytes: bytes, cor: int, palavras: list) -> str:
    W = len(palavras)
    val = int.from_bytes(hash_bytes[:8], byteorder="big")
    mistura = val ^ ((cor + 1) * 0x9E3779B97F4A7C15)
    return palavras[mistura % W] + palavras[(mistura // W) % W]


def gerar_senha_aleatoria(palavras: list, num_palavras: int) -> str:
    if num_palavras == 1:
        return random.choice(palavras)
    return random.choice(palavras) + random.choice(palavras)


def gerar_rainbow_table(
    altura_m: int, largura_k: int, palavras: list, num_palavras: int
):
    func_reducao = (
        reduzir_1_palavra if num_palavras == 1 else reduzir_2_palavras
    )
    tabela = {}
    if num_palavras == 1 and altura_m <= len(palavras):
        senhas_iniciais = random.sample(palavras, altura_m)
    else:
        senhas_iniciais = [
            gerar_senha_aleatoria(palavras, num_palavras)
            for _ in range(altura_m)
        ]

    inicio_t = time.perf_counter()
    for p_inicial in senhas_iniciais:
        p_atual = p_inicial
        for cor in range(largura_k):
            p_atual = func_reducao(myHash(p_atual), cor, palavras)
        tabela[p_atual] = p_inicial
    tempo_geracao = time.perf_counter() - inicio_t
    return tabela, tempo_geracao


def quebrar_hash(
    hash_alvo: bytes,
    tabela: dict,
    largura_k: int,
    palavras: list,
    num_palavras: int,
):
    func_reducao = (
        reduzir_1_palavra if num_palavras == 1 else reduzir_2_palavras
    )
    alarmes_falsos = 0
    for cor_inicial in range(largura_k - 1, -1, -1):
        h_temp = hash_alvo
        for cor in range(cor_inicial, largura_k):
            p_fim = func_reducao(h_temp, cor, palavras)
            if cor < largura_k - 1:
                h_temp = myHash(p_fim)
        if p_fim in tabela:
            p_candidata = tabela[p_fim]
            for c in range(cor_inicial):
                p_candidata = func_reducao(myHash(p_candidata), c, palavras)
            if myHash(p_candidata) == hash_alvo:
                return p_candidata, alarmes_falsos
            else:
                alarmes_falsos += 1
    return None, alarmes_falsos


def coletar_dados_experimento(
    palavras: list, num_palavras: int, configuracoes: list, qtd_testes: int = 500
) -> pd.DataFrame:
    senhas_teste = [
        gerar_senha_aleatoria(palavras, num_palavras) for _ in range(qtd_testes)
    ]
    hashes_teste = [myHash(s) for s in senhas_teste]
    linhas_df = []

    for m, k in configuracoes:
        tabela, t_geracao = gerar_rainbow_table(m, k, palavras, num_palavras)
        linhas_unicas = len(tabela)
        memoria_kb = (
            sys.getsizeof(tabela)
            + sum(
                sys.getsizeof(k_s) + sys.getsizeof(v_s)
                for k_s, v_s in tabela.items()
            )
        ) / 1024.0

        sucessos = 0
        total_alarmes_falsos = 0
        inicio_busca = time.perf_counter()
        for h_alvo in hashes_teste:
            senha_encontrada, falsos = quebrar_hash(
                h_alvo, tabela, k, palavras, num_palavras
            )
            total_alarmes_falsos += falsos
            if senha_encontrada is not None:
                sucessos += 1
        tempo_medio_busca_ms = (
            (time.perf_counter() - inicio_busca) / qtd_testes
        ) * 1000.0
        eficacia = (sucessos / qtd_testes) * 100.0

        linhas_df.append({
            "Config": f"m={m}\nk={k}",
            "Altura (m)": m,
            "Largura (k)": k,
            "Linhas Únicas": linhas_unicas,
            "Memória (KB)": round(memoria_kb, 1),
            "T. Geração (s)": round(t_geracao, 3),
            "Eficácia (%)": round(eficacia, 1),
            "T. Busca (ms)": round(tempo_medio_busca_ms, 3),
            "Falsos Alarmes": total_alarmes_falsos,
        })

    return pd.DataFrame(linhas_df)


def plotar_painel(df: pd.DataFrame, titulo: str, arquivo_saida: str):
    fig, axes = plt.subplots(2, 2, figsize=(14, 10))
    fig.suptitle(titulo, fontsize=15, fontweight="bold")
    x = np.arange(len(df["Config"]))
    labels = df["Config"]

    # Gráfico 1: Eficácia (%)
    bars1 = axes[0, 0].bar(x, df["Eficácia (%)"], color="#2b5c8f", width=0.6)
    axes[0, 0].set_title("Eficácia de Quebra de Senhas (%)")
    axes[0, 0].set_ylabel("Taxa de Sucesso (%)")
    axes[0, 0].set_xticks(x)
    axes[0, 0].set_xticklabels(labels)
    axes[0, 0].set_ylim(0, 105)
    axes[0, 0].grid(axis="y", linestyle="--", alpha=0.5)
    axes[0, 0].bar_label(bars1, fmt="%.1f%%", padding=3)

    # Gráfico 2: Trade-off Memória (KB) vs Tempo Médio de Busca (ms)
    ax2 = axes[0, 1]
    ax2_twin = ax2.twinx()
    w = 0.35
    b_mem = ax2.bar(
        x - w / 2,
        df["Memória (KB)"],
        width=w,
        color="#3690c0",
        label="Memória (KB)",
    )
    b_tmp = ax2_twin.bar(
        x + w / 2,
        df["T. Busca (ms)"],
        width=w,
        color="#e34a33",
        label="T. Busca (ms)",
    )
    ax2.set_title("Trade-off: Memória (KB) vs. Tempo de Busca (ms)")
    ax2.set_ylabel("Memória Ocupada (KB)", color="#3690c0", fontweight="bold")
    ax2_twin.set_ylabel(
        "Tempo Médio de Busca (ms)", color="#e34a33", fontweight="bold"
    )
    ax2.set_xticks(x)
    ax2.set_xticklabels(labels)
    ax2.grid(axis="y", linestyle="--", alpha=0.5)

    # Gráfico 3: Fusão de Cadeias (Altura m vs Linhas Únicas Salvas)
    axes[1, 0].bar(
        x - w / 2,
        df["Altura (m)"],
        width=w,
        color="#a6bddb",
        label="Altura Inicial (m)",
    )
    axes[1, 0].bar(
        x + w / 2,
        df["Linhas Únicas"],
        width=w,
        color="#045a8d",
        label="Linhas Únicas (Pós-Colisão)",
    )
    axes[1, 0].set_title(
        "Efeito de Fusão de Cadeias (Altura vs. Linhas Únicas)"
    )
    axes[1, 0].set_ylabel("Quantidade de Cadeias")
    axes[1, 0].set_xticks(x)
    axes[1, 0].set_xticklabels(labels)
    axes[1, 0].legend()
    axes[1, 0].grid(axis="y", linestyle="--", alpha=0.5)

    # Gráfico 4: Falsos Alarmes em função da Largura
    bars4 = axes[1, 1].bar(x, df["Falsos Alarmes"], color="#d95f0e", width=0.6)
    axes[1, 1].set_title("Total de Falsos Alarmes (500 buscas)")
    axes[1, 1].set_ylabel("Ocorrências de Falsos Alarmes")
    axes[1, 1].set_xticks(x)
    axes[1, 1].set_xticklabels(labels)
    axes[1, 1].grid(axis="y", linestyle="--", alpha=0.5)
    axes[1, 1].bar_label(bars4, padding=3)

    plt.tight_layout(rect=[0, 0.03, 1, 0.95])
    plt.savefig(arquivo_saida, dpi=300)
    plt.close()
    print(f"[OK] Gráfico salvo em: {arquivo_saida}")


if __name__ == "__main__":
    random.seed(42)
    palavras_completas = carregar_diceware()

    configs_1 = [
        (100, 10),
        (500, 10),
        (1500, 10),
        (100, 50),
        (500, 50),
        (1500, 50),
        (500, 150),
    ]
    df_1 = coletar_dados_experimento(
        palavras_completas, 1, configs_1, qtd_testes=500
    )
    df_1.to_csv("tabela_1_palavra.csv", index=False)
    plotar_painel(
        df_1,
        "Rainbow Table - Cenário 1 Palavra (Espaço = 7.776 senhas)",
        "cenario_1_palavra.png",
    )

    configs_2 = [
        (500, 20),
        (2000, 20),
        (5000, 20),
        (500, 100),
        (2000, 100),
        (5000, 100),
    ]
    df_2 = coletar_dados_experimento(
        palavras_completas[:300], 2, configs_2, qtd_testes=500
    )
    df_2.to_csv("tabela_2_palavras.csv", index=False)
    plotar_painel(
        df_2,
        "Rainbow Table - Cenário 2 Palavras (Espaço = 90.000 senhas)",
        "cenario_2_palavras.png",
    )