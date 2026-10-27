#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "estruturas.h"

// Funções da Árvore Binária de Pesquisa
No* criarArvore();
No* criarNo(Candidato candidato);
No* inserirNo(No *raiz, Candidato candidato);
No* pesquisarPorEstado(No *raiz, char estado[3]);
No* pesquisarPorCidade(No *raiz, char estado[3], char cidade[50]);
No* pesquisarPorNumero(No *raiz, char cidade[50], char estado[3], char numero[10]);
void imprimirEmOrdem(No *raiz);
void imprimirArvore(No *raiz, int nivel);
void mostrarInformacoesNo(No *no);
void mostrarTodosCandidatosPorEstado(No *raiz, const char *estado);
void mostrarTodosCandidatosPorCidade(No* raiz, char *estado, char *cidade);
void mostrarInformacoesAdicionaisNo(No* no, int opcaoDesejada);
void mostrarCorRacaEstado(No *raiz, const char *estado, const char *cor);
void mostrarGeneroEstado(No *raiz, const char *estado, const char *genero);
void mostrarPartidoEstado(No *raiz, const char *estado, const char *partido);
void mostrarCorCidade(No *raiz, const char *estado, const char *cidade, const char *cor);
void mostrarGeneroCidade(No *raiz, const char *estado, const char *cidade, const char *genero);
void mostrarPartidoCidade(No *raiz, const char *estado, const char *cidade, const char *partido);