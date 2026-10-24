#include <stdio.h>

// Tokens com Lexema
#define TOK_ID 1
#define TOK_RELOP 2
#define TOK_SEPARADOR 3
#define TOK_NUM_INT 4
#define TOK_NUM_FLOAT 5
#define TOK_COMENTARIO 6

// Tokens que retornam none
#define TOK_PARESQ 7
#define TOK_PARDIR 8
#define TOK_ATRIB 9
#define TOK_INI 10
#define TOK_FIM 11
#define TOK_SE 12
#define TOK_SENAO 13
#define TOK_ENQUANTO 14
#define TOK_FACA 15
#define TOK_EOF 16
#define TOK_ERRO 17

// Estrutura de um token
typedef struct {
    int tipo;
    char atributo[50]; 
} Token;

// Função para criar um token
extern Token *token(int tipo, char *valor);

// Função do analisador lexico
extern Token *yylex();

// Variável do FLEX para ler arquivo
extern FILE *yyin; 
