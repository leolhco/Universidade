#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexico.h"


// classes de caracteres
enum {
    C_LETRA = 0, // letra excluindo 'e' e 'E'                                
    C_E,// 'E' e 'e'    
    C_DIG, // digito                                                   
    C_UNDER, // _                                                        
    C_PLUS, // +                                                        
    C_MINUS, // -                                                        
    C_AST, // *                                                        
    C_SLASH, // /                                                        
    C_EQ, // =                                                        
    C_LT, // <                                                        
    C_GT, // >                                                        
    C_LPAR, // (
    C_RPAR, // )
    C_SEMI, // ;
    C_COLON, // :
    C_COMMA, // ,
    C_QUOTE, // '
    C_DOT, // .  
    C_WS, // ' ' | '\t' | '\n'  \r'   */
    C_OUTRO, // qualquer outro caractere
    C_EOF, // EFO
    NUM_CLASSES
};

// estados do AFD
enum {
    E_INI  = 0,  
    E_SEP  = 1,  
    E_ID   = 2,  
    E_INT  = 3,  
    E_DOT  = 4,  
    E_FLT  = 5,  
    E_EX1  = 6,  
    E_EX2  = 7,  
    E_EXD  = 8,  
    E_CH1  = 9,  
    E_CH2  = 10, 
    E_CH3  = 11, 
    E_AST  = 12, 
    E_POT  = 13, 
    E_EQ1  = 14, 
    E_EQ2  = 15, 
    E_LT   = 16, 
    E_LE   = 17, 
    E_NE   = 18, 
    E_GT   = 19, 
    E_GE   = 20, 
    E_SLH  = 21, 
    E_COM  = 22, 
    E_CAST = 23, 
    E_COMF = 24, 
    E_SOMA = 25, 
    E_SUB  = 26, 
    E_LPAR = 27, 
    E_RPAR = 28, 
    E_SEMI = 29, 
    E_COLN = 30, 
    E_COMA = 31, 
    NUM_ESTADOS
};

// estado global
typedef struct {
    long pos; 
    int linha, col;
 } Posicao;

static char *fonte = NULL;   
static long tam_fonte = 0;
static Posicao atual = {0, 1, 1};
static int total_erros = 0;

static int trans[NUM_ESTADOS][NUM_CLASSES]; // tabela de transição do AFD 
static int aceita[NUM_ESTADOS];  

// nomes dos tokens
static const char *NOMES[] = {
    "programa","inicio","fim","void","int","char","float",
    "se","entao","e_se","senao","enquanto","faca","repita","ate","para","passo",
    "id","num_int","num_float","char_const",
    "soma","sub","mult","div","pot",
    "atrib","igual","dif","menor","maior","menor_ig","maior_ig",
    "abre_par","fecha_par","ponto_virgula","dois_pontos","virgula",
    "separador","comentario","EOF"
};
const char *nome_token(TipoToken t) { return NOMES[t]; }

// tabela de palavras reservadas
static const struct { const char *lexema; TipoToken tipo; } RESERVADAS[] = {
    {"programa",TK_PROGRAMA},{"inicio",TK_INICIO},{"fim",TK_FIM},
    {"void",TK_VOID},{"int",TK_INT},{"char",TK_CHAR},{"float",TK_FLOAT},
    {"se",TK_SE},{"entao",TK_ENTAO},{"e_se",TK_E_SE},{"senao",TK_SENAO},
    {"enquanto",TK_ENQUANTO},{"faca",TK_FACA},{"repita",TK_REPITA},
    {"ate",TK_ATE},{"para",TK_PARA},{"passo",TK_PASSO}
};

#define NUM_RESERVADAS (int)(sizeof(RESERVADAS)/sizeof(RESERVADAS[0]))
static int busca_reservada(const char *lex) {
    for (int i = 0; i < NUM_RESERVADAS; i++)
        if (strcmp(RESERVADAS[i].lexema, lex) == 0) return RESERVADAS[i].tipo;
    return -1;
}

// tabela de simmbolos                             
#define MAX_TS 1024
typedef struct {
    char nome_token[16];
    char lexema[MAX_LEXEMA];
    char tipo_dado[8];
} EntradaTS;

static EntradaTS ts[MAX_TS];
static int ts_qtd = 0;

