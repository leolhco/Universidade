# Relatório Técnico: Implementação e Testes de Rainbow Tables com Diceware

## 1. Objetivo e Metodologia dos Testes

Este trabalho avalia na prática o funcionamento de uma Rainbow Table aplicada na quebra de senhas curtas baseadas na lista oficial do Diceware. O experimento explora diferentes configurações de altura e largura da tabela para medir a eficácia na descoberta de senhas e a eficiência no uso de memória e tempo de processamento.

Os testes foram executados localmente em um computador equipado com processador Intel Core i3 1315U de décima terceira geração com 8 threads lógicas operando até 4500 MHz e 7,5 GiB de memória RAM principal. O sistema operacional utilizado foi o Linux Kernel 6.14 com o interpretador Python 3.12.15. Toda a execução ocorreu em thread única na CPU e com as tabelas alocadas diretamente na memória RAM para medir o tempo puro de processamento sem interferência de leitura em disco.

A partir do arquivo oficial do Diceware, foram filtradas as 7776 palavras válidas. A função de hash fornecida utiliza o algoritmo SHA256 concatenando o prefixo fixo GBC083 com a senha em formato UTF8, sendo validada previamente com a entrada 1234 para confirmar o hash hexadecimal de referência. Para evitar que cadeias distintas se fundam ao colidirem em colunas diferentes, foram implementadas várias funções de redução distintas chamadas de cores. Cada coluna da tabela aplica uma operação lógica XOR entre os primeiros 8 bytes do hash e um múltiplo do índice da coluna antes de mapear o valor para uma palavra da lista via operador módulo.

A bateria de experimentos foi dividida em dois cenários usando semente aleatória fixa igual a 42 e um conjunto de 500 senhas sorteadas aleatoriamente para cada bateria. O primeiro cenário utiliza senhas formadas por 1 palavra dentre as 7776 disponíveis. O segundo cenário utiliza senhas formadas pela concatenação de 2 palavras limitadas às 300 primeiras da lista, totalizando 90000 combinações possíveis. O tempo foi medido com a função `time.perf_counter` e o consumo de memória foi calculado somando o espaço ocupado pelo dicionário do Python e pelas strings armazenadas.

---

## 2. Implementação

```python
import hashlib
import os
import platform
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


def myHashHex(s: str) -> str:
    hash_object = hashlib.sha256()
    hash_object.update(b"GBC083")
    hash_object.update(s.encode("utf-8"))
    return hash_object.hexdigest()


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

    bars1 = axes[0, 0].bar(x, df["Eficácia (%)"], color="#2b5c8f", width=0.6)
    axes[0, 0].set_title("Eficácia de Quebra de Senhas (%)")
    axes[0, 0].set_ylabel("Taxa de Sucesso (%)")
    axes[0, 0].set_xticks(x)
    axes[0, 0].set_xticklabels(labels)
    axes[0, 0].set_ylim(0, 105)
    axes[0, 0].grid(axis="y", linestyle="--", alpha=0.5)
    axes[0, 0].bar_label(bars1, fmt="%.1f%%", padding=3)

    ax2 = axes[0, 1]
    ax2_twin = ax2.twinx()
    w = 0.35
    ax2.bar(
        x - w / 2,
        df["Memória (KB)"],
        width=w,
        color="#3690c0",
        label="Memória (KB)",
    )
    ax2_twin.bar(
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

```

---

## 3. Resultados e Análise: Cenário de 1 Palavra

Os resultados obtidos para o espaço de 7776 senhas de 1 palavra estão resumidos na Tabela 1 e representados nos quatro gráficos da figura do primeiro cenário.

**Tabela 1: Resultados experimentais para senhas de 1 palavra em 500 buscas**

| Altura m | Largura k | Linhas Únicas | Memória em KB | Geração em s | Eficácia | Busca em ms | Falsos Alarmes |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 100 | 10 | 96 | 11,7 | 0,003 | 12,2% | 0,078 | 362 |
| 500 | 10 | 364 | 44,9 | 0,004 | 42,2% | 0,033 | 871 |
| 1500 | 10 | 754 | 92,0 | 0,011 | 66,2% | 0,032 | 1258 |
| 100 | 50 | 68 | 7,6 | 0,003 | 33,4% | 0,781 | 3665 |
| 500 | 50 | 194 | 23,6 | 0,018 | 72,8% | 0,598 | 5840 |
| 1500 | 50 | 265 | 29,9 | 0,053 | 81,8% | 0,522 | 5752 |
| 500 | 150 | 91 | 11,3 | 0,052 | 84,0% | 4,539 | 17147 |

Observando o gráfico de eficácia no canto superior esquerdo do painel, vemos que o aumento tanto da altura quanto da largura amplia a capacidade de quebra das senhas testadas, subindo de 12,2% na menor tabela até atingir 84,0% na configuração de altura 500 e largura 150. Porém, o gráfico inferior esquerdo, que compara a altura inicial com as linhas únicas salvas, explica por que o crescimento da eficácia desacelera nas tabelas maiores. Quando duas linhas reduzem para a mesma palavra na mesma coluna, elas seguem o mesmo caminho até o final e geram chaves repetidas no dicionário. Como o universo de 7776 palavras é pequeno, na tabela de altura 1500 e largura 50 restaram apenas 265 linhas únicas das 1500 geradas, e na tabela de largura 150 sobreviveram apenas 91 linhas de 500 criadas.

