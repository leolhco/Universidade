#include <stdio.h>
#include <stdlib.h>
#include "ecommerce.h"
#include <string.h>

//Funçao que cria a lista de usuarios(LU).
Listausuario *criarlu() {
    Listausuario *lu = (Listausuario*) malloc(sizeof(Listausuario));
    lu->inicio = NULL;
    return lu;
}
//Funçao que verifica se LU esta vazia.
int lisvu(Listausuario *lu) {
    if(lu == NULL) return -1;
    if(lu->inicio == NULL) return 0;
    else return 1;
}
//Funçao que verifica o tamanho LU.
int tamu(Listausuario *lu){
    if(lu == NULL) return -1;
    if(lisvu(lu) == 0) return -2;
    int cont = 0;
    Nousuario *no = lu->inicio;
    while(no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}
//Funçao que insere um item em LU.
int insiu(Listausuario *lu,Cliente cliente) {
    if(lu == NULL) return -1;
    Nousuario *no = (Nousuario*) malloc(sizeof(Nousuario));
    no->cl = cliente;
    no->prox = lu->inicio;
    lu->inicio = no;
    return 0;

}
//Funçao que busca um item em LU, atraves de um ponteiro para ponteiro.
int bususer(Listausuario *lu,char *us,char *senha,Nousuario **user) {
    if(lu == NULL) return -1;
    if(lisvu(lu) == 0) return -2;
    Nousuario *no = lu->inicio;
    while(no != NULL) {
        if(strcmp(us,no->cl.us)==0) {
            if(strcmp(senha,no->cl.senha)== 0){
                *user = no;
                return 0;
            }else return -3;
        }
        no = no->prox;
    }
    return -4;
}
//Funçao que mostra os itens de LU.
void showu(Listausuario *lu){
    if(lu == NULL) return;
    if(lisvu(lu) == 0) return;
    Nousuario *no = lu->inicio;
    while(no != NULL){
        printf("Nome: %s\n",no->cl.nome);
        printf("Usuario: %s\n",no->cl.us);
        printf("------------------------------------\n");
        no = no->prox;
    }
}
//Funçao que insere os usuarios pre cadastrados no programa.
int usuariosIniciais(Listausuario *lu) {
    if(lu == NULL) return -2;

    Cliente cs[] = {
        {"professor","professor","professor"},
        {"monitor","monitor","monitor"}
    };

    int i = 0;
    while(i < 2){
        insiu(lu,cs[i]);
        i++;
    }

    return 0;
}
