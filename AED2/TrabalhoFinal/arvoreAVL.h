#ifndef ARVORE_AVL_H
#define ARVORE_AVL_H

#include "estruturas.h"
#include <stdbool.h>


No* criarArvoreAVL();
No* criarNoAVL(Candidato candidato);
int altura(No* no);
int fatorBalanceamento(No* no);
No* rotacaoDireita(No* y);
No* rotacaoEsquerda(No* x);
No* balancear(No* no);
No* inserirNoAVL(No* no, Candidato candidato);
No* pesquisarPorEstadoAVL(No* raiz, char estado[3]);
No* pesquisarPorCidadeAVL(No *raiz, char estado[3], char cidade[50]);
No* pesquisarPorNumeroAVL(No* raiz, const char* estado, const char* cidade, const char* numero);
void imprimirEmOrdemAVL(No* raiz);
void mostrarInformacoesNoAVL(No* no);
void mostrarTodosCandidatosPorEstadoAVL(No *raiz, const char *estado, bool *encontrado);
int contarNos(No* no);
No* removerNoAVL(No* raiz, char numero[10]);
No* minValorNo(No* no);
void mostrarTodosCandidatosPorCidadeAVL(No *raiz, const char *estado, const char *cidade);
void buscaPorGeneroAVL(No* raiz, const char* estado, const char* cidade, const char* numero, const char* genero);
void buscaPorPartidoAVL(No* raiz, const char* estado, const char* cidade, const char* numero, const char* partido);
void buscaPorRacaAVL(No* raiz, const char* estado, const char* cidade, const char* numero, const char* raca);
void buscaGeneroPorEstadoAVL(No* raiz, const char* estado, const char* genero);
void buscaRacaPorEstadoAVL(No* raiz, const char* estado, const char* raca);
void buscaPartidoPorEstadoAVL(No* raiz, const char* estado, const char* partido);
void buscaRacaPorCidadeAVL(No* raiz, const char* estado, const char* cidade, const char* raca);
void buscaGeneroPorCidadeAVL(No* raiz, const char* estado, const char* cidade, const char* genero);
void buscaPartidoPorCidadeAVL(No* raiz, const char* estado, const char* cidade, const char* partido);

#endif