// insere e devolve a posição da entrada na tabela       
static int ts_insere(const char *nome, const char *lex, const char *tipo) {
    for (int i = 0; i < ts_qtd; i++)
        if (strcmp(ts[i].lexema, lex) == 0 &&
            strcmp(ts[i].nome_token, nome) == 0)
            return i; // ja existe 
    if (ts_qtd >= MAX_TS) {
        fprintf(stderr, "AVISO: tabela de simbolos cheia.\n");
        return -1;
    }
    snprintf(ts[ts_qtd].nome_token, sizeof ts[ts_qtd].nome_token, "%s", nome);
    snprintf(ts[ts_qtd].lexema,     sizeof ts[ts_qtd].lexema,     "%s", lex);
    snprintf(ts[ts_qtd].tipo_dado,  sizeof ts[ts_qtd].tipo_dado,  "%s", tipo);
    return ts_qtd++;
}

void imprime_tabela_simbolos(void) {
    printf("\n=================== TABELA DE SIMBOLOS ===================\n");
    printf("%-8s %-12s %-24s %s\n", "Posicao", "Token", "Lexema", "Tipo do Dado");
    printf("-----------------------------------------------------------\n");
    for (int i = 0; i < ts_qtd; i++)
        printf("%-8d %-12s %-24s %s\n",
               i, ts[i].nome_token, ts[i].lexema, ts[i].tipo_dado);
}

// classificador de caracteres
static int move(int c) {
    if (c == -1)                  
        return C_EOF;
    if (c == 'E' || c == 'e')     
        return C_E;
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))   
        return C_LETRA;
    if (c >= '0' && c <= '9')     
        return C_DIG;
    switch (c) {
        case '_':  
            return C_UNDER;
        case '+':  
            return C_PLUS;
        case '-':  
            return C_MINUS;
        case '*':  
            return C_AST;
        case '/':  
            return C_SLASH;
        case '=':  
            return C_EQ;
        case '<':  
            return C_LT;
        case '>':  
            return C_GT;
        case '(':  
            return C_LPAR;
        case ')':  
            return C_RPAR;
        case ';':  
            return C_SEMI;
        case ':':  
            return C_COLON;
        case ',':  
            return C_COMMA;
        case '\'': 
            return C_QUOTE;
        case '.':  
            return C_DOT;
        case ' ': 
            return C_WS;
        case '\t':
            return C_WS;
        case '\n':
            return C_WS;
        case '\r': 
            return C_WS;
        default:   
            return C_OUTRO;
    }
}

// construção da tabela de transição
// não for definido -> -1 (erro)
static void init_tabelas(void) {
    for (int e = 0; e < NUM_ESTADOS; e++) {
        aceita[e] = -1;
        for (int c = 0; c < NUM_CLASSES; c++) trans[e][c] = -1;
    }

    // estado inicial
    trans[E_INI][C_WS] = E_SEP;
    trans[E_INI][C_LETRA] = E_ID;
    trans[E_INI][C_E] = E_ID;
    trans[E_INI][C_DIG] = E_INT;
    trans[E_INI][C_QUOTE] = E_CH1;
    trans[E_INI][C_AST] = E_AST;
    trans[E_INI][C_SLASH] = E_SLH;
    trans[E_INI][C_EQ] = E_EQ1;
    trans[E_INI][C_LT] = E_LT;
    trans[E_INI][C_GT] = E_GT;
    trans[E_INI][C_PLUS] = E_SOMA;
    trans[E_INI][C_MINUS] = E_SUB;
    trans[E_INI][C_LPAR] = E_LPAR;
    trans[E_INI][C_RPAR] = E_RPAR;
    trans[E_INI][C_SEMI] = E_SEMI;
    trans[E_INI][C_COLON] = E_COLN;
    trans[E_INI][C_COMMA] = E_COMA;

    // separador 
    trans[E_SEP][C_WS] = E_SEP;

    // id 
    trans[E_ID][C_LETRA] = E_ID;
    trans[E_ID][C_E] = E_ID;
    trans[E_ID][C_DIG] = E_ID;
    trans[E_ID][C_UNDER] = E_ID;

    // num_int / num_float
    trans[E_INT][C_DIG] = E_INT;
    trans[E_INT][C_DOT] = E_DOT;
    trans[E_INT][C_E] = E_EX1;
    trans[E_DOT][C_DIG] = E_FLT;
    trans[E_FLT][C_DIG] = E_FLT;
    trans[E_FLT][C_E] = E_EX1;
    trans[E_EX1][C_PLUS] = E_EX2;
    trans[E_EX1][C_MINUS] = E_EX2;
    trans[E_EX1][C_DIG] = E_EXD;
    trans[E_EX2][C_DIG] = E_EXD;
    trans[E_EXD][C_DIG] = E_EXD;

    // char_const
    trans[E_CH1][C_LETRA] = E_CH2;
    trans[E_CH1][C_E] = E_CH2;
    trans[E_CH1][C_DIG] = E_CH2;
    trans[E_CH2][C_QUOTE] = E_CH3;

    //  operadores 
    trans[E_AST][C_AST] = E_POT; // **   
    trans[E_EQ1][C_EQ] = E_EQ2; // ==   
    trans[E_LT][C_EQ] = E_LE; // <=   
    trans[E_LT][C_GT] = E_NE; // <>   
    trans[E_GT][C_EQ] = E_GE; // >=   

    //  comentario 
    trans[E_SLH][C_AST] = E_COM;      
    for (int c = 0; c < NUM_CLASSES; c++) {
        if (c == C_EOF) 
            continue;// EOF dentro de comentário = erro    
        trans[E_COM][c] = E_COM; // consome qualquer caractere         
        trans[E_CAST][c] = E_COM;             
    }
    trans[E_COM][C_AST] = E_CAST;
    trans[E_CAST][C_AST] = E_CAST;
    trans[E_CAST][C_SLASH] = E_COMF;

    // estados de aceitação 
    aceita[E_SEP] = TK_SEPARADOR;
    aceita[E_ID] = TK_ID; 
    aceita[E_INT] = TK_NUM_INT;
    aceita[E_FLT] = TK_NUM_FLOAT;
    aceita[E_EXD] = TK_NUM_FLOAT;
    aceita[E_CH3] = TK_CHAR_CONST;
    aceita[E_AST] = TK_MULT;
    aceita[E_POT] = TK_POT;
    aceita[E_EQ1] = TK_ATRIB;
    aceita[E_EQ2] = TK_IGUAL;
    aceita[E_LT] = TK_MENOR;
    aceita[E_LE] = TK_MENOR_IG;
    aceita[E_NE] = TK_DIF;
    aceita[E_GT] = TK_MAIOR;
    aceita[E_GE] = TK_MAIOR_IG;
    aceita[E_SLH] = TK_DIV;
    aceita[E_COMF] = TK_COMENTARIO;
    aceita[E_SOMA] = TK_SOMA;
    aceita[E_SUB] = TK_SUB;
    aceita[E_LPAR] = TK_ABRE_PAR;
    aceita[E_RPAR] = TK_FECHA_PAR;
    aceita[E_SEMI] = TK_PONTO_VIRGULA;
    aceita[E_COLN] = TK_DOIS_PONTOS;
    aceita[E_COMA] = TK_VIRGULA;
}

