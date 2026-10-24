"""
Diogo Koichi Cruz Yonemoto - 12311BCC010
Leonardo Henrique Carvalho Oliveira - 12311BCC003
"""

import socket
import threading

host = socket.gethostname()
port = 12345

def receber_mensagem(s, nome):
    while True:
        try:
            data = s.recv(1024)
            if not data:
                print("Desconectado do servidor.")
                break

            msg = data.decode()
            print(f"\r{msg}\n", end="")
            print(f"{nome}: ", end="", flush=True)
        
        except Exception as e:
            print(f"Erro: {e}")
            break

    s.close()

def iniciar_cliente():
    s = socket.socket()

    try:
        s.connect((host, port))
    except Exception as e:
        print(f"Erro ao conectar ao servidor: {e}")
        return
    
    print(f"Conectado ao servidor {host}:{port}")

    nome = input("Digite seu nome: ")
    s.send(nome.encode())

    thread = threading.Thread(target=receber_mensagem, args=(s, nome))
    thread.daemon = True
    thread.start()

    try:
        while True:
            msg = input(f"{nome}: ")

            if msg == "SAIR":
                print("Desconectando do chat...")
                break

            if msg:
                s.send(msg.encode())
    
    except Exception as e:
        print(f"Erro: {e}")
    
    finally:
        s.close()
        print("Conexão encerrada.")

if __name__ == "__main__":
    iniciar_cliente()