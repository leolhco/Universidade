from mochila import mochila, mochila_memorizacao, mochila_PD
from gerador_dados import gerar_dados_mochila, carregar_dados_mochila, medir_tempo_execucao

def rodar_teste(arquivo):
    capacidade, valores, pesos = carregar_dados_mochila(arquivo)

    print("\n==========================================================")
    print(f" Teste com {len(valores)} itens | Capacidade: {capacidade}")
    print("===========================================================")

    funcoes = [mochila, mochila_memorizacao, mochila_PD]

    for func in funcoes:
        resultado, tempo = medir_tempo_execucao(func, capacidade, valores, pesos)
        print(f"{func.__name__:>20} -> Resultado: {resultado:3d} | Tempo: {tempo:.6f}s")

if __name__ == "__main__":
    #Alterar a quantidade de itens e a capacidade
    gerar_dados_mochila(num_itens=25, capacidade=150, arquivo="dados_mochila.json", seed=42)
    rodar_teste("dados_mochila.json")
