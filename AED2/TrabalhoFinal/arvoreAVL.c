#include "arvoreAVL.h"
#include "estruturas.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>


No* criarArvoreAVL() {
    return NULL;
}

No* criarNoAVL(Candidato candidato) {
    No* no = (No*)malloc(sizeof(No));
    if (no == NULL) {
        printf("Erro de alocação de memória\n");
        exit(1);
    }

    no->candidato = candidato;
    no->esquerda = NULL;
    no->direita = NULL;
    no->altura = 0;
    return no;
}

int altura(No* no) {
    return (no == NULL) ? -1 : no->altura; // Altura inicializada como -1 para nós nulos
}

void atualizarAltura(No* no) {
    if (no != NULL) {
        no->altura = 1 + fmax(altura(no->esquerda), altura(no->direita));
    }
}

int fatorBalanceamento(No* no) {
    if (no == NULL) return 0;
    return altura(no->esquerda) - altura(no->direita);
}

No* rotacaoDireita(No* y) {
    No* x = y->esquerda;
    No* T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    atualizarAltura(y); 
    atualizarAltura(x); 

    return x;
}

No* rotacaoEsquerda(No* x) {
    No* y = x->direita;
    No* T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    atualizarAltura(x); 
    atualizarAltura(y); 

    return y;
}

No* balancear(No* no) {
    if (no == NULL) return no;

    atualizarAltura(no); 

    int balance = fatorBalanceamento(no);

    // Caso 1: desbalanceada à esquerda esquerda
    if (balance > 1 && fatorBalanceamento(no->esquerda) >= 0) {
        return rotacaoDireita(no);
    }

    // Caso 2: desbalanceada à direita direita
    if (balance < -1 && fatorBalanceamento(no->direita) <= 0) {
        return rotacaoEsquerda(no);
    }

    // Caso 3: desbalanceada à esquerda direita
    if (balance > 1 && fatorBalanceamento(no->esquerda) < 0) {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }

    // Caso 4: desbalanceada à direita esquerda
    if (balance < -1 && fatorBalanceamento(no->direita) > 0) {
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }

    return no; 
}

No* inserirNoAVL(No* no, Candidato candidato) {
    // Inserir o novo candidato na árvore
    if (no == NULL) return criarNoAVL(candidato);

    int cmpEstado = strcmp(candidato.estado, no->candidato.estado);
    if (cmpEstado < 0) {
        no->esquerda = inserirNoAVL(no->esquerda, candidato);
    } else if (cmpEstado > 0) {
        no->direita = inserirNoAVL(no->direita, candidato);
    } else {
        int cmpCidade = strcmp(candidato.cidade, no->candidato.cidade);
        if (cmpCidade < 0) {
            no->esquerda = inserirNoAVL(no->esquerda, candidato);
        } else if (cmpCidade > 0) {
            no->direita = inserirNoAVL(no->direita, candidato);
        } else {
            int cmpNumero = strcmp(candidato.numero, no->candidato.numero);
            if (cmpNumero < 0) {
                no->esquerda = inserirNoAVL(no->esquerda, candidato);
            } else {
                no->direita = inserirNoAVL(no->direita, candidato);
            }
        }
    }

    
    return balancear(no);
}


void imprimirEmOrdemAVL(No* raiz) {
    if (raiz != NULL) {
        imprimirEmOrdemAVL(raiz->esquerda);
        mostrarInformacoesNoAVL(raiz);
        imprimirEmOrdemAVL(raiz->direita);
    }
}



No* pesquisarPorEstadoAVL(No *raiz, char estado[3]) {
    if (raiz == NULL || strcmp(raiz->candidato.estado, estado) == 0) {
        return raiz;  // Encontrou ou a árvore está vazia
    }

    // Comparar o estado e decidir se vai para a esquerda ou direita
    if (strcmp(raiz->candidato.estado, estado) > 0) {
        return pesquisarPorEstadoAVL(raiz->esquerda, estado);
    } else {
        return pesquisarPorEstadoAVL(raiz->direita, estado);
    }
}


No* pesquisarPorCidadeAVL(No *raiz, char estado[3], char cidade[50]) {
    if (raiz == NULL) return NULL;

    // Primeiro, verificar se o estado do candidato é o mesmo que o estado procurado
    if (strcmp(raiz->candidato.estado, estado) == 0) {
        // Se o estado for o correto, verificar a cidade
        if (strcmp(raiz->candidato.cidade, cidade) == 0) {
            return raiz;  // Encontrou o candidato pela cidade
        }
    }

    // Continuar a busca pela esquerda e pela direita
    No *esquerda = pesquisarPorCidadeAVL(raiz->esquerda, estado, cidade);
    if (esquerda != NULL) return esquerda;  // Encontrou o candidato na subárvore esquerda

    return pesquisarPorCidadeAVL(raiz->direita, estado, cidade);  // Buscar na subárvore direita
}



No* pesquisarPorNumeroAVL(No* raiz, const char* estado, const char* cidade, const char* numero) {
    if (raiz == NULL) return NULL;

    // Primeiro, verificar se o estado do candidato é o mesmo que o estado procurado
    if (strcmp(raiz->candidato.estado, estado) == 0) {
        // Verificar se a cidade é a mesma
        if (strcmp(raiz->candidato.cidade, cidade) == 0) {
            // Verificar o número do candidato
            if (strcmp(raiz->candidato.numero, numero) == 0) {
                return raiz;  // Encontrou o candidato
            }
        }
    }

    // Continuar a busca pela esquerda e pela direita
    No *esquerda = pesquisarPorNumeroAVL(raiz->esquerda, cidade, estado, numero);
    if (esquerda != NULL) return esquerda;  // Encontrou o candidato na subárvore esquerda

    return pesquisarPorNumeroAVL(raiz->direita, cidade, estado, numero);  // Buscar na subárvore direita
}


void mostrarTodosCandidatosPorEstadoAVL(No *raiz, const char *estado, bool *encontrado) {
        if (raiz != NULL) {
        // Primeiro, percorra a subárvore esquerda
        mostrarTodosCandidatosPorEstadoAVL(raiz->esquerda, estado, encontrado);

        // Verifique se o estado do nó atual corresponde ao estado desejado
        if (strcmp(raiz->candidato.estado, estado) == 0) {
            mostrarInformacoesNoAVL(raiz);  // Mostra as informações do nó
            *encontrado = true;              // Indica que pelo menos um candidato foi encontrado
        } 

        // Depois, percorra a subárvore direita
        mostrarTodosCandidatosPorEstadoAVL(raiz->direita, estado, encontrado);
    }
}



void mostrarInformacoesNoAVL(No *no) {
    if (no != NULL) {
        printf("\n--------------------------------------------\n");
        printf("Nome: %s\n", no->candidato.nome);
        printf("Estado: %s\n", no->candidato.estado);
        printf("Cidade: %s\n", no->candidato.cidade);
        printf("Número: %s\n", no->candidato.numero);
        printf("Cargo: %s\n", no->candidato.cargo);
        printf("Nome na Urna: %s\n", no->candidato.nomeUrna);
        printf("Sigla do Partido: %s\n", no->candidato.siglaPartido);
        printf("Gênero: %s\n", no->candidato.genero);
        printf("Grau de Instrução: %s\n", no->candidato.grauInstrucao);
        printf("Cor/Raça: %s\n", no->candidato.corRaca);
        printf("--------------------------------------------\n");
    } else {
        printf("CANDIDATO NÃO ENCONTRADO!\n");
    }
}

int contarNos(No* no) {
    if (no == NULL) {
        return 0;  
    }
    return 1 + contarNos(no->esquerda) + contarNos(no->direita);  // Conta o nó atual e os filhos
}


No* minValorNo(No* no) {
    No* atual = no;
    // Encontra o nó mais à esquerda (com o menor valor)
    while (atual->esquerda != NULL) 
        atual = atual->esquerda;

    return atual;
}

