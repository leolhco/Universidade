#ifndef PESQUISA_BINARIA_H
#define PESQUISA_BINARIA_H

#include "estruturas.h"

// Funções de amostragem para cada caso.
void mostrarCandidato(Candidato *vetorCandidatos, int inicio, int fim, int tam);
void mostrarCandidatoPartido(Candidato *vetorCandidatos, int inicio, int fim, char partido[10], int tam);
void mostrarCandidatoGenero(Candidato *vetorCandidatos, int inicio, int fim, char genero[10], int tam);
void mostrarCandidatoCorRaca(Candidato *vetorCandidatos, int inicio, int fim, char corRaca[10], int tam);

// Ordenação do vetor, shellSort tem o melhor desempenho sendo O(n^1.26).
void shellSort(Candidato *vetorCandidatos, int tam);

// Funções de busca considerando cada caso e buscando os limites de cada caso para amostragem geral de todos os itens.
int buscaBinariaEstadoCima(Candidato *vetorCandidatos, int tam, char estado[3]);
int buscaBinariaEstadoBaixo(Candidato *vetorCandidatos, int tam, char estado[3]);
int buscaBinariaCidadeCima(Candidato *vetorCandidatos, int tam, char estado[3], char cidade[100]);
int buscaBinariaCidadeBaixo(Candidato *vetorCandidatos, int tam, char estado[3], char cidade[100]);
int buscaBinariaNumero(Candidato *vetorCandidatos, int tam, char estado[3], char cidade[100], char numero[10]);

#endif