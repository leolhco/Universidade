"""
Diogo Koichi Cruz Yonemoto - 12311BCC010
Leonardo Henrique Carvalho Oliveira - 12311BCC003
"""

import xmlrpc.client

try:
    proxy = xmlrpc.client.ServerProxy("http://localhost:8000/")
except Exception as e:
    print(f"Erro de conexão: {e}")

def menu():
    while True:
        print("\n" + "-" * 20)
        print("1 - Dados do Livro")
        print("2 - Calcular Compra")
        print("0 - Sair")
        print("-" * 20)

        op = input("Escolha uma opção: ")

        try:
            match op:
                case "1":
                    a = input("Digite o nome do livro: ")
                    servidor = proxy.dados(a)
                    print("\n--- Retorno do Servidor ---")
                    print(servidor)
                
                case "2":
                    a = input("Digite o nome do livro: ")
                    b = int(input("Digite a quantidade: "))
                    servidor = proxy.compra(a, b)
                    print("\n--- Retorno do Servidor ---")
                    print(servidor)
                
                case "0":
                    print("Encerrando cliente...")
                    break
               
                case _:
                    print("Opção inválida, tente novamente.")
        
        except Exception as e:
            print(f"Erro durante a operação: {e}")

if __name__ == "__main__":
    menu()