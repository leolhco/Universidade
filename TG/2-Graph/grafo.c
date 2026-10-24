#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



Grafo* criar_grafo(int n) {
    Grafo* grafo = (Grafo*) malloc(sizeof(Grafo));
    grafo->num_vertices = n;
    grafo->vertices = (Vertice*) malloc(n * sizeof(Vertice));
    for (int i = 0; i < n; i++) {
        grafo->vertices[i].lista_adj = NULL;
    }
    return grafo;
}



void adicionar_aresta(Grafo* grafo, int origem, int destino, int peso) {
    Aresta* nova_aresta = (Aresta*) malloc(sizeof(Aresta));
    nova_aresta->destino = destino;
    nova_aresta->peso = peso;
    nova_aresta->prox = grafo->vertices[origem].lista_adj;
    grafo->vertices[origem].lista_adj = nova_aresta;
}



Grafo* ler_grafo_de_arquivo(const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return NULL;
    }

    int num_cidades;
    fscanf(arquivo, "%d", &num_cidades);

    Grafo* grafo = criar_grafo(num_cidades);

    for (int i = 0; i < num_cidades; i++) {
        fscanf(arquivo, "%s", grafo->vertices[i].cidade);
    }

    char cidade_origem[100], cidade_destino[100];
    int peso;
    while (fscanf(arquivo, "%s %s %d", cidade_origem, cidade_destino, &peso) != EOF) {
        int origem = -1, destino = -1;

        for (int i = 0; i < num_cidades; i++) {
            if (strcmp(grafo->vertices[i].cidade, cidade_origem) == 0) {
                origem = i;
            }
            if (strcmp(grafo->vertices[i].cidade, cidade_destino) == 0) {
                destino = i;
            }
        }

        if (origem != -1 && destino != -1) {
            adicionar_aresta(grafo, origem, destino, peso);
        }
    }

    fclose(arquivo);
    return grafo;
}
