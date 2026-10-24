#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lex.h"


Token *proximo_token() {
    return yylex();
}

// Mostrar o token retornado pelo analisador lexico
void imprime_token(Token *tok) {
    switch(tok->tipo) {
        
        // LEXEMA
        case TOK_COMENTARIO:
        case TOK_SEPARADOR:
        case TOK_ID:
        case TOK_NUM_INT:
        case TOK_NUM_FLOAT:
            printf("%s", tok->atributo);
            break;
            
        
        case TOK_PARESQ: printf("("); break;
        case TOK_PARDIR: printf(")"); break;
        
        // RELOP
        case TOK_RELOP:
            if (strcmp(tok->atributo, "=") == 0) {
                printf("==");
            } else {
                printf("%s", tok->atributo);
            }
            break;
            
        // Atribuição
        case TOK_ATRIB: 
            printf("="); 
            break;
        
        // Delimitador de bloco
        case TOK_INI: 
            printf("{"); 
            break;
        
        //  Delimitador de bloco
        case TOK_FIM: 
            printf("}"); 
            break;
        
        // Palavra reservada
        case TOK_SE: 
            printf("if"); 
            break;

        // Palavra reservada    
        case TOK_SENAO:
            printf("else");
            break;
        
        // Palavra reservada    
        case TOK_ENQUANTO: 
            printf("while"); 
            break;
        
        // Palavra reservada    
        case TOK_FACA: 
            printf("do"); 
            break;
        
        // Final de arquivo
        case TOK_EOF: 
            printf("// Fim do Programa\n"); 
            break;
        
        // Tratamento de erro
        case TOK_ERRO:
            printf("ERRO: Caractere desconhecido '%s' ", tok->atributo);
            break;
    }
}

int main() {
    char nome_arquivo[50];
    FILE *arquivo;
    Token *tok;

    printf("Digite o nome do arquivo: ");
    scanf("%s", nome_arquivo);

    // Abre o arquivo 
    arquivo = fopen(nome_arquivo, "r");

    // Tratamento de um possivel erro na abertura do arquivo
    if (!arquivo) {
        printf("Erro: Nao foi possivel abrir o arquivo '%s'.\n", nome_arquivo);
        return 1;
    }

    // Vinculamento do yyin ao FLEX
    yyin = arquivo;

    printf("\n--- Inicio da Analise Lexica ---\n");

    while (1) {
        tok = proximo_token();
        
        if (tok == NULL) break;
        
        imprime_token(tok);
        
        if (tok->tipo == TOK_EOF) break;
    }

    fclose(arquivo);
    return 0;
}