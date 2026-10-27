#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

#include "pesquisaBinaria.h"
#include "arvoreBinaria.h"
#include "arvoreAVL.h"
#include "estruturas.h"


#define MAX_LINE_LENGTH 256
#define TOTAL_CANDIDATOS 500000


void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }  
}

double calculaTempo(clock_t inicioClock){
    clock_t fim = clock();
    double tempo = ((double)(fim - inicioClock)) / CLOCKS_PER_SEC;
    return tempo;

}
// Função para calcular o logaritmo base 2
double calcularLog(int n) {
    return log(n) / log(2); // log base 2
}

// Função para verificar o equilíbrio da árvore AVL
void verificarEquilibrioAVL(No* raizAVL) {
    int n = contarNos(raizAVL);  
    int alturaAtual = altura(raizAVL);  
    double limite = 1.44 * calcularLog(n);  // Limite para altura

    printf("\nVerificação de Equilíbrio da Árvore AVL:\n");
    printf("Número de nós: %d\n", n);
    printf("Altura atual: %d\n", alturaAtual);
    printf("Limite de altura (1.44 * log(n)): %.2f\n", limite);

    if (alturaAtual <= limite) {
        printf("A árvore AVL está balanceada.\n");
    } else {
        printf("A árvore AVL NÃO está balanceada.\n");
    }
}

EstruturaAux *criarEstruturaAux(int capacidade) {
    EstruturaAux *aux = malloc(sizeof(EstruturaAux));
    aux->candidatos = malloc(capacidade * sizeof(Candidato));
    aux->tamanho = 0;
    aux->capacidade = capacidade;
    return aux;
}

int lerArquivo(const char *nomeArquivo, EstruturaAux *aux) {
    setlocale(LC_ALL, "");  // UTF-8 para caracteres especiais

    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", nomeArquivo);
        return -1;
    }

    char linha[MAX_LINE_LENGTH];
    fgets(linha, sizeof(linha), arquivo);  // Ignorar o cabeçalho

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (aux->tamanho >= aux->capacidade) {
            printf("Capacidade da estrutura auxiliar excedida.\n");
            break;
        }

        linha[strcspn(linha, "\n")] = '\0';  // Remover '\n'

        Candidato candidato;
        char *token = strtok(linha, ";");
        if (token != NULL) strcpy(candidato.estado, token);
        token = strtok(NULL, ";");
        if (token != NULL) strcpy(candidato.cidade, token);
        token = strtok(NULL, ";");
        if (token != NULL) strcpy(candidato.numero, token);
        token = strtok(NULL, ";");
        if (token != NULL) strcpy(candidato.cargo, token);
        token = strtok(NULL, ";");
        if (token != NULL) strcpy(candidato.nome, token);
        token = strtok(NULL, ";");
        if (token != NULL) strcpy(candidato.nomeUrna, token);
        token = strtok(NULL, ";");
        if (token != NULL) strcpy(candidato.siglaPartido, token);
        token = strtok(NULL, ";");
        if (token != NULL) strcpy(candidato.genero, token);
        token = strtok(NULL, ";");
        if (token != NULL) strcpy(candidato.grauInstrucao, token);
        token = strtok(NULL, ";");
        if (token != NULL) strcpy(candidato.corRaca, token);

        aux->candidatos[aux->tamanho++] = candidato;
    }

    fclose(arquivo);
    return 1;  // Sucesso
}

void carregaEstruturaVetor(Candidato *vetorCandidatos, EstruturaAux *aux, int *tam) {
    if (vetorCandidatos != NULL && aux != NULL && aux->candidatos != NULL) {
        memcpy(vetorCandidatos, aux->candidatos, aux->tamanho * sizeof(Candidato));
        *tam = aux->tamanho;
    } else {
        printf("Erro: Ponteiro nulo passado para carregaEstruturaVetor.\n");
    }
}

