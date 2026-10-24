#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// COMO USAR O MAKEFILE NESTE CÓDIGO

// 1 -> abra o diretório que contenha todos os arquivos necessários
// 2 -> para compilar, basta digitar o comando "make" no terminal
// 3 -> para executar o arquivo, digite o nome do arquivo executável. Por exemplo:
// -> No linux:   ./programa_grafo   -> No windows:      programa_grafo.exe



// REFERÊNCIA DOS DADOS DO ARQUIVO
// https://www.rome2rio.com


void imprimir_menu() {
    printf("\nMenu:\n");
    printf("1. Ler dados do grafo a partir de um arquivo\n");
    printf("2. Imprimir o grafo completo\n");
    printf("3. Inserir uma nova aresta\n");
    printf("4. Remover uma aresta\n");
    printf("5. Verificar se existe uma rodovia entre duas cidades\n");
    printf("6. Listar cidades com ligação direta até 100 km\n");
    printf("7. Verificar se o grafo é acíclico\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
}



void imprimir_grafo(Grafo* grafo) {
    printf("\n  ---------------   GRAFO  ------------------:\n");
    for (int i = 0; i < grafo->num_vertices; i++) {
        printf("Cidade Origem: [%s]\n", grafo->vertices[i].cidade);
        Aresta* adj = grafo->vertices[i].lista_adj;
        while (adj != NULL) {
            printf("           Cidade Destino -> [%s] (DISTANCIA: %d km)\n", grafo->vertices[adj->destino].cidade, adj->peso);
            adj = adj->prox;
        }
    }
}



void inserir_aresta_usuario(Grafo* grafo) {
    char cidade_origem[100], cidade_destino[100];
    int peso;
    printf("Digite a [cidade de origem]: ");
    scanf("%s", cidade_origem);
    printf("Digite a [cidade de destino]: ");
    scanf("%s", cidade_destino);
    printf("Digite a [distancia entre as cidades]: ");
    scanf("%d", &peso);

    int origem = -1, destino = -1;
    for (int i = 0; i < grafo->num_vertices; i++) {
        if (strcmp(grafo->vertices[i].cidade, cidade_origem) == 0) {
            origem = i;
        }
        if (strcmp(grafo->vertices[i].cidade, cidade_destino) == 0) {
            destino = i;
        }
    }

    if (origem != -1 && destino != -1) {
        adicionar_aresta(grafo, origem, destino, peso);
        printf("Aresta inserida com SUCESSO!!!!\n");
    } else {
        printf("ERRO: Cidades não encontradas.\n");
    }
}



void remover_aresta_usuario(Grafo* grafo) {
    char cidade_origem[100], cidade_destino[100];
    printf("Digite a cidade de ORIGEM: ");
    scanf("%s", cidade_origem);
    printf("Digite a cidade de DESTINO: ");
    scanf("%s", cidade_destino);

    int origem = -1, destino = -1;
    for (int i = 0; i < grafo->num_vertices; i++) {
        if (strcmp(grafo->vertices[i].cidade, cidade_origem) == 0) {
            origem = i;
        }
        if (strcmp(grafo->vertices[i].cidade, cidade_destino) == 0) {
            destino = i;
        }
    }

    if (origem != -1 && destino != -1) {
        Aresta* atual = grafo->vertices[origem].lista_adj;
        Aresta* anterior = NULL;
        while (atual != NULL && atual->destino != destino) {
            anterior = atual;
            atual = atual->prox;
        }
        if (atual != NULL) {
            if (anterior == NULL) {
                grafo->vertices[origem].lista_adj = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            printf("Aresta removida com SUCESSO!\n");
        } else {
            printf("ERRO: Aresta não encontrada.\n");
        }
    } else {
        printf("ERRO: Cidades não encontradas.\n");
    }
}



void verificar_rodovia(Grafo* grafo) {
    char cidade_origem[100], cidade_destino[100];
    printf("Digite a cidade de ORIGEM: ");
    scanf("%s", cidade_origem);
    printf("Digite a cidade de DESTINO: ");
    scanf("%s", cidade_destino);

    int origem = -1, destino = -1;
    for (int i = 0; i < grafo->num_vertices; i++) {
        if (strcmp(grafo->vertices[i].cidade, cidade_origem) == 0) {
            origem = i;
        }
        if (strcmp(grafo->vertices[i].cidade, cidade_destino) == 0) {
            destino = i;
        }
    }

    if (origem != -1 && destino != -1) {
        Aresta* adj = grafo->vertices[origem].lista_adj;
        while (adj != NULL) {
            if (adj->destino == destino) {
                printf("SUCESSO! Existe uma rodovia de %s para %s com distancia de %d km.\n", cidade_origem, cidade_destino, adj->peso);
                return;
            }
            adj = adj->prox;
        }
        printf("NAO existe rodovia direta entre %s e %s.\n", cidade_origem, cidade_destino);
    } else {
        printf("ERRO: Cidades nao encontradas.\n");
    }
}



void listar_ligacoes(Grafo* grafo) {
    char cidade[100];
    printf("Digite a cidade: ");
    scanf("%s", cidade);

    int indice = -1;
    for (int i = 0; i < grafo->num_vertices; i++) {
        if (strcmp(grafo->vertices[i].cidade, cidade) == 0) {
            indice = i;
            break;
        }
    }

    if (indice != -1) {
        printf("Cidades com ligacao direta até 100 km de %s:\n", cidade);
        Aresta* adj = grafo->vertices[indice].lista_adj;
        while (adj != NULL) {
            if (adj->peso <= 100) {
                printf("  -> %s (DISTANCIA: %d km)\n", grafo->vertices[adj->destino].cidade, adj->peso);
            }
            adj = adj->prox;
        }
    } else {
        printf("ERRO: Cidade não encontrada.\n");
    }
}





// 88888888888888888888888888888888888888888888888888888888888888888888888888888

int verificar_aciclico(Grafo* grafo) {
    // Implementação de verificação de ciclo em grafo,
    // normalmente usa-se busca em profundidade (DFS). Aqui fica um placeholder.
    return 0;
}

// 88888888888888888888888888888888888888888888888888888888888888888888888888888




int main() {
    Grafo* grafo = NULL;
    int opcao;

    do {
        imprimir_menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                char arquivo[100];
                printf("Digite o nome do arquivo de dados: ");
                scanf("%s", arquivo);
                grafo = ler_grafo_de_arquivo(arquivo);
                if (grafo != NULL) {
                    printf("Grafo carregado com SUCESSO!\n");
                } else {
                    printf("ERRO ao carregar o grafo.\n");
                }
                break;
            }
            case 2:
                if (grafo != NULL) {
                    imprimir_grafo(grafo);
                } else {
                    printf("NENHUM grafo carregado.\n");
                }
                break;
            case 3:
                if (grafo != NULL) {
                    inserir_aresta_usuario(grafo);
                } else {
                    printf("NENHUM grafo carregado.\n");
                }
                break;
            case 4:
                if (grafo != NULL) {
                    remover_aresta_usuario(grafo);
                } else {
                    printf("NENHUM grafo carregado.\n");
                }
                break;
            case 5:
                if (grafo != NULL) {
                    verificar_rodovia(grafo);
                } else {
                    printf("NENHUM grafo carregado.\n");
                }
                break;
            case 6:
                if (grafo != NULL) {
                    listar_ligacoes(grafo);
                } else {
                    printf("NENHUM grafo carregado.\n");
                }
                break;
            case 7:
                if (grafo != NULL) {
                    verificar_aciclico(grafo);
                } else {
                    printf("NENHUM grafo carregado.\n");
                }
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    // Liberar a memória alocada para o grafo


    return 0;
}

