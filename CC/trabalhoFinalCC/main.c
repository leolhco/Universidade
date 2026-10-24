#include <stdio.h>
#include <string.h>
#include "lexico.h"
#include "sintatico.h"

//execuçao do lexico
static void lexico(const char *arquivo) {
    lex_inicializa(arquivo);

    printf("%-15s %-18s %-26s %s\n", "TOKEN", "LEXEMA", "ATRIBUTO", "POSICAO (lin,col)");
    printf("--------------------------------------------------------------------------\n");

    Token t;
    do {
        t = proximo_token();

        char attr[64] = "-";
        if (t.tem_atributo) {
            switch (t.tipo) {
                case TK_ID:
                    snprintf(attr, sizeof attr, "TS[%d]", t.atributo.pos_ts);
                    break;
                case TK_NUM_INT:
                    snprintf(attr, sizeof attr, "%ld", t.atributo.num_int);
                    break;
                case TK_NUM_FLOAT:
                    snprintf(attr, sizeof attr, "%g", t.atributo.num_float);
                    break;
                case TK_CHAR_CONST:
                    snprintf(attr, sizeof attr, "'%c'", t.atributo.char_const);
                    break;
                default:
                    break;
            }
        }
        printf("%-15s %-18s %-26s (%d,%d)\n",
               nome_token(t.tipo), t.lexema, attr, t.linha, t.coluna);

    } while (t.tipo != TK_EOF);

    imprime_tabela_simbolos();

    int erros = lex_total_erros();
    if (erros > 0)
        fprintf(stderr, "\nAnalise lexica concluida com %d erro(s).\n", erros);
    else
        printf("\nAnalise lexica concluida sem erros.\n");

    lex_finaliza();
}

// execuçao do sintatico
static void sintatico(const char *arquivo) {
    lex_inicializa(arquivo);        
    NoArvore *raiz = analisar();    

    int erros = sint_total_erros();
    if (erros == 0) {
        imprime_arvore(raiz);
        printf("\nAnalise sintatica concluida sem erros.\n");
    } else {
        fprintf(stderr, "\nAnalise sintatica concluida com %d erro(s).\n", erros);
    }

    libera_arvore(raiz);
    lex_finaliza();
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s [OPCAO] <arquivo-fonte>\n", argv[0]);
        fprintf(stderr, "-t : exibe a tabela de transicao do lexer\n");
        fprintf(stderr, "-l <arquivo> : exibe os tokens (apenas analise lexica)\n");
        fprintf(stderr, "<arquivo> : executa a analise sintatica completa (padrao)\n");
        return 1;
    }

    if (strcmp(argv[1], "-t") == 0) {
        lex_inicializa("/dev/null");   
        imprime_tabela_transicao();
        lex_finaliza();
        return 0;
    }

    if (strcmp(argv[1], "-l") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Erro: a opcao -l requer um arquivo-fonte.\n");
            return 1;
        }
        lexico(argv[2]);
        return 0;
    }

    sintatico(argv[1]);
    return 0;
    //compilaçao = gcc *.c -o analisador
    //execuçao = ./compilador teste.txt
}