void carregaEstruturaAVL(No **raizAVL, EstruturaAux *aux) {
    for (int i = 0; i < aux->tamanho; i++) {
        *raizAVL = inserirNoAVL(*raizAVL, aux->candidatos[i]);
    }
}

void carregaEstruturaABB(No **raizABB, EstruturaAux *aux) {
    for (int i = 0; i < aux->tamanho; i++) {
        *raizABB = inserirNo(*raizABB, aux->candidatos[i]);
    }
}


int main() 
{
    setlocale(LC_ALL, "");
    No *raizAVL = NULL; 
    No *raizABB = NULL;            
    Candidato *vetorC = malloc(500000 * sizeof(Candidato));  
    int tam = 0;
    char nomeArq[30];

    EstruturaAux *estruturaAux = criarEstruturaAux(500000);
    while (1) 
    { 
        printf("Informe o nome do arquivo. EX: eleicoes2024.CSV: ");
        fgets(nomeArq, sizeof(nomeArq), stdin);
        // Remove o '\n' que o fgets armazena no final da string
        nomeArq[strcspn(nomeArq, "\n")] = 0;

        if(lerArquivo(nomeArq, estruturaAux) == 1){
            printf("ARQUIVO LIDO COM SUCESSO!!\n");
            break;
        } else {
            printf("ERRO AO LER ARQUIVO!\n");
        }
    
    }

    //carregamento do vetor para pesquisa binaria (com ordenação)
    clock_t inicioCarregamentoVetor = clock();
    carregaEstruturaVetor(vetorC, estruturaAux, &tam);
    shellSort(vetorC, tam);
    double tempoCarregamentoVetor = calculaTempo(inicioCarregamentoVetor);

    //carregando estrutura ABB
    clock_t inicioCarregamentoABB = clock();
    carregaEstruturaABB(&raizABB, estruturaAux);
    double tempoCarregamentoABB = calculaTempo(inicioCarregamentoABB);

    //carregando AVL
    clock_t inicioCarregamentoAVL = clock();
    carregaEstruturaAVL(&raizAVL, estruturaAux);
    double tempoCarregamentoAVL = calculaTempo(inicioCarregamentoAVL);

    int opcao = 0, opcaoGeral = 0, opcaoFiltro = 0, inicio, fim;
    char estado[3];
    char cidade[100];
    char numero[10];
    char genero[10];
    char partido[10];
    char raca[10];

    printf("\n----------- TEMPO PARA CARREGAR CADA UMA DAS ESTRUTURAS DE DADOS -----------\n");
    printf("Pesquisa Binária = %2lf segundos\n ", tempoCarregamentoVetor);
    printf("ABB sem balanceamento = %2lf segundos\n", tempoCarregamentoABB);
    printf("Árvore AVL = %2lf segundos\n", tempoCarregamentoAVL);

    do {
        printf("\nMENU INTERATIVO:\n");
        printf("0. Realizar verificações em [Pesquisa Binária]\n");
        printf("1. Realizar verificações na [ABB sem balanceamento]\n");
        printf("2. Realizar verificações na [Árvore AVL]\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) 
        {

            case 0:
                do {
                    printf("\n=== MENU PRINCIPAL ===\n");
                    printf("0. Filtrar por Estado\n");
                    printf("1. Filtrar por Cidade\n");
                    printf("2. Filtrar por Número\n");
                    printf("3. Sair\n");
                    printf("Escolha uma opção: ");
                    scanf("%d", &opcaoGeral);
                    printf("\n");

                    switch (opcaoGeral) {
                        
                         // Submenu de filtro por Estado
                        case 0:
                           
                            printf("\nDigite o estado (sigla de 2 letras): ");
                            limparBuffer();
                            scanf("%s", estado);
                            
                            // Busca, no conjunto de dados, o subconjunto de dados que correspondem ao Estado desejado baseado nos seus limites.
                            inicio = buscaBinariaEstadoBaixo(vetorC, tam, estado);
                            fim = buscaBinariaEstadoCima(vetorC, tam, estado);
                            
                            // Inicio do contador de tempo para calcular o tempo de execução do caso
                            

                            // Checagem de caso onde candidado não existe no vetor, exemplo: estado KK
                            if (inicio == -1 || fim == -1) {
                                printf("Nenhum candidato encontrado para o estado %s.\n", estado);
                                break;
                            }

                            // Submenu do filtro de casos extras por Estado
                            do {
                                printf("\n=== FILTRAR POR ESTADO ===\n");
                                printf("0. Mostrar Geral\n");
                                printf("1. Filtrar por Cor/Raça\n");
                                printf("2. Filtrar por Gênero\n");
                                printf("3. Filtrar por Partido\n");
                                printf("4. Voltar\n");
                                printf("Escolha uma opção: ");
                                scanf("%d", &opcaoFiltro);
                                printf("\n");

                                switch (opcaoFiltro) {
                                    case 0:{
                                        clock_t inicioEstadoVetor = clock();
                                        mostrarCandidato(vetorC, inicio, fim, tam);
                                        printf("Tempo de processamento para consulta: %lf", calculaTempo(inicioEstadoVetor));
                                        break;
                                    }
                                    case 1:{
                                        printf("Digite a cor/raça: ");
                                        limparBuffer();
                                        scanf("%s", raca);
                                        clock_t inicioCandidatoCor = clock();
                                        mostrarCandidatoCorRaca(vetorC, inicio, fim, raca, tam);
                                        printf("Tempo de processamento para consulta: %lf", calculaTempo(inicioCandidatoCor));
                                        break;
                                    }
                                        
                                    case 2:{
                                        printf("Digite o gênero: ");
                                        limparBuffer();
                                        scanf("%s", genero);
                                        clock_t inicioCandidatoGenero = clock();
                                        mostrarCandidatoGenero(vetorC, inicio, fim, genero, tam);
                                        printf("Tempo de processamento para consulta: %lf", calculaTempo(inicioCandidatoGenero));
                                        break;
                                    }
                                    case 3:{
                                        printf("Digite a sigla do partido: ");
                                        limparBuffer();
                                        scanf("%s", partido);
                                        clock_t inicioCandidatoPartido = clock();
                                        mostrarCandidatoPartido(vetorC, inicio, fim, partido, tam);
                                        printf("Tempo de processamento para consulta: %lf", calculaTempo(inicioCandidatoPartido));
                                        break;
                                    }
                                    case 4:
                                        break;
                                    default:
                                        printf("Opção inválida!\n");
                                }
                            } while (opcaoFiltro != 4);

                            printf("\nForam mostrados os candidatos do Estado (%s).\n", estado);

                            break;

                        // Submenu de filtro por Cidade
                        case 1:
                            
                            printf("\nDigite o estado (sigla de 2 letras): ");
                            limparBuffer();
                            scanf("%s", estado);
                            printf("Digite a cidade: ");
                            limparBuffer();
                            scanf("%[^\n]s", cidade);
                            
                            // Busca, no conjunto de dados, o subconjunto de dados que correspondem ao Estado e Cidade desejado baseado nos seus limites.
                            inicio = buscaBinariaCidadeBaixo(vetorC, tam, estado, cidade);
                            fim = buscaBinariaCidadeCima(vetorC, tam, estado, cidade);

                            // Checagem de caso onde candidado não existe no vetor, exemplo: cidade AAAAAA
                            if (inicio == -1 || fim == -1) {
                                printf("Nenhum candidato encontrado para a cidade %s.\n", cidade);
                                break;
                            }

                            // Submenu do filtro de casos extras por Estado e Cidade
                            do {
                                printf("\n=== FILTRAR POR CIDADE ===\n");
                                printf("0. Mostrar Geral\n");
                                printf("1. Filtrar por Cor/Raça\n");
                                printf("2. Filtrar por Gênero\n");
                                printf("3. Filtrar por Partido\n");
                                printf("4. Voltar\n");
                                printf("Escolha uma opção: ");
                                scanf("%d", &opcaoFiltro);
                                printf("\n");

                                switch (opcaoFiltro) {
                                    case 0:{
                                        clock_t inicioCandidatoCidade = clock();
                                        mostrarCandidato(vetorC, inicio, fim, tam);
                                        printf("Tempo de processamento para consulta: %lf", calculaTempo(inicioCandidatoCidade));
                                        break;
                                    }
                                    case 1:{
                                        printf("Digite a cor/raça: ");
                                        limparBuffer();
                                        scanf("%s", raca);
                                        clock_t inicioCandidatoCor = clock();
                                        mostrarCandidatoCorRaca(vetorC, inicio, fim, raca, tam);
                                        printf("Tempo de processamento para consulta: %lf", calculaTempo(inicioCandidatoCor));
                                        break;
                                    }
                                    case 2:{
                                        printf("Digite o gênero: ");
                                        limparBuffer();
                                        scanf("%s", genero);
                                        clock_t inicioCandidatoGenero = clock();
                                        mostrarCandidatoGenero(vetorC, inicio, fim, genero, tam);
                                        printf("Tempo de processamento para consulta: %lf", calculaTempo(inicioCandidatoGenero));
                                        break;
                                    }
                                    case 3:{
                                        printf("Digite a sigla do partido: ");
                                        limparBuffer();
                                        scanf("%s", partido);
                                        clock_t inicioCandidatoPartido = clock();
                                        mostrarCandidatoPartido(vetorC, inicio, fim, partido, tam);
                                        printf("Tempo de processamento para consulta: %lf", calculaTempo(inicioCandidatoPartido));
                                        break;
                                    }
                                    case 4:
                                        break;
                                    default:
                                        printf("Opção inválida!\n");
                                }
                            } while (opcaoFiltro != 4);
                            break;

                        // Submenu de filtro por Número
                        case 2:
                            
                            printf("\nDigite o estado (sigla de 2 letras): ");
                            limparBuffer();
                            scanf("%s", estado);
                            printf("Digite a cidade: ");
                            limparBuffer();
                            scanf("%[^\n]s", cidade);
                            printf("Digite o número: ");
                            limparBuffer();
                            scanf("%s", numero);
                            
                            // Busca, no conjunto de dados, o subconjunto de dados que correspondem ao Estado, Cidade e Número desejado baseado nos seus limites.
                            inicio = fim = buscaBinariaNumero(vetorC, tam, estado, cidade, numero);

                            // Checagem de caso onde candidado não existe no vetor, exemplo: número 0000
                            if (inicio == -1) {
                                printf("Nenhum candidato encontrado com o número %s.\n", numero);
                                break;
                            }

                            clock_t inicioCandidatoNumero = clock();
                            mostrarCandidato(vetorC, inicio, fim, tam);
                            printf("Tempo de processamento para consulta: %lf", calculaTempo(inicioCandidatoNumero));
                            
                            break;

                        case 3:
                            printf("\nSaindo do programa...\n");
                            break;

                        default:
                            printf("Opção inválida!\n");
                    }
                } while (opcaoGeral != 3);

                break;

            case 1:
                // Código para ABB sem balanceamento
                do
                {
                    printf("\n=== MENU PRINCIPAL ===\n");
                    printf("0. Filtrar por Estado\n");
                    printf("1. Filtrar por Cidade\n");
                    printf("2. Filtrar por Número\n");
                    printf("3. Sair\n");
                    printf("Escolha uma opção: ");
                    scanf("%d", &opcaoGeral);
                    printf("\n");

                    switch (opcaoGeral)
                    {
                        case 0:
                            printf("\nDigite o estado (sigla de 2 letras): ");
                            limparBuffer();
                            scanf("%s", estado);

                            do {
                                    printf("\n=== FILTRAR POR ESTADO ===\n");
                                    printf("0. Mostrar Geral\n");
                                    printf("1. Filtrar por Cor/Raça\n");
                                    printf("2. Filtrar por Gênero\n");
                                    printf("3. Filtrar por Partido\n");
                                    printf("4. Voltar\n");
                                    printf("Escolha uma opção: ");
                                    scanf("%d", &opcaoFiltro);
                                    printf("\n");

                                    switch (opcaoFiltro) {
                                        case 0:{
                                            clock_t inicioCandidatosEstado = clock();
                                            mostrarTodosCandidatosPorEstado(raizABB, estado);
                                            printf("Tempo de processamento para consulta: %lf", calculaTempo(inicioCandidatosEstado));
                                            break;
                                        }
                                            
                                        case 1:{
                                            printf("Digite a cor/raça (PARDA/BRANCA/AMARELA/PRETA): ");
                                            limparBuffer();
                                            scanf("%s", raca);
                                            clock_t inicioCorEstado = clock();
                                            mostrarCorRacaEstado(raizABB, estado, raca);
                                            printf("Tempo de processamento para consulta: %lf", calculaTempo(inicioCorEstado));
                                            break;
                                        }
                                        case 2:{
                                            printf("Digite o gênero: ");
                                            limparBuffer();
                                            scanf("%s", genero);
                                            clock_t inicioGeneroEstado = clock();
                                            mostrarGeneroEstado(raizABB, estado, genero);
                                            printf("Tempo de processamento para consulta: %lf", calculaTempo(inicioGeneroEstado));
                                            break;
                                        }
                                        case 3:{
                                            printf("Digite a sigla do partido: ");
                                            limparBuffer();
                                            scanf("%s", partido);
                                            clock_t inicioPartidoEstado = clock();
                                            mostrarPartidoEstado(raizABB, estado, partido);
                                            printf("Tempo de processamento para consulta: %lf", calculaTempo(inicioPartidoEstado));
                                            break;
                                        } 
                                        case 4:
                                            break;
                                        default:
                                            printf("Opção inválida!\n");
                                    }
                            } while (opcaoFiltro != 4);

                            break;
                        case 1:
                            printf("\nDigite o estado (sigla de 2 letras): ");
                            limparBuffer();
                            scanf("%s", estado);
                            printf("Digite a cidade: ");
                            limparBuffer();
                            scanf("%[^\n]s", cidade);

                            do {
                                printf("\n=== FILTRAR POR CIDADE ===\n");
                                printf("0. Mostrar Geral\n");
                                printf("1. Filtrar por Cor/Raça\n");
                                printf("2. Filtrar por Gênero\n");
                                printf("3. Filtrar por Partido\n");
                                printf("4. Voltar\n");
                                printf("Escolha uma opção: ");
                                scanf("%d", &opcaoFiltro);
                                printf("\n");

                                switch (opcaoFiltro) {
                                    case 0:{
                                        clock_t inicioCandidatosCidade = clock();
                                        mostrarTodosCandidatosPorCidade(raizABB, estado, cidade);
                                        printf("Tempo de processamento para consulta: %lf", calculaTempo(inicioCandidatosCidade));
                                        break;
                                    }
                                        
                                    case 1:{
                                        printf("Digite a cor/raça: ");
                                        limparBuffer();
                                        scanf("%s", raca);
                                        clock_t inicioCorCidade = clock();
                                        mostrarCorCidade(raizABB, estado, cidade, raca);
                                        printf("Tempo de processamento para consulta: %lf", calculaTempo(inicioCorCidade));
                                        break;
                                    }
                                        
                                    case 2:{
                                        printf("Digite o gênero: ");
                                        limparBuffer();
                                        scanf("%s", genero);
                                        clock_t inicioGeneroCidade = clock();
                                        mostrarGeneroCidade(raizABB, estado, cidade, genero);
                                        printf("Tempo de processamento para consulta: %lf", calculaTempo(inicioGeneroCidade));
                                        break;
                                    }
                                    case 3:{
                                        printf("Digite a sigla do partido: ");
                                        limparBuffer();
                                        scanf("%s", partido);
                                        clock_t inicioPartidoCidade = clock();
                                        mostrarPartidoCidade(raizABB, estado, cidade, partido);
                                        printf("Tempo de processamento para consulta: %lf", calculaTempo(inicioPartidoCidade));
                                        break;
                                    }
                                    case 4:
                                        break;
                                    default:
                                        printf("Opção inválida!\n");
                                }
                            } while (opcaoFiltro != 4);
                            break;
                        case 2:{
                            printf("\nDigite o estado (sigla de 2 letras): ");
                            limparBuffer();
                            scanf("%s", estado);
                            printf("Digite a cidade: ");
                            limparBuffer();
                            scanf("%[^\n]s", cidade);
                            printf("Digite o número: ");
                            limparBuffer();
                            scanf("%s", numero);

                            clock_t inicioCandidatoNumero = clock();
                            mostrarInformacoesNo(pesquisarPorNumero(raizABB, cidade, estado, numero));
                            printf("Tempo de processamento para consulta: %lf", calculaTempo(inicioCandidatoNumero));
                            break;
                        }
                            
                        case 3:
                            break;
                        default:
                            printf("Opcao invalida!");
                            break;
                    }  
                } while (opcaoGeral != 3 && opcaoGeral != 2);
                //Não faz sentido perguntar ao usuario sobre listagem adicionais de genero, cor e partido se a pesquisa é feita por numero. Como o numero é unico, o resultado de sua pesquisa é o único com aquela cor, genero partido e numero.
                break;

            case 2:
                verificarEquilibrioAVL(raizAVL);

                do
                {
                    printf("\n=== MENU PRINCIPAL ===\n");
                    printf("0. Filtrar por Estado\n");
                    printf("1. Filtrar por Cidade\n");
                    printf("2. Filtrar por Número\n");
                    printf("3. Sair\n");
                    printf("Escolha uma opção: ");
                    scanf("%d", &opcaoGeral);
                    printf("\n");

                    switch (opcaoGeral)
                    {
                        case 0:
                            printf("\nDigite o estado (sigla de 2 letras): ");
                            limparBuffer();
                            scanf("%s", estado);

                            do {
                                    printf("\n=== FILTRAR POR ESTADO ===\n");
                                    printf("0. Mostrar Geral\n");
                                    printf("1. Filtrar por Cor/Raça\n");
                                    printf("2. Filtrar por Gênero\n");
                                    printf("3. Filtrar por Partido\n");
                                    printf("4. Voltar\n");
                                    printf("Escolha uma opção: ");
                                    scanf("%d", &opcaoFiltro);
                                    printf("\n");

                                    switch (opcaoFiltro) {
                                        case 0:{
                                            clock_t inicioEstado = clock();
                                            bool encontrou;

                                            if (!encontrou) {
                                                printf("\n\nESTADO NÃO ENCONTRADO!!!!\n\n");
                                                break;
                                            }
                                            mostrarTodosCandidatosPorEstadoAVL(raizAVL, estado, &encontrou);
                                            printf("Tempo de processamento para consulta: %lf", calculaTempo(inicioEstado));
                                            break;
                                        }
                                            
                                        case 1:{
                                            printf("Digite a cor/raça (PARDA/BRANCA/AMARELA/PRETA): ");
                                            limparBuffer();
                                            scanf("%s", raca);
                                            clock_t inicioCorEstado = clock();
                                            buscaRacaPorEstadoAVL(raizAVL, estado, raca);
                                            printf("Tempo de processamento para consulta: %lf", calculaTempo(inicioCorEstado));
                                            break;
                                        }
                                        case 2:{
                                            printf("Digite o gênero: ");
                                            limparBuffer();
                                            scanf("%s", genero);
                                            clock_t inicioGeneroEstado = clock();
                                            buscaGeneroPorEstadoAVL(raizAVL, estado, genero);
                                            printf("Tempo de processamento para consulta: %lf", calculaTempo(inicioGeneroEstado));
                                            break;
                                        }
                                        case 3:{
                                            printf("Digite a sigla do partido: ");
                                            limparBuffer();
                                            scanf("%s", partido);
                                            clock_t inicioPartidoEstado = clock();
                                            buscaPartidoPorEstadoAVL(raizAVL, estado, partido);
                                            printf("Tempo de processamento para consulta: %lf", calculaTempo(inicioPartidoEstado));
                                            break;
                                        } 
                                        case 4:
                                            break;
                                        default:
                                            printf("Opção inválida!\n");
                                    }
                            } while (opcaoFiltro != 4);
                            break;
                        case 1:
                            printf("\nDigite o estado (sigla de 2 letras): ");
                            limparBuffer();
                            scanf("%s", estado);
                            printf("Digite a cidade: ");
                            limparBuffer();
                            scanf("%[^\n]s", cidade);

                            do {
                                printf("\n=== FILTRAR POR CIDADE ===\n");
                                printf("0. Mostrar Geral\n");
                                printf("1. Filtrar por Cor/Raça\n");
                                printf("2. Filtrar por Gênero\n");
                                printf("3. Filtrar por Partido\n");
                                printf("4. Voltar\n");
                                printf("Escolha uma opção: ");
                                scanf("%d", &opcaoFiltro);
                                printf("\n");

                                switch (opcaoFiltro) {
                                    case 0:{
                                        clock_t inicioCandidatosCidade = clock();
                                        mostrarTodosCandidatosPorCidadeAVL(raizABB, estado, cidade);
                                        printf("Tempo de processamento para consulta: %lf", calculaTempo(inicioCandidatosCidade));
                                        break;
                                    }
                                        
                                    case 1:{
                                        printf("Digite a cor/raça: ");
                                        limparBuffer();
                                        scanf("%s", raca);
                                        clock_t inicioCorCidade = clock();
                                        buscaRacaPorCidadeAVL(raizAVL, estado, cidade, raca);
                                        printf("Tempo de processamento para consulta: %lf", calculaTempo(inicioCorCidade));
                                        break;
                                    }
                                        
                                    case 2:{
                                        printf("Digite o gênero: ");
                                        limparBuffer();
                                        scanf("%s", genero);
                                        clock_t inicioGeneroCidade = clock();
                                        buscaGeneroPorCidadeAVL(raizAVL, estado, cidade, genero);
                                        printf("Tempo de processamento para consulta: %lf", calculaTempo(inicioGeneroCidade));
                                        break;
                                    }
                                    case 3:{
                                        printf("Digite a sigla do partido: ");
                                        limparBuffer();
                                        scanf("%s", partido);
                                        clock_t inicioPartidoCidade = clock();
                                        buscaPartidoPorCidadeAVL(raizAVL, estado, cidade, partido);
                                        printf("Tempo de processamento para consulta: %lf", calculaTempo(inicioPartidoCidade));
                                        break;
                                    }
                                    case 4:
                                        break;
                                    default:
                                        printf("Opção inválida!\n");
                                }
                            } while (opcaoFiltro != 4);
                            break;
                        case 2:{
                            printf("\nDigite o estado (sigla de 2 letras): ");
                            limparBuffer();
                            scanf("%s", estado);
                            printf("Digite a cidade: ");
                            limparBuffer();
                            scanf("%[^\n]s", cidade);
                            printf("Digite o número: ");
                            limparBuffer();
                            scanf("%s", numero);

                            clock_t inicioCandidatoNumero = clock();
                            mostrarInformacoesNoAVL(pesquisarPorNumeroAVL(raizAVL, cidade, estado, numero));
                            printf("Tempo de processamento para consulta: %lf", calculaTempo(inicioCandidatoNumero));
                            break;
                        }
                        case 3:
                            break;
                        default:
                            printf("Opcao inválida!\n");
                            break;
                    }   
                } while(opcaoGeral != 3 && opcaoGeral != 2);

        }
                
    } while (opcao != 3);

    printf("Programa encerrado!\n");

    free(vetorC);  

    return 0;
}