// leitura do fonte com posição
static int peek(void) {
    return (atual.pos >= tam_fonte) ? -1 : (unsigned char)fonte[atual.pos];
} 

static void prox_char(void) {
    int c = peek();
    if (c == -1) 
        return;
    atual.pos++;
    if (c == '\n') {
        atual.linha++; 
        atual.col = 1; 
    }
    else
        atual.col++;
}

// mensagens de erro
static void erro_lexico(int estado, Posicao inicio, int c) {
    total_erros++;
    fprintf(stderr, "ERRO LEXICO (linha %d, coluna %d): ", atual.linha, atual.col);
    if (estado == E_CH1 || estado == E_CH2) {
        fprintf(stderr, "constante de caractere malformada iniciada na linha %d, "
                        "coluna %d — esperado uma unica letra ou digito entre "
                        "apostrofos, mas foi encontrado ", inicio.linha, inicio.col);
    } else {
        fprintf(stderr, "caractere invalido para a linguagem: ");
    }
    if (c == -1)        fprintf(stderr, "<fim de arquivo>.\n");
    else if (c == '\n') fprintf(stderr, "'\\n'.\n");
    else if (c == '\t') fprintf(stderr, "'\\t'.\n");
    else                fprintf(stderr, "'%c' (codigo 0x%02X).\n", c, c);
}

// construção do token aceito
static Token get_token(int estado_final, Posicao inicio, Posicao fim) {
    Token t;
    memset(&t, 0, sizeof t);
    t.tipo   = (TipoToken)aceita[estado_final];
    t.linha  = inicio.linha;
    t.coluna = inicio.col;

    long n = fim.pos - inicio.pos;
    if (n >= MAX_LEXEMA) n = MAX_LEXEMA - 1;     
    memcpy(t.lexema, fonte + inicio.pos, (size_t)n);
    t.lexema[n] = '\0';

    switch (t.tipo) {
        case TK_ID: {
            int r = busca_reservada(t.lexema);
            if (r != -1) {                 
                t.tipo = (TipoToken)r; 
            } else {                     
                t.atributo.pos_ts = ts_insere("id", t.lexema, "-");
                t.tem_atributo = 1;
            }
            break;
        }
        case TK_NUM_INT:
            t.atributo.num_int = strtol(t.lexema, NULL, 10);
            t.tem_atributo  = 1;
            ts_insere("num_int", t.lexema, "int");
            break;
        case TK_NUM_FLOAT:
            t.atributo.num_float = strtod(t.lexema, NULL);
            t.tem_atributo  = 1;
            ts_insere("num_float", t.lexema, "float");
            break;
        case TK_CHAR_CONST:
            t.atributo.char_const = t.lexema[1]; 
            t.tem_atributo  = 1;
            ts_insere("char_const", t.lexema, "char");
            break;
        default:
            break;  
    }
    return t;
}

