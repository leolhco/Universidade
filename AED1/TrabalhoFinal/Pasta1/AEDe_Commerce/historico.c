#include "ecommerce.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Funçao para criar a pilha Historico de Compras(HC).
Pilhahistorico* criarhist() {
    Pilhahistorico* p = (Pilhahistorico*)malloc(sizeof(Pilhahistorico));
    p->topo = NULL;
    return p;
}
//Funçao que verifica se HC esta vazia.
int pilv(Pilhahistorico* p) {
    if (p == NULL) return -1;
    if (p->topo == NULL) return 0;
    else return 1;
}
//Funçao que verifica o tamanho de HC.
int tamhist(Pilhahistorico* p) {
    if (p == NULL) return -1;
    if (pilv(p) == 0) return -2;
    Nohistorico* no = p->topo;
    int cont = 0;
    while (no != NULL) {
        cont++;
        no = no->prox;
    }
    return cont;
}
//Funçao para mostrar os itens de HC.
void showhist(Pilhahistorico* p) {
    if (p == NULL) return;
    if (pilv(p) == 0) printf("Voce ainda nao confirmou nenhuma compra!\n");
    Nohistorico* no = p->topo;
    int indice = 0;
    while (no != NULL) {
        printf("Indice: %d\n", indice);
        printf("Nome: %s\n", no->mer.nome);
        printf("Descricao: %s\n", no->mer.descricao);
        printf("Categoria: %s\n", no->mer.categoria);
        printf("Preco: %.2f\n", no->mer.preco);
        printf("Avaliacao: %.2f\n", no->mer.avaliacao);
        printf("Quantidade: %d\n", no->mer.carrinho);
        printf("Vendedor: %s\n", no->mer.vendedor);
        printf("---------------------------------------------\n");
        indice++;
        no = no->prox;
    }
}
//Funçao que insere um item em HC.
int push(Pilhahistorico* p, Mercadoria cp) {
    if (p == NULL) return -1;
    Nohistorico* no = (Nohistorico*)malloc(sizeof(Nohistorico));
    no->mer = cp;
    no->prox = p->topo;
    p->topo = no;
    return 0;
}
//Funçao que retira um item de HC para utilizaçao posterior.
int pop(Pilhahistorico* p, Mercadoria* cp) {
    if (p == NULL) return -1;
    if (pilv(p) == 0) return -2;
    Nohistorico* no = p->topo;
    p->topo = no->prox;
    *cp = no->mer;
    free(no);
    return 0;
}
//Funçao que busca um item em HC.
int consultarhist(Pilhahistorico* p, Mercadoria* cp) {
    if (p == NULL) return -1;
    if (pilv(p) == 0) return -2;
    *cp = p->topo->mer;
    return 0;
}
//Funçao que exclui HC.
void destroyhist(Pilhahistorico* p) {
    if (p == NULL) return;
    while (pilv(p) != 0) remhist(p);
}
//Funçao que remove um item de HC.
int remhist(Pilhahistorico* p) {
    if (p == NULL) return -1;
    if (pilv(p) == 0) return -2;
    Nohistorico* no = p->topo;
    p->topo = no->prox;
    free(no);
    return 0;
}
