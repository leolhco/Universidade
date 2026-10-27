
#include "arvoreBinaria.h"

No* criarArvore(){
    No *raiz = NULL;
    return raiz;
}

No* criarNo(Candidato novoCandidato) {
    No *novoNo = (No*) malloc(sizeof(No));  // Aloca memória para o novo nó
    if (novoNo == NULL) {
        printf("Erro de alocação de memória!\n");
        exit(1);  // Sai do programa caso a alocação falhe
    }

    // Copia os dados do candidato para o novo nó
    strcpy(novoNo->candidato.estado, novoCandidato.estado);
    strcpy(novoNo->candidato.cidade, novoCandidato.cidade);
    strcpy(novoNo->candidato.numero, novoCandidato.numero);
    strcpy(novoNo->candidato.cargo, novoCandidato.cargo);
    strcpy(novoNo->candidato.nome, novoCandidato.nome);
    strcpy(novoNo->candidato.nomeUrna, novoCandidato.nomeUrna);
    strcpy(novoNo->candidato.siglaPartido, novoCandidato.siglaPartido);
    strcpy(novoNo->candidato.genero, novoCandidato.genero);
    strcpy(novoNo->candidato.grauInstrucao, novoCandidato.grauInstrucao);
    strcpy(novoNo->candidato.corRaca, novoCandidato.corRaca);
    
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

No* inserirNo(No *raiz, Candidato novoCandidato) {
    // Se a árvore estiver vazia, cria um novo nó
    if (raiz == NULL) {
        return criarNo(novoCandidato);
    }

    // Comparar o estado
    int cmpEstado = strcmp(novoCandidato.estado, raiz->candidato.estado);
    
    if (cmpEstado < 0) {
        // O novo candidato tem estado menor, insere à esquerda
        raiz->esquerda = inserirNo(raiz->esquerda, novoCandidato);
    } else if (cmpEstado > 0) {
        // O novo candidato tem estado maior, insere à direita
        raiz->direita = inserirNo(raiz->direita, novoCandidato);
    } else {
        // Estados são iguais, comparar a cidade
        int cmpCidade = strcmp(novoCandidato.cidade, raiz->candidato.cidade);
        
        if (cmpCidade < 0) {
            // O novo candidato tem cidade menor, insere à esquerda
            raiz->esquerda = inserirNo(raiz->esquerda, novoCandidato);
        } else if (cmpCidade > 0) {
            // O novo candidato tem cidade maior, insere à direita
            raiz->direita = inserirNo(raiz->direita, novoCandidato);
        } else {
            // Estados e cidades são iguais, comparar o número do candidato
            int cmpNumero = strcmp(novoCandidato.numero, raiz->candidato.numero);
            if (cmpNumero < 0) {
                raiz->esquerda = inserirNo(raiz->esquerda, novoCandidato);
            } else {
                raiz->direita = inserirNo(raiz->direita, novoCandidato);
            }
        }
    }

    return raiz;  // Retorna a raiz atualizada
}

No* pesquisarPorEstado(No *raiz, char estado[3]){
    if(raiz == NULL || strcmp(raiz->candidato.estado, estado) == 0) return raiz;

    if(strcmp(raiz->candidato.estado, estado) == 1){
        return pesquisarPorEstado(raiz->esquerda, estado);
    } else {
        return pesquisarPorEstado(raiz->direita, estado);
    }
}

No* pesquisarPorCidade(No *raiz, char estado[3], char cidade[50]) {
    if (raiz == NULL) return NULL;

    // Primeiro, verificar se o estado do candidato é o mesmo que o estado procurado
    if (strcmp(raiz->candidato.estado, estado) == 0) {
        // Se o estado for o correto, verificar a cidade
        if (strcmp(raiz->candidato.cidade, cidade) == 0) {
            return raiz;  // Encontrou o candidato pela cidade
        }
    }

    // Continuar a busca pela esquerda e pela direita
    No *esquerda = pesquisarPorCidade(raiz->esquerda, estado, cidade);
    if (esquerda != NULL) return esquerda;  // Encontrou o candidato na subárvore esquerda

    return pesquisarPorCidade(raiz->direita, estado, cidade);  // Buscar na subárvore direita
}

No* pesquisarPorNumero(No *raiz, char cidade[50], char estado[3], char numero[10]) {
    if (raiz == NULL) return NULL;

    if (strcmp(raiz->candidato.estado, estado) == 0) {

        if (strcmp(raiz->candidato.cidade, cidade) == 0) {

            if (strcmp(raiz->candidato.numero, numero) == 0) {
                return raiz;
            }
        }
    }

    No *esquerda = pesquisarPorNumero(raiz->esquerda, cidade, estado, numero);
    if (esquerda != NULL) return esquerda;  // Encontrou o candidato na subárvore esquerda

    return pesquisarPorNumero(raiz->direita, cidade, estado, numero);
}



void mostrarTodosCandidatosPorEstado(No *raiz, const char *estado) {
    if (raiz != NULL) {
        // Percorre a subárvore esquerda
        mostrarTodosCandidatosPorEstado(raiz->esquerda, estado);

        // Verifica se o estado do nó atual corresponde ao estado desejado
        if (strcmp(raiz->candidato.estado, estado) == 0) {
            mostrarInformacoesNo(raiz);  // Mostra as informações do nó
        }

        // Percorre a subárvore direita
        mostrarTodosCandidatosPorEstado(raiz->direita, estado);
    }
}

void mostrarTodosCandidatosPorCidade(No* raiz, char *estado, char *cidade){
    if (raiz != NULL) {
        // Percorre a subárvore esquerda
        mostrarTodosCandidatosPorCidade(raiz->esquerda, estado, cidade);

        // Verifica se o estado do nó atual corresponde ao estado desejado
        if (strcmp(raiz->candidato.cidade, cidade) == 0) {
            mostrarInformacoesNo(raiz);  // Mostra as informações do nó
        }

        // Percorre a subárvore direita
        mostrarTodosCandidatosPorCidade(raiz->direita, estado, cidade);
    }
}
void mostrarInformacoesNo(No *no) {
    if (no != NULL) {
        printf("Nome: %s\n", no->candidato.nome);
        printf("Estado: %s\n", no->candidato.estado);
        printf("Cidade: %s\n", no->candidato.cidade);
        printf("Numero: %s\n", no->candidato.numero);
        printf("Cargo: %s\n", no->candidato.cargo);
        printf("Nome na Urna: %s\n", no->candidato.nomeUrna);
        printf("Sigla do Partido: %s\n", no->candidato.siglaPartido);
        printf("Genero: %s\n", no->candidato.genero);
        printf("Grau de Instrucao: %s\n", no->candidato.grauInstrucao);
        printf("Cor/Raca: %s\n", no->candidato.corRaca);
        printf("------------------------------------\n");
    } else {
        printf("No vazio!\n");
    }
}

void mostrarInformacoesAdicionaisNo(No* no, int opcaoDesejada){

    // opcaoDesejada = 1 -> genero
    // opcaoDesejada = 2 -> partido
    // opcaoDesejada = 3 -> cor/raca

    if(no != NULL){
        switch (opcaoDesejada)
        {
            case 1:
                printf("ENTROU NO CASE 1\n");
                printf("Genero: %s\n", no->candidato.genero);
                break;
            case 2:
                printf("Partido: %s\n", no->candidato.siglaPartido);
                break;
            case 3:
                printf("Cor/Raca: %s\n", no->candidato.corRaca);
                break;
            default:
                break;
        }
    } else {
        printf("ERRO! No vazio");
    }
}



void imprimirEmOrdem(No *raiz) {
    if (raiz != NULL) {
        imprimirEmOrdem(raiz->esquerda);  // Percorre a subárvore esquerda
        // Imprime os dados do candidato
        printf("Estado: %s, Cidade: %s, Número: %s, Cargo: %s, Nome: %s, Nome na Urna: %s, Sigla: %s, Gênero: %s, Grau: %s, Cor: %s\n", 
               raiz->candidato.estado, raiz->candidato.cidade, raiz->candidato.numero, 
               raiz->candidato.cargo, raiz->candidato.nome, raiz->candidato.nomeUrna, 
               raiz->candidato.siglaPartido, raiz->candidato.genero, 
               raiz->candidato.grauInstrucao, raiz->candidato.corRaca);
        imprimirEmOrdem(raiz->direita);   // Percorre a subárvore direita
    }
}

void imprimirArvore(No *raiz, int nivel) {
    if (raiz == NULL) {
        return;
    }

    // Primeiro imprime o filho direito
    imprimirArvore(raiz->direita, nivel + 1);
    
    // Imprime o nó atual
    for (int i = 0; i < nivel; i++) {
        printf("    ");  // Indenta para mostrar o nível
    }
    printf("%s\n", raiz->candidato.numero);  // Imprime o número do candidato como referência

    // Depois imprime o filho esquerdo
    imprimirArvore(raiz->esquerda, nivel + 1);
}

void mostrarCorRacaEstado(No *raiz, const char *estado, const char *cor) {
    if (raiz != NULL) {
        // Percorre a subárvore esquerda
        mostrarCorRacaEstado(raiz->esquerda, estado, cor);

        // Verifica se o estado do nó atual corresponde ao estado desejado
        // e se a cor/raca do candidato corresponde à cor/raca desejada
        if (strcmp(raiz->candidato.estado, estado) == 0 && 
            strcmp(raiz->candidato.corRaca, cor) == 0) {
            mostrarInformacoesNo(raiz);  // Mostra as informações do nó
        }

        // Percorre a subárvore direita
        mostrarCorRacaEstado(raiz->direita, estado, cor);
    }
}

void mostrarGeneroEstado(No *raiz, const char *estado, const char *genero) {
    if (raiz != NULL) {
        // Percorre a subárvore esquerda
        mostrarGeneroEstado(raiz->esquerda, estado, genero);

        // Verifica se o estado do nó atual corresponde ao estado desejado
        // e se a cor/raca do candidato corresponde à cor/raca desejada
        if (strcmp(raiz->candidato.estado, estado) == 0 && 
            strcmp(raiz->candidato.genero, genero) == 0) {
            mostrarInformacoesNo(raiz);  // Mostra as informações do nó
        }

        // Percorre a subárvore direita
        mostrarGeneroEstado(raiz->direita, estado, genero);
    }
}

void mostrarPartidoEstado(No *raiz, const char *estado, const char *partido) {
    if (raiz != NULL) {
        // Percorre a subárvore esquerda
        mostrarPartidoEstado(raiz->esquerda, estado, partido);

        // Verifica se o estado do nó atual corresponde ao estado desejado
        // e se a cor/raca do candidato corresponde à cor/raca desejada
        if (strcmp(raiz->candidato.estado, estado) == 0 && 
            strcmp(raiz->candidato.siglaPartido, partido) == 0) {
            mostrarInformacoesNo(raiz);  // Mostra as informações do nó
        }

        // Percorre a subárvore direita
        mostrarPartidoEstado(raiz->direita, estado, partido);
    }
}

// Função para mostrar candidatos de uma certa cor que estejam presentes em uma dada cidade e estado
void mostrarCorCidade(No *raiz, const char *estado, const char *cidade, const char *cor) {
    if (raiz != NULL) {
        // Percorre a subárvore esquerda
        mostrarCorCidade(raiz->esquerda, estado, cidade, cor);

        // Verifica se o estado e a cidade do nó atual correspondem aos desejados
        // e se a cor do candidato corresponde à cor desejada
        if (strcmp(raiz->candidato.estado, estado) == 0 && 
            strcmp(raiz->candidato.cidade, cidade) == 0 && 
            strcmp(raiz->candidato.corRaca, cor) == 0) {
            mostrarInformacoesNo(raiz);  // Mostra as informações do nó
        }

        // Percorre a subárvore direita
        mostrarCorCidade(raiz->direita, estado, cidade, cor);
    }
}

void mostrarGeneroCidade(No *raiz, const char *estado, const char *cidade, const char *genero) {
    if (raiz != NULL) {
        // Percorre a subárvore esquerda
        mostrarGeneroCidade(raiz->esquerda, estado, cidade, genero);

        // Verifica se o estado e a cidade do nó atual correspondem aos desejados
        // e se a cor do candidato corresponde à cor desejada
        if (strcmp(raiz->candidato.estado, estado) == 0 && 
            strcmp(raiz->candidato.cidade, cidade) == 0 && 
            strcmp(raiz->candidato.genero, genero) == 0) {
            mostrarInformacoesNo(raiz);  // Mostra as informações do nó
        }

        // Percorre a subárvore direita
        mostrarGeneroCidade(raiz->direita, estado, cidade, genero);
    }
}

void mostrarPartidoCidade(No *raiz, const char *estado, const char *cidade, const char *partido) {
    if (raiz != NULL) {
        // Percorre a subárvore esquerda
        mostrarPartidoCidade(raiz->esquerda, estado, cidade, partido);

        // Verifica se o estado e a cidade do nó atual correspondem aos desejados
        // e se a cor do candidato corresponde à cor desejada
        if (strcmp(raiz->candidato.estado, estado) == 0 && 
            strcmp(raiz->candidato.cidade, cidade) == 0 && 
            strcmp(raiz->candidato.siglaPartido, partido) == 0) {
            mostrarInformacoesNo(raiz);  // Mostra as informações do nó
        }

        // Percorre a subárvore direita
        mostrarPartidoCidade(raiz->direita, estado, cidade, partido);
    }
}


