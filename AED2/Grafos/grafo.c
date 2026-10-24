#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cidades {
   char nome[70];
   int indice;
} Cidades;

typedef struct no {
    int destino; // índice da cidade de destino
    float distancia; // peso da aresta, ou seja, a distância
    struct no* prox;
} No;

typedef struct lista {
    No* inicio; 
} Lista;

typedef struct grafo {
    Cidades* cidades; // vetor de cidades
    Lista* listas;    // vetor de listas de adjacência
    int numVertices;
    int numArestas;
} Grafo;

// Função para criar uma lista de adjacência
Lista* criarl() {
    Lista* l = (Lista*)malloc(sizeof(Lista));
    l->inicio = NULL;
    return l;
}

// Função para criar um grafo
Grafo* criarg(int numVertices, int numArestas) {
    Grafo* g = (Grafo*)malloc(sizeof(Grafo));
    g->numVertices = numVertices;
    g->numArestas = numArestas;

    // Alocar espaço para as cidades
    g->cidades = (Cidades*)malloc(numVertices * sizeof(Cidades));

    // Alocar espaço para as listas de adjacência
    g->listas = (Lista*)malloc(numVertices * sizeof(Lista));

    // Inicializar as listas de adjacência
    for (int i = 0; i < numVertices; i++) {
        g->listas[i] = *criarl(); // Cada cidade terá sua lista
    }

    return g;
}


void inserirCidade(Grafo* g, int indice, const char* nome) {
    if (indice >= g->numVertices) {
        printf("Erro: Índice excede o número de vértices do grafo.\n");
        return;
    }

    // Definir o índice da cidade
    g->cidades[indice].indice = indice;
    
    // Definir o nome da cidade (limitando o tamanho para evitar overflow)
    strncpy(g->cidades[indice].nome, nome, 70);
    g->cidades[indice].nome[69] = '\0';  // Garantir que o nome termine com '\0'

    // Inicializar a lista de adjacência para essa cidade
    //g->listas[indice] = *criarl();
}

// Função para adicionar uma aresta ao grafo (rodovia entre duas cidades)
void insereAresta(Grafo* g, int origem, int destino, float distancia) {
    No* novo = (No*)malloc(sizeof(No));
    novo->destino = destino;
    novo->distancia = distancia;
    novo->prox = g->listas[origem].inicio;
    g->listas[origem].inicio = novo;
}

int verificarAresta(Grafo* g, int origem, int destino){
    No* no = g->listas[origem].inicio;
    while(no != NULL){
        if(no->destino == destino) return 1;
        no = no->prox;
    }
    return 0;
}




void removerAresta(Grafo* g, int origem, int destino) {
    No* no = g->listas[origem].inicio;
    No* anterior = NULL;

    while (no != NULL) {
        if (no->destino == destino) {
            // Se for o primeiro nó
            if (anterior == NULL) {
                g->listas[origem].inicio = no->prox; // Ajusta o início da lista
            } else {
                anterior->prox = no->prox; // Ajusta o ponteiro do nó anterior
            }
            No* aux = no;
            no = no->prox; // Avança para o próximo nó
            free(aux); // Libera o nó removido
        } else {
            anterior = no; // Atualiza o anterior
            no = no->prox; // Avança para o próximo nó
        }
    }
}


// Função para imprimir o grafo
void imprimeGrafo(Grafo* g) {
    for (int i = 0; i < g->numVertices; i++) {
        printf("Cidade: %s\n", g->cidades[i].nome);
        No* adj = g->listas[i].inicio;
        while (adj != NULL) {
            printf(" -> %d (distância: %.2f)\n", adj->destino, adj->distancia);
            adj = adj->prox;
        }
        printf("\n");
    }
}

int buscaProfundidade_Grafo(Grafo *g, int ini, int *visitado) {
    int i, cont = 1;
    int ehCiclico = 0;

    // Inicializa todos os vértices como não visitados
    for (i = 0; i < g->numVertices; i++) {
        visitado[i] = 0;
    }

    // Realiza a busca em profundidade para cada vértice não visitado
    for (i = 0; i < g->numVertices; i++) {
        if (visitado[i] == 0) { 
            buscaProfundidade(g, i, visitado, cont, &ehCiclico);
        }
    }

    // Imprime a ordem de visitação
    for (i = 0; i < g->numVertices; i++) {
        printf("%d -> %d\n", i, visitado[i]);
    }

    // Retorna se há ciclo ou não
    return ehCiclico;
}

void buscaProfundidade(Grafo *g, int ini, int *visitado, int cont, int *ehCiclico) {
    visitado[ini] = cont;  // Marca o vértice como visitado com o valor da ordem de visitação

    No* no = g->listas[ini].inicio;
    while (no != NULL) {
        if (visitado[no->destino] > 0 && visitado[no->destino] < cont) {
            // Se já foi visitado e é parte de um ciclo
            *ehCiclico = 1;
        } else if (visitado[no->destino] == 0) {
            // Se o vértice ainda não foi visitado, continua a busca
            buscaProfundidade(g, no->destino, visitado, cont + 1, ehCiclico);
        }
        no = no->prox;
    }
}
