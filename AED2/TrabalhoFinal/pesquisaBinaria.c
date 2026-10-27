#include "pesquisaBinaria.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VETOR_MAX_TAM 470000

// Função para mostrar os dados de candidatos em um certo intervalo.
void mostrarCandidato(Candidato *vetorCandidatos, int inicio, int fim,
                      int tam) {

  // Tratamento de erro para caso os limites possivelmente causem loop
  // infinitos.
  if (inicio < 0 || fim >= tam || inicio > fim) {
    printf("Índices inválidos!\n");
    return;
  }

  for (int i = inicio; i <= fim; i++) {
    printf("Nome: %s\n", vetorCandidatos[i].nome);
    printf("Estado: %s\n", vetorCandidatos[i].estado);
    printf("Cidade: %s\n", vetorCandidatos[i].cidade);
    printf("Cargo: %s\n", vetorCandidatos[i].cargo);
    printf("Numero: %s\n", vetorCandidatos[i].numero);
    printf("Nome na Urna: %s\n", vetorCandidatos[i].nomeUrna);
    printf("Sigla do Partido: %s\n", vetorCandidatos[i].siglaPartido);
    printf("Genero: %s\n", vetorCandidatos[i].genero);
    printf("Grau de Instrução: %s\n", vetorCandidatos[i].grauInstrucao);
    printf("Cor/Raça: %s\n", vetorCandidatos[i].corRaca);
    printf("---------------------------------------------------------------\n");
  }
}

// Funçao para mostrar os candidatos baseado na chave partido.
void mostrarCandidatoPartido(Candidato *vetorCandidatos, int inicio, int fim,
                             char partido[10], int tam) {

  // Tratamento de erro para caso os limites possivelmente causem loop
  // infinitos.
  if (inicio < 0 || fim >= tam || inicio > fim) {
    printf("Índices inválidos!\n");
    return;
  }

  for (int i = inicio; i <= fim; i++) {
    if (strcmp(vetorCandidatos[i].siglaPartido, partido) == 0) {
      printf("Nome: %s\n", vetorCandidatos[i].nome);
      printf("Estado: %s\n", vetorCandidatos[i].estado);
      printf("Cidade: %s\n", vetorCandidatos[i].cidade);
      printf("Cargo: %s\n", vetorCandidatos[i].cargo);
      printf("Numero: %s\n", vetorCandidatos[i].numero);
      printf("Nome na Urna: %s\n", vetorCandidatos[i].nomeUrna);
      printf("Sigla do Partido: %s\n", vetorCandidatos[i].siglaPartido);
      printf("Genero: %s\n", vetorCandidatos[i].genero);
      printf("Grau de Instrução: %s\n", vetorCandidatos[i].grauInstrucao);
      printf("Cor/Raça: %s\n", vetorCandidatos[i].corRaca);
      printf(
          "---------------------------------------------------------------\n");
    }
  }
}

// Funçao para mostrar os candidatos baseado na chave genero.
void mostrarCandidatoGenero(Candidato *vetorCandidatos, int inicio, int fim,
                            char genero[10], int tam) {

  // Tratamento de erro para caso os limites possivelmente causem loop
  // infinitos.
  if (inicio < 0 || fim >= tam || inicio > fim) {
    printf("Índices inválidos!\n");
    return;
  }

  for (int i = inicio; i <= fim; i++) {
    if (strcmp(vetorCandidatos[i].genero, genero) == 0) {
      printf("Nome: %s\n", vetorCandidatos[i].nome);
      printf("Estado: %s\n", vetorCandidatos[i].estado);
      printf("Cidade: %s\n", vetorCandidatos[i].cidade);
      printf("Cargo: %s\n", vetorCandidatos[i].cargo);
      printf("Numero: %s\n", vetorCandidatos[i].numero);
      printf("Nome na Urna: %s\n", vetorCandidatos[i].nomeUrna);
      printf("Sigla do Partido: %s\n", vetorCandidatos[i].siglaPartido);
      printf("Genero: %s\n", vetorCandidatos[i].genero);
      printf("Grau de Instrução: %s\n", vetorCandidatos[i].grauInstrucao);
      printf("Cor/Raça: %s\n", vetorCandidatos[i].corRaca);
      printf(
          "---------------------------------------------------------------\n");
    }
  }
}

// Funçao para mostrar os candidatos baseado na chave corRaca.
void mostrarCandidatoCorRaca(Candidato *vetorCandidatos, int inicio, int fim,
                             char *corRaca, int tam) {

  // Tratamento de erro para caso os limites possivelmente causem loop
  // infinitos.
  if (inicio < 0 || fim >= tam || inicio > fim) {
    printf("Índices inválidos!\n");
    return;
  }

  for (int i = inicio; i <= fim; i++) {
    if (strcmp(vetorCandidatos[i].corRaca, corRaca) == 0) {
      printf("Nome: %s\n", vetorCandidatos[i].nome);
      printf("Estado: %s\n", vetorCandidatos[i].estado);
      printf("Cidade: %s\n", vetorCandidatos[i].cidade);
      printf("Cargo: %s\n", vetorCandidatos[i].cargo);
      printf("Numero: %s\n", vetorCandidatos[i].numero);
      printf("Nome na Urna: %s\n", vetorCandidatos[i].nomeUrna);
      printf("Sigla do Partido: %s\n", vetorCandidatos[i].siglaPartido);
      printf("Genero: %s\n", vetorCandidatos[i].genero);
      printf("Grau de Instrução: %s\n", vetorCandidatos[i].grauInstrucao);
      printf("Cor/Raça: %s\n", vetorCandidatos[i].corRaca);
      printf(
          "---------------------------------------------------------------\n");
    }
  }
}