No* removerNoAVL(No* raiz, char numero[10]) {
    if (raiz == NULL) return raiz;

    // Se o número a ser removido for menor que o número da raiz, vá para a subárvore esquerda
    if (strcmp(numero, raiz->candidato.numero) < 0) {
        raiz->esquerda = removerNoAVL(raiz->esquerda, numero);

    // Se o número a ser removido for maior que o número da raiz, vá para a subárvore direita
    } else if (strcmp(numero, raiz->candidato.numero) > 0) {
        raiz->direita = removerNoAVL(raiz->direita, numero);

    // Se o número for igual ao número do nó atual, este é o nó a ser removido
    } else {
        // Caso 1: O nó não tem filhos (nó folha)
        if (raiz->esquerda == NULL && raiz->direita == NULL) {
            free(raiz);
            return NULL;

        // Caso 2: O nó tem um filho (esquerda ou direita)
        } else if (raiz->esquerda == NULL) {
            No* temp = raiz->direita;
            free(raiz);
            return temp;

        } else if (raiz->direita == NULL) {
            No* temp = raiz->esquerda;
            free(raiz);
            return temp;

        // Caso 3: O nó tem dois filhos
        } else {
            // Encontra o sucessor in-order (menor nó na subárvore direita)
            No* temp = minValorNo(raiz->direita);
            // Copia os dados do sucessor para este nó
            raiz->candidato = temp->candidato;
            // Remove o sucessor in-order
            raiz->direita = removerNoAVL(raiz->direita, temp->candidato.numero);
        }
    }

    // Reequilibrar a árvore AVL após a remoção
    raiz = balancear(raiz);

    return raiz;
}


void mostrarTodosCandidatosPorCidadeAVL(No *raiz, const char *estado, const char *cidade) {
    if (raiz == NULL) 
        return;  // Se a árvore está vazia, não faz nada

    // Percorre a subárvore esquerda
    mostrarTodosCandidatosPorCidadeAVL(raiz->esquerda, estado, cidade);

    // Verifica se o candidato está no estado e cidade especificados
    if (strcmp(raiz->candidato.estado, estado) == 0 && strcmp(raiz->candidato.cidade, cidade) == 0) 
        mostrarInformacoesNoAVL(raiz);

    // Percorre a subárvore direita
    mostrarTodosCandidatosPorCidadeAVL(raiz->direita, estado, cidade);
}

void buscaGeneroPorEstadoAVL(No* raiz, const char* estado, const char* genero) 
{
    if (raiz == NULL) return;

    buscaGeneroPorEstadoAVL(raiz->esquerda, estado, genero);

    if (strcmp(raiz->candidato.estado, estado) == 0 &&
        strcmp(raiz->candidato.genero, genero) == 0) {
        mostrarInformacoesNoAVL(raiz);
    }

    buscaGeneroPorEstadoAVL(raiz->direita, estado, genero);
}

// Função para buscar candidatos por gênero

void buscaGeneroPorCidadeAVL(No* raiz, const char* estado, const char* cidade, const char* genero) 
{
    if (raiz == NULL) return;

    buscaGeneroPorCidadeAVL(raiz->esquerda, estado, cidade, genero);

    if (strcmp(raiz->candidato.estado, estado) == 0 &&
        strcmp(raiz->candidato.cidade, cidade) == 0 &&
        strcmp(raiz->candidato.genero, genero) == 0) {
        mostrarInformacoesNoAVL(raiz);
    }

    buscaGeneroPorCidadeAVL(raiz->direita, estado, cidade, genero);
}

void buscaPorGeneroAVL(No* raiz, const char* estado, const char* cidade, const char* numero, const char* genero) 
{
    if (raiz == NULL) return;

    buscaPorGeneroAVL(raiz->esquerda, estado, cidade, numero, genero);

    if (strcmp(raiz->candidato.estado, estado) == 0 &&
        strcmp(raiz->candidato.cidade, cidade) == 0 &&
        strcmp(raiz->candidato.numero, numero) == 0 &&
        strcmp(raiz->candidato.genero, genero) == 0) {
        mostrarInformacoesNoAVL(raiz);
    }

    buscaPorGeneroAVL(raiz->direita, estado, cidade, numero, genero);
}

