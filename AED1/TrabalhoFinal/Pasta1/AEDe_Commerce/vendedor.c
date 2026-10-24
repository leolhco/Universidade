#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ecommerce.h"

//Funçao que cria a lista de vendedores(LV).
Listavendedor* criarv(){
    Listavendedor* v = (Listavendedor*)malloc(sizeof(Listavendedor));
    v->inicio = NULL;
    return v;
}
//Funçao que verifica se LV esta vazia.
int lisvv(Listavendedor* v){
    if (v == NULL) return -1;
    if (v->inicio == NULL) return 0;
    else return 1;
}
//Funçao que verifica o tamanho de LV.
int tamv(Listavendedor* v){
    if (v == NULL) return -1;
    if (lisvv(v) == 0) return -2;
    Novendedor* no = v->inicio;
    int cont = 0;
    while (no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}
//Funçao que insere um item em LV.
int insiv(Listavendedor* v, Vendedor lo){
    if (v == NULL) return -1;
    Novendedor* no = (Novendedor*)malloc(sizeof(Novendedor));
    no->loja = lo;
    no->prox = v->inicio;
    v->inicio = no;
    return 0;
}
//Funçao que busca um item em LV, atraves de um ponteiro para ponteiro.
int busvendedor(Listavendedor *lv,char *nome,char *senha,Novendedor **v0) {
    if(lv == NULL) return -1;
    if(lisvv(lv) == 0) return -2;
    Novendedor *no = lv->inicio;
    while(no != NULL) {
        if(strcmp(nome,no->loja.nome)==0) {
            if(strcmp(senha,no->loja.senha)== 0){
                *v0 = no;
                return 0;
            }else return -3;
        }
        no = no->prox;
    }
    return -4;
}
//Funçao que mostras os itens de LV.
void showv(Listavendedor* v){
    if (v == NULL) return;
    if (lisvv(v) == 0) return;
    Novendedor* no = v->inicio;
    while (no != NULL){
        printf("Nome do vendedor: %s\n", no->loja.nome);
        printf("Descricao: %s\n", no->loja.tipo);
        printf("---------------------------------------\n");
        no = no->prox;
    }
}
//Funçao que insere os vendedores pre cadastrados no programa.
int vendedoresIniciais(Listavendedor *lv) {
    if(lv == NULL) return -2;

    Vendedor vs[] = {
        {"professorv","professorv","professorv"}
    };

    int i = 0;
    while(i < 1){
        insiv(lv,vs[i]);
        i++;
    }
}