Essa escolha de dimensões reflete diretamente nas métricas de eficiência exibidas nos dois gráficos da direita. O gráfico superior direito compara a memória ocupada em azul com o tempo médio de busca em vermelho, evidenciando a troca entre armazenamento e processamento. Comparando duas configurações que realizam 5000 operações teóricas, a tabela de altura 500 e largura 10 ocupa 44,9 KB de memória e faz buscas quase instantâneas em 0,033 ms. Já a tabela de altura 100 e largura 50 consome apenas 7,6 KB de memória, mas eleva o tempo de busca para 0,781 ms. A razão dessa lentidão na busca é mostrada no gráfico inferior direito de falsos alarmes. Conforme a largura passa de 10 para 50 e depois para 150 colunas, a quantidade de vezes em que o algoritmo reconstrói uma linha inteira devido a uma colisão falsa salta de 871 para 5840 e chega a 17147 ocorrências, fazendo o tempo médio de busca atingir 4,539 ms.

---

## 4. Resultados e Análise: Cenário de 2 Palavras

No segundo cenário, com espaço total de 90000 senhas possíveis, o comportamento das seis configurações testadas encontra se na Tabela 2 e nos gráficos da segunda figura.

**Tabela 2: Resultados experimentais para senhas de 2 palavras em 500 buscas**

| Altura m | Largura k | Linhas Únicas | Memória em KB | Geração em s | Eficácia | Busca em ms | Falsos Alarmes |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 500 | 20 | 479 | 59,6 | 0,008 | 9,6% | 0,159 | 527 |
| 2000 | 20 | 1606 | 208,0 | 0,031 | 33,0% | 0,144 | 1445 |
| 5000 | 20 | 3162 | 410,8 | 0,078 | 53,6% | 0,133 | 2053 |
| 500 | 100 | 394 | 51,3 | 0,039 | 32,0% | 3,532 | 7640 |
| 2000 | 100 | 942 | 117,7 | 0,153 | 68,8% | 2,708 | 10761 |
| 5000 | 100 | 1342 | 156,8 | 0,384 | 76,4% | 2,446 | 11723 |

Pelo gráfico superior esquerdo de eficácia do segundo painel, fica claro que o espaço maior exige estruturas mais robustas, fazendo com que 500 linhas de largura 20 quebrem apenas 9,6% das senhas, enquanto a combinação de altura 5000 e largura 100 alcança 76,4% de sucesso. Nota se também que a tabela de altura 2000 com largura 20 atinge 33,0% de eficácia, empatando tecnicamente com a tabela de altura 500 com largura 100, que registra 32,0%. No gráfico inferior esquerdo de fusão de cadeias, observa se que um espaço de 90000 senhas preserva melhor as linhas únicas quando a largura é 20, salvando 3162 cadeias das 5000 geradas. Porém, ao alongar as cadeias para largura 100, as colisões na mesma coluna voltam a crescer e reduzem as 5000 linhas iniciais para 1342 linhas únicas.

No gráfico superior direito de memória versus tempo de busca, vemos uma separação nítida entre os dois grupos de largura testados. As três primeiras tabelas de largura 20 apresentam barras azuis de memória crescentes que chegam a 410,8 KB, mantendo barras vermelhas de tempo de busca mínimas ao redor de 0,14 ms. Já nas três tabelas de largura 100, o gasto de memória cai para o intervalo entre 51,3 KB e 156,8 KB, mas as barras vermelhas de tempo de busca sobem para a faixa de 2,4 ms a 3,5 ms. Isso é reflexo direto do gráfico inferior direito, onde os falsos alarmes passam de no máximo 2053 nas tabelas curtas para até 11723 nas tabelas longas. Um detalhe importante nas barras vermelhas de largura 100 é que o tempo médio de busca cai de 3,532 ms para 2,446 ms conforme a altura sobe de 500 para 5000. Quando uma senha não existe na tabela, o algoritmo precisa percorrer todas as 100 colunas até o fim, mas em uma tabela com alta taxa de acerto a busca encontra a senha logo nas primeiras colunas testadas e encerra o processamento mais cedo.

---

## 5. Conclusão

Os experimentos demonstram como as dimensões da Rainbow Table controlam diretamente o consumo de recursos de hardware. Tabelas altas com poucas colunas demandam mais memória RAM, mas oferecem tempos de busca quase imediatos e poucos falsos alarmes. Em contrapartida, tabelas com muitas colunas economizam bastante memória para atingir a mesma eficácia, mas transferem um custo elevado para o processador devido ao grande volume de reconstruções em falsos alarmes. Por fim, o uso do prefixo fixo GBC083 na função de hash ilustra como a adoção de um salt único para cada usuário em sistemas reais protege contra Rainbow Tables, pois obrigaria o atacante a gerar uma tabela inteira do zero para cada senha.