void buscaPartidoPorEstadoAVL(No* raiz, const char* estado, const char* partido) {
    if (raiz == NULL) return;

    buscaPartidoPorEstadoAVL(raiz->esquerda, estado, partido);

    if (strcmp(raiz->candidato.estado, estado) == 0 &&
        strcmp(raiz->candidato.siglaPartido, partido) == 0) {
        mostrarInformacoesNoAVL(raiz);
        
    }

    buscaPartidoPorEstadoAVL(raiz->direita, estado, partido);
}

void buscaPartidoPorCidadeAVL(No* raiz, const char* estado, const char* cidade, const char* partido) {
    if (raiz == NULL) return;

    buscaPartidoPorCidadeAVL(raiz->esquerda, estado, cidade, partido);

    if (strcmp(raiz->candidato.estado, estado) == 0 &&
        strcmp(raiz->candidato.cidade, cidade) == 0 &&
        strcmp(raiz->candidato.siglaPartido, partido) == 0) {
        mostrarInformacoesNoAVL(raiz);
        
    }

    buscaPartidoPorCidadeAVL(raiz->direita, estado, cidade, partido);
}

// Função para buscar candidatos por partido
void buscaPorPartidoAVL(No* raiz, const char* estado, const char* cidade, const char* numero, const char* partido) {
    if (raiz == NULL) return;

    

    buscaPorPartidoAVL(raiz->esquerda, estado, cidade, numero, partido);

    if (strcmp(raiz->candidato.estado, estado) == 0 &&
        strcmp(raiz->candidato.cidade, cidade) == 0 &&
        strcmp(raiz->candidato.numero, numero) == 0 &&
        strcmp(raiz->candidato.siglaPartido, partido) == 0) {
        mostrarInformacoesNoAVL(raiz);
        
    }

    buscaPorPartidoAVL(raiz->direita, estado, cidade, numero, partido);
}

void buscaRacaPorEstadoAVL(No* raiz, const char* estado, const char* raca) {
    if (raiz == NULL) return;
    
    buscaRacaPorEstadoAVL(raiz->esquerda, estado, raca);

    if (strcmp(raiz->candidato.estado, estado) == 0 &&
        strcmp(raiz->candidato.corRaca, raca) == 0) {
        mostrarInformacoesNoAVL(raiz);

    }

    buscaRacaPorEstadoAVL(raiz->direita, estado, raca);
}

void buscaRacaPorCidadeAVL(No* raiz, const char* estado, const char* cidade, const char* raca) {
    if (raiz == NULL) return;
    
    buscaRacaPorCidadeAVL(raiz->esquerda, estado, cidade, raca);

    if (strcmp(raiz->candidato.estado, estado) == 0 &&
        strcmp(raiz->candidato.cidade, cidade) == 0 &&
        strcmp(raiz->candidato.corRaca, raca) == 0) {
        mostrarInformacoesNoAVL(raiz);

    }

    buscaRacaPorCidadeAVL(raiz->direita, estado, cidade, raca);
}

// Função para buscar candidatos por raça
void buscaPorRacaAVL(No* raiz, const char* estado, const char* cidade, const char* numero, const char* raca) {
    if (raiz == NULL) return;
    
    buscaPorRacaAVL(raiz->esquerda, estado, cidade, numero, raca);

    if (strcmp(raiz->candidato.estado, estado) == 0 &&
        strcmp(raiz->candidato.cidade, cidade) == 0 &&
        strcmp(raiz->candidato.numero, numero) == 0 &&
        strcmp(raiz->candidato.corRaca, raca) == 0) {
        mostrarInformacoesNoAVL(raiz);

    }

    buscaPorRacaAVL(raiz->direita, estado, cidade, numero, raca);
}



