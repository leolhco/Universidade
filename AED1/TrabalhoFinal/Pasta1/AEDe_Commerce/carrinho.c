#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ecommerce.h"

//Funçao para criar lista carrinho.
Carrinho *criarc(){
    Carrinho *c = (Carrinho*) malloc(sizeof(Carrinho));
    c->inicio = NULL;
    return c;
}
//Funçao que verifica se a lista esta vazia.
int lisvc(Carrinho *c) {
    if(c == NULL) return -1;
    if(c->inicio == NULL) return 0;
    else return 1;
}
//Funçao que verifica o tamanho da lista.
int tamc(Carrinho *c) {
    if(c == NULL) return -1;
    if(lisvc(c) == 0) return -2;
    Nocarrinho *no = c->inicio;
    int cont = 0;
    while(no != NULL) {
        cont++;
        no = no->prox;
    }
    return cont;
}
//Funçao que remove um item da lista,
int rem(Carrinho *c){
    if(c == NULL) return -1;
    if(lisvc(c) == 0) return -2;
    Nocarrinho *no = c->inicio;
    c->inicio = no->prox;
    free(no);
    if (c->inicio == NULL){
        c = NULL;
    }
    return 0;
}
//Funçao que exclui lista.
void excluir(Carrinho *c) {
    if(c == NULL) return;
    if(lisvc(c) == 0) return;
    while(lisvc(c) != 0) {
        rem(c);
    }
}
//Funçao que mostra os itens da lista.
void showc(Carrinho *c) {
    if(c == NULL) return;
    if(lisvc(c) == 0) return;
    Nocarrinho *no = c->inicio;
    int indice = 0;
    while(no != NULL) {
        printf("Indice: %d\n",indice);
        printf("Nome: %s\n",no->mer.nome);
        printf("Descricao: %s\n",no->mer.descricao);
        printf("Categoria: %s\n",no->mer.categoria);
        printf("Preco: %.2f\n",no->mer.preco);
        printf("Avalicao: %.2f\n",no->mer.avaliacao);
        printf("Vendedor: %s\n", no->mer.vendedor);
        printf("Quantidade carrinho: %d\n",no->mer.carrinho);
        printf("---------------------------------------------\n");
        no = no->prox;
        indice++;
    }
}
//Funçao que insere item na lista.
int insc(Carrinho *c,int quantidade,Mercadoria m) {
    if(c == NULL) return -1;
    if(quantidade <= 0 ) return -2;
    if(quantidade <= m.estoque) {
            Nocarrinho *no = (Nocarrinho*) malloc (sizeof(Nocarrinho));
            no->mer = m;
            no->mer.carrinho = quantidade;
            no->prox = c->inicio;
            c->inicio = no;
        }else
            printf("Quantidade invalida.\n");

    return 0;
}

//Funçao que remove um item em uma dada posiçao da lista.
int remposc(Carrinho *c,int pos){
    if (c == NULL) return -1;
    if (lisvc(c) == 0) return -2;
    if(pos < 0 || pos >= tamc(c)) return -3;

    Nocarrinho *no = c->inicio;
    Nocarrinho *aux = NULL;
    int p = 0;
    while(p < pos){
        aux = no;
        no = no->prox;
        p++;
    }

    if(aux == NULL)
        c->inicio = no->prox;
    else
        aux->prox = no->prox;

    free(no);

    return 0;
}

//Funçao que calcula o total que o cliente tera que pagar.
float totalc(Carrinho *c){
    if (c == NULL) return -1;

    Nocarrinho *no = c->inicio;
    float total = 0;

    while(no != NULL){
        total += (no->mer.preco * no->mer.carrinho);
        no = no->prox;
    }

    return total;
}

//Funçao que remove uma quantidade de um item da lista.
int remqtdc(Carrinho *c, int qtd, int pos){
    if (c == NULL) return -1;

    Nocarrinho *no = c->inicio;
    int p = 0;

    while (no->prox != NULL && p < pos){
        no = no->prox;
        p++;
    }

    if ((no->mer.carrinho - qtd) > 0)
        no->mer.carrinho = no->mer.carrinho - qtd;
    else
        remposc(c, p);

    return 0;
}


//Funçao que retorna o nome do produto.
char *retornafinalizarcompra(Carrinho *c){
    if (c == NULL) return "Ponteiro para lista na existe";
    if (lisvc(c) == 0) return "Carrinho vazio";

    Nocarrinho *no = c->inicio;

    return no->mer.nome;
}

//Funçao que retorna a quantidade do produto.
int retornaqtdcompra(Carrinho *c){
    if (c == NULL) return -2;
    if (lisvc(c) == 0) return -1;

    Nocarrinho *no = c->inicio;

    return no->mer.carrinho;
}
//Funçao que verifica se um item existe no carrinho.
int contemitemcarrinho(Carrinho *c, Mercadoria m){
    if (c == NULL) return -2;
    if (lisvc(c) == 0) return -3;

    Nocarrinho *no = c->inicio;
    int contador = 0;
    while (no != NULL){
        if(strcmp(no->mer.nome,m.nome) == 0){
            return contador;
        } else {
            contador++;
            no = no->prox;
        }
    }
    return -1;
}
