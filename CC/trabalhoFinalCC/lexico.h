#ifndef LEXICO_H
#define LEXICO_H

#define MAX_LEXEMA 128

// tipos de token  
typedef enum {
    // palavras reservadas 
    TK_PROGRAMA, TK_INICIO, TK_FIM, TK_VOID, TK_INT, TK_CHAR, TK_FLOAT,
    TK_SE, TK_ENTAO, TK_E_SE, TK_SENAO, TK_ENQUANTO, TK_FACA,
    TK_REPITA, TK_ATE, TK_PARA, TK_PASSO,
    // identificador e constantes 
    TK_ID, TK_NUM_INT, TK_NUM_FLOAT, TK_CHAR_CONST,
    // operadores
    TK_SOMA, TK_SUB, TK_MULT, TK_DIV, TK_POT,
    TK_ATRIB, TK_IGUAL, TK_DIF, TK_MENOR, TK_MAIOR, TK_MENOR_IG, TK_MAIOR_IG,
    // pontuação
    TK_ABRE_PAR, TK_FECHA_PAR, TK_PONTO_VIRGULA, TK_DOIS_PONTOS, TK_VIRGULA,
    // comentario e separador
    TK_SEPARADOR, TK_COMENTARIO,
    // EOF
    TK_EOF
} TipoToken;

// valor do atributo 
typedef union {
    long num_int;                  
    double num_float;
    char char_const;                      
    int pos_ts; 
} Atributo;

// token
typedef struct {
    TipoToken tipo;
    Atributo atributo;
    int tem_atributo; // 1 se o atributo é válido
    int linha, coluna;          
    char lexema[MAX_LEXEMA];
} Token;

void lex_inicializa(const char *caminho_arquivo);
Token proximo_token(void);    
void lex_finaliza(void);
const char *nome_token(TipoToken t);
void imprime_tabela_simbolos(void);
void imprime_tabela_transicao(void);    
int lex_total_erros(void);

#endif 
