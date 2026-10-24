"""
Diogo Koichi Cruz Yonemoto - 12311BCC010
Leonardo Henrique Carvalho Oliveira - 12311BCC003
"""

import socket
import threading

host = socket.gethostname()
port = 12345

clientes = []
clientes_removidos = []

clientes_lock = threading.Lock()

def transmitir_msg(msg, fonte):
    msg = msg.encode()

    with clientes_lock:
        for cliente in clientes:
            if cliente != fonte: 
                try:
                    cliente.send(msg)
                except Exception as e:
                    print(f"Erro: {e}")
                    clientes_removidos.append(cliente)
        
        for cliente in clientes_removidos:
            clientes.remove(cliente)
        clientes_removidos.clear()


def handle_cliente(c, addr):
    print(f"Nova conexão: {addr} conectado.")
    
    with clientes_lock:
        clientes.append(c) 

    try:
        nome_data = c.recv(1024)
        if not nome_data:
            raise Exception(f"Cliente {addr} desconectado antes de enviar o nome.")
        
        nome = nome_data.decode()
        transmitir_msg(f"{nome} entrou no chat.", c)

        while True:
            data = c.recv(1024)

            if not data:
                print(f"Cliente {nome}({addr}) desconectou.")
                break

            msg_recebida = data.decode()
            msg_enviar = f"{nome}: {msg_recebida}"

            transmitir_msg(msg_enviar, c)

    except Exception as e:
        print(f"{addr} Erro: {e}")

    finally:
        with clientes_lock:
            clientes.remove(c)
        print(f"{nome}({addr}) saiu.")

        transmitir_msg(f"{nome} saiu do chat.", c)

        c.close()


def iniciar_server():
    s = socket.socket()

    s.bind((host, port))
    s.listen(5)
    print(f"Servidor iniciado em {host}:{port}")

    try:
        while True:
            c, addr = s.accept()

            thread = threading.Thread(target=handle_cliente, args=(c, addr))
            thread.daemon = True
            thread.start()
    except Exception as e:
        print(f"Erro: {e}")
    finally:
        s.close()

if __name__ == "__main__":
    iniciar_server()