/* Função para ordenar o vetor com as 3 chaves propostas pela professora no
enunciado, usando ShellSort e a sequência de Knuth.*/
void shellSort(Candidato *vetorCandidatos, int tam) {
  int i, j, h = 1;
  Candidato aux;

  // Calcula o fator h (sequência de Knuth)
  while (h < tam) {
    h = h * 3 + 1;
  }

  // Ordenação por Shell Sort
  while (h > 1) {
    h /= 3;
    for (i = h; i < tam; i++) {
      aux = vetorCandidatos[i];
      j = i;

      /* Comparação em três níveis: estado, cidade e número. primeiro cosidera
      se estado de vetorCandidatos[j - h] é lexicograficamente menor que o
      estado de aux, se for faz a troca, caso seja igual considera a cidade,
      caso a cidade seja igual faz a mesma coisa para o número.
      */
      while (j >= h) {
        if (strcmp(vetorCandidatos[j - h].estado, aux.estado) > 0) {
          vetorCandidatos[j] = vetorCandidatos[j - h];
        } else if (strcmp(vetorCandidatos[j - h].estado, aux.estado) == 0) {
          if (strcmp(vetorCandidatos[j - h].cidade, aux.cidade) > 0) {
            vetorCandidatos[j] = vetorCandidatos[j - h];
          } else if (strcmp(vetorCandidatos[j - h].cidade, aux.cidade) == 0) {
            if (strcmp(vetorCandidatos[j - h].numero, aux.numero) > 0) {
              vetorCandidatos[j] = vetorCandidatos[j - h];
            } else {
              break;
            }
          } else {
            break;
          }
        } else {
          break;
        }
        j -= h;
      }
      vetorCandidatos[j] = aux;
    }
  }
}

// Funçao que por busca binaria encontra o indice do ultimo candidato no vetor
// baseado na chave estado.
int buscaBinariaEstadoCima(Candidato *vetorCandidatos, int tam,
                           char estado[3]) {
  int inf = 0, sup = tam - 1, meio, resultado = -1;

  while (inf <= sup) {
    meio = (inf + sup) / 2;

    if (strcmp(vetorCandidatos[meio].estado, estado) == 0) {
      resultado = meio;
      inf = meio + 1;
    } else if (strcmp(vetorCandidatos[meio].estado, estado) > 0) {
      sup = meio - 1;
    } else {
      inf = meio + 1;
    }
  }

  return resultado;
}

// Funçao que por busca binaria encontra o indice do primeiro candidato no vetor
// baseado na chave estado.
int buscaBinariaEstadoBaixo(Candidato *vetorCandidatos, int tam,
                            char estado[3]) {
  int inf = 0, sup = tam - 1, meio, resultado = -1;

  while (inf <= sup) {
    meio = (inf + sup) / 2;

    if (strcmp(vetorCandidatos[meio].estado, estado) == 0) {
      resultado = meio;
      sup = meio - 1;
    } else if (strcmp(vetorCandidatos[meio].estado, estado) > 0) {
      sup = meio - 1;
    } else {
      inf = meio + 1;
    }
  }

  return resultado;
}

// Funçao que por busca binaria encontra o indice do ultimo candidato no vetor
// baseado na chave cidade.
int buscaBinariaCidadeCima(Candidato *vetorCandidatos, int tam, char estado[3],
                           char cidade[100]) {
  int inf, sup, meio, resultado = -1;

  inf = buscaBinariaEstadoBaixo(vetorCandidatos, tam, estado);
  sup = buscaBinariaEstadoCima(vetorCandidatos, tam, estado);

  // Busca binária pela cidade dentro do intervalo de estado.
  while (inf <= sup) {
    meio = (inf + sup) / 2;

    if (strcmp(vetorCandidatos[meio].cidade, cidade) == 0) {
      resultado = meio;
      inf = meio + 1;
    } else if (strcmp(vetorCandidatos[meio].cidade, cidade) > 0) {
      sup = meio - 1;
    } else {
      inf = meio + 1;
    }
  }

  return resultado;
}

// Funçao que por busca binaria encontra o indice do primeiro candidato no vetor
// baseado na chave cidade.
int buscaBinariaCidadeBaixo(Candidato *vetorCandidatos, int tam, char estado[3],
                            char cidade[100]) {
  int inf, sup, meio, resultado = -1;

  inf = buscaBinariaEstadoBaixo(vetorCandidatos, tam, estado);
  sup = buscaBinariaEstadoCima(vetorCandidatos, tam, estado);

  // Busca binária pela cidade dentro do intervalo de estado.
  while (inf <= sup) {
    meio = (inf + sup) / 2;

    if (strcmp(vetorCandidatos[meio].cidade, cidade) == 0) {
      resultado = meio;
      sup = meio - 1;
    } else if (strcmp(vetorCandidatos[meio].cidade, cidade) > 0) {
      sup = meio - 1;
    } else {
      inf = meio + 1;
    }
  }

  return resultado;
}

// Funçao que por buca binaria encontra um candidato com a chave numero
// desejada.
int buscaBinariaNumero(Candidato *vetorCandidatos, int tam, char estado[3],
                       char cidade[100], char numero[10]) {
  int inf, sup, meio;

  inf = buscaBinariaCidadeBaixo(vetorCandidatos, tam, estado, cidade);
  sup = buscaBinariaCidadeCima(vetorCandidatos, tam, estado, cidade);

  // Busca binária pelo número dentro do intervalo restrito de cidade.
  while (inf <= sup) {
    meio = (inf + sup) / 2;

    if (strcmp(vetorCandidatos[meio].numero, numero) == 0) {
      return meio;
    }

    else if (strcmp(vetorCandidatos[meio].numero, numero) > 0)
      sup = meio - 1;
    else
      inf = meio + 1;
  }

  return -1;
}