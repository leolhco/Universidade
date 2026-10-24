#ifndef ECOMMERCE_H
#define ECOMMERCE_H

#include <stdio.h>
#include <stdlib.h>


typedef struct cliente{
    char nome[30];
    char us[20];
    char senha[25];
}Cliente;

typedef struct mercadoria{
    char nome[40];
    char descricao[130];
    char categoria[40];
    float preco;
    float avaliacao;
    int estoque;
    int carrinho;
    int vendas;
    char vendedor[40];
}Mercadoria;

typedef struct vendedor {
    char nome[30];
    char senha[25];
    char tipo[15];
}Vendedor;

typedef struct categoria {
    char nome[40];
}Categoria;

//----------------------------------------- NOS

typedef struct nohistorico{
    Mercadoria mer;
    struct nohistorico* prox;
}Nohistorico;

typedef struct nousuario {
    Cliente cl;
    struct nousuario *prox;
}Nousuario;

typedef struct nocarrinho {
    Mercadoria mer;
    struct nocarrinho *prox;
}Nocarrinho;

typedef struct novendedor{
    Vendedor loja;
    struct novendedor *prox;
}Novendedor;

typedef struct noprodutos{
    Mercadoria mer;
    struct noprodutos *prox;
}Noprodutos;

typedef struct nocategoria{
    Categoria cat;
    struct nocategoria *prox;
}NoCategoria;

//----------------------------------------- Listas

typedef struct listacategorias{
    NoCategoria *inicio;
}ListaCategorias;

typedef struct listausuario {
    Nousuario *inicio;
}Listausuario;

typedef struct carrinho {
    Nocarrinho *inicio;
}Carrinho;

typedef struct listavendedor{
    Novendedor* inicio;
}Listavendedor;

typedef struct listaProdutos{
    Noprodutos *inicio;
}ListaProdutos;

//-----------------------------------------
typedef struct pilhahistorico{
    Nohistorico* topo;
}Pilhahistorico;

//Funções Carrinho
Carrinho *criarc();
int lisvc(Carrinho *c);
int tamc(Carrinho *c);
int rem(Carrinho *c);
void excluir(Carrinho *c);
void showc(Carrinho *c);
int insc(Carrinho *c,int quantidade,Mercadoria m);
int remposc(Carrinho *c,int pos);
float totalc(Carrinho *c);
int remqtdc(Carrinho *c, int qtd, int pos);
int altrecomendacao(Carrinho *c,Nousuario *user);
char *retornanomecheckout(Carrinho *c);
int retornaquantidadecheckout(Carrinho *c);
int contemitemcarrinho(Carrinho *c, Mercadoria m);

//Funções Vendedor
Listavendedor* criarv();
int lisvv(Listavendedor* v);
int tamv(Listavendedor* v);
int insfv(Listavendedor* v, Vendedor lo);
void showv(Listavendedor* v);

//Funções Usuario
Listausuario *criarlu();
int lisvu(Listausuario *lu);
int tamu(Listausuario *lu);
int insiu(Listausuario *lu,Cliente cliente);
int bususer(Listausuario *lu,char *us,char *senha,Nousuario **user);
void showu(Listausuario *lu);
int usuariosIniciais(Listausuario *lu);

//Funções Produto
ListaProdutos *criarProdutos();
int lisvp(ListaProdutos *p);
int showp(ListaProdutos *p);
int showbyname(ListaProdutos *p, char *nome);
int showbytype(ListaProdutos *p, char *categoria);
int catval(char *categoria);
int showrelated(Pilhahistorico *his);
int criarNovaMercadoria(Mercadoria novaMercadoria);
int salvarListaProdutos(ListaProdutos *p);
int contem(ListaProdutos *p, char *item);
int remestoque(ListaProdutos *p, char *it, float nota, int qtd);
int inserirProduto(ListaProdutos *p, Mercadoria me);
int buspos(ListaProdutos *p, int pos, Mercadoria *rn);
int produtosIniciais(ListaProdutos *p);
int percorretipo5(ListaProdutos *p, char *categoria,ListaProdutos *m);

//Funçoes Historico de Compras
Pilhahistorico* criarhist();
int pilv(Pilhahistorico* p);
int tamhist(Pilhahistorico* p);
void showhist(Pilhahistorico* p);
int push(Pilhahistorico* p, Mercadoria cp);
int pop(Pilhahistorico* p, Mercadoria* cp);
int consultarhist(Pilhahistorico* p, Mercadoria* cp);
void destroyhist(Pilhahistorico* p);
int remhist(Pilhahistorico *p);

//Funções Categoria
ListaProdutos *criarProdutos();
int categoriainLcategoria(char *categoria,ListaCategorias *lc);
int categoriasIniciais(ListaCategorias *lc);
void showcategorias(ListaCategorias *lc);
int insic(ListaCategorias *lc,Categoria categoria);

#endif
