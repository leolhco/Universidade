"""
Diogo Koichi Cruz Yonemoto - 12311BCC010
Leonardo Henrique Carvalho Oliveira - 12311BCC003
"""

from xmlrpc.server import SimpleXMLRPCServer

server = SimpleXMLRPCServer(("localhost", 8000))
print("Servidor RPC iniciado na porta 8000...")

acervo = [
    {
        "isbn": "9789896717926",
        "nome": "O Menino Maluquinho", 
        "autor": "Ziraldo", 
        "editora": "Melhoramentos",
        "categoria": "Comedia Infanto Juvenil", 
        "quantidade": 100, 
        "valor": 60.00
    },
    {
        "isbn": "9788599296578",
        "nome": "O Guia do Mochileiro Das Galáxias", 
        "autor": "Douglas Adams", 
        "editora": "Arqueiro",
        "categoria": "Ficçao Cientifica Infanto Juvenil", 
        "quantidade": 100, 
        "valor": 70.00
    }, 
    {
        "isbn": "9788576831303",
        "nome": "Diário de um Banana", 
        "autor": "Jeff Kinney", 
        "editora": "VR Editora",
        "categoria": "Comedia Infanto Juvenil", 
        "quantidade": 100, 
        "valor": 80.00
    }
]

def buscar(a):
    for livro in acervo:
        if livro["nome"].lower() == a.lower():
            return livro 
    return None 

def dados(a):
    livro = buscar(a) 

    if not livro:
        return f"Erro: O livro '{a}' não existe na base de dados."
        
    informacoes = (f"ISBN: {livro['isbn']}\n"
                   f"Nome: {livro['nome']}\n"
                   f"Autor: {livro['autor']}\n"
                   f"Categoria: {livro['categoria']}\n"
                   f"Editora: {livro['editora']}\n"
                   f"Valor: {livro['valor']}\n"
                   f"Quantidade em estoque: {livro['quantidade']}")
    return informacoes

def compra(a, b):
    livro = buscar(a) 

    if not livro:
        return f"Erro: O livro '{a}' não existe na base de dados."
    
    if b > livro["quantidade"]:
        return "Erro: Quantidade indisponível no estoque."
    
    venda = livro["valor"] * b
    
    return f"O valor da venda de {b} unidades de '{a}' é: R$ {venda:.2f}"

server.register_function(dados, "dados")
server.register_function(compra, "compra")

server.serve_forever()