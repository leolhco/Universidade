#ifndef GRAFO_H
#define GRAFO_H

typedef struct Aresta {
    int destino;
    int peso;
    struct Aresta* prox;
} Aresta;

typedef struct Vertice {
    char cidade[100];
    Aresta* lista_adj;
} Vertice;

typedef struct Grafo {
    int num_vertices;
    Vertice* vertices;
} Grafo;

// Funções do grafo
Grafo* criar_grafo(int n);
void adicionar_aresta(Grafo* grafo, int origem, int destino, int peso);
Grafo* ler_grafo_de_arquivo(const char* nome_arquivo);

#endif