Token proximo_token(void) {
    for (;;) {   
        Posicao inicio = atual;
        int estado = E_INI;
        int ult_aceite_estado = -1;
        Posicao ult_aceite_pos = atual;

        for (;;) {
            int c   = peek();
            int cls = move(c);

            // fim do arquivo alcançado fora de qualquer lexema
            if (estado == E_INI && cls == C_EOF) {
                Token t; 
                memset(&t, 0, sizeof t);
                t.tipo = TK_EOF; 
                t.linha = atual.linha; 
                t.coluna = atual.col;
                strcpy(t.lexema, "<EOF>");
                return t;
            }

            int prox = trans[estado][cls]; 

            if (prox == -1) {    
                if (estado == E_COM || estado == E_CAST) {
                    total_erros++;
                    fprintf(stderr, "ERRO LEXICO (linha %d, coluna %d): comentario "
                            "aberto aqui nao foi finalizado antes do fim do "
                            "arquivo (esperado \"*/\").\n",
                            inicio.linha, inicio.col);
                    Token t; 
                    memset(&t, 0, sizeof t);
                    t.tipo = TK_EOF;
                    t.linha = atual.linha;
                    t.coluna = atual.col;
                    strcpy(t.lexema, "<EOF>");
                    return t;
                }
                if (ult_aceite_estado != -1) {  
                    atual = ult_aceite_pos;
                    Token t = get_token(ult_aceite_estado, inicio, atual);
                    if (t.tipo == TK_SEPARADOR || t.tipo == TK_COMENTARIO)
                        break; 
                    return t;
                }
                // nenhum prefixo aceito -> erro lexico e modo panico 
                erro_lexico(estado, inicio, c);
                atual = inicio;
                prox_char();  // descarta 1 caractere    
                break; 
            }

            estado = prox;
            prox_char();
            if (aceita[estado] != -1) {
                ult_aceite_estado = estado;
                ult_aceite_pos    = atual;
            }
        }
    }
}

void lex_inicializa(const char *caminho_arquivo) {
    FILE *f = fopen(caminho_arquivo, "rb");
    if (!f) {
        fprintf(stderr, "ERRO: nao foi possivel abrir '%s'.\n", caminho_arquivo);
        exit(1);
    }
    fseek(f, 0, SEEK_END);
    tam_fonte = ftell(f);
    fseek(f, 0, SEEK_SET);
    fonte = (char *)malloc((size_t)tam_fonte + 1);
    if (!fonte) { fprintf(stderr, "ERRO: sem memoria.\n"); exit(1); }
    if (tam_fonte > 0 && fread(fonte, 1, (size_t)tam_fonte, f) != (size_t)tam_fonte) {
        fprintf(stderr, "ERRO: falha na leitura de '%s'.\n", caminho_arquivo);
        exit(1);
    }
    fonte[tam_fonte] = '\0';
    fclose(f);

    atual.pos = 0; atual.linha = 1; atual.col = 1;
    total_erros = 0;
    ts_qtd = 0;
    init_tabelas();
}

void lex_finaliza(void) { 
    free(fonte); fonte = NULL; 
}

int  lex_total_erros(void) { 
    return total_erros;
 }

void imprime_tabela_transicao(void) {
    static const char *CL[] = {"letra","E/e","dig","_","+","-","*","/","=",
                               "<",">","(",")",";",":",",","'",".","ws","outro","EOF"};
    printf("TABELA DE TRANSICAO DO AFD (linhas = estados, colunas = classes; . = erro)\n\n");
    printf("%4s |", "est");
    for (int c = 0; c < NUM_CLASSES; c++) printf("%6s", CL[c]);
    printf("  | aceita\n");
    for (int c = 0; c < NUM_CLASSES + 1; c++) printf("------");
    printf("--------\n");
    for (int e = 0; e < NUM_ESTADOS; e++) {
        printf("%4d |", e);
        for (int c = 0; c < NUM_CLASSES; c++) {
            if (trans[e][c] == -1) printf("%6s", ".");
            else                   printf("%6d", trans[e][c]);
        }
        if (aceita[e] != -1)
            printf("  | %s", NOMES[aceita[e]]);
        printf("\n");
    }
}
