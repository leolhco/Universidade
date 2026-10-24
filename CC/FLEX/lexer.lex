%option noyywrap
%option nodefault
%option outfile="lexer.c" header-file="lexer.h"

%{
#include <string.h>
#include "lex.h"

 /* Modificaçao para garantir que o yylex() retorne o ponteiro do Token 
   Referencia sobre a macro YY_DECL: https://ftp.gnu.org/old-gnu/Manuals/flex-2.5.4/html_node/flex_10.html
 */
#define YY_DECL Token *yylex(void)

%}

 /* Expressoes regulares */
SEPARADOR    [ \t\n\r]+
ID        [a-zA-Z_][a-zA-Z0-9_]*
NUM_INT   [0-9]+
NUM_FLOAT [0-9]+\.[0-9]+([eE][+-]?[0-9]+)?
RELOP     "<"|"<="|">"|">="|"="|"<<"

 /* Referencia sobre a Expressao Regular: https://stackoverflow.com/questions/25395251/detecting-and-skipping-line-comments-with-flex */
COMENTARIO   "/*"([^*]|\*+[^*/])*\*+"/"

%%

{COMENTARIO}    { return token(TOK_COMENTARIO, yytext); }
{SEPARADOR}       { return token(TOK_SEPARADOR, yytext); }

"ini"       { return token(TOK_INI, "none"); }
"fim"       { return token(TOK_FIM, "none"); }
"se"        { return token(TOK_SE, "none"); }
"senao"     { return token(TOK_SENAO, "none"); }
"enquanto"  { return token(TOK_ENQUANTO, "none"); }
"faca"      { return token(TOK_FACA, "none"); }

{RELOP}     { return token(TOK_RELOP, yytext); }
{NUM_FLOAT} { return token(TOK_NUM_FLOAT, yytext); }
{NUM_INT}   { return token(TOK_NUM_INT, yytext); }
{ID}        { return token(TOK_ID, yytext); }

"("         { return token(TOK_PARESQ, "none"); }
")"         { return token(TOK_PARDIR, "none"); }
":"         { return token(TOK_ATRIB, "none"); }

<<EOF>>     { return token(TOK_EOF, "none"); }

 /* Tratamento de token desconhecido */
.           { return token(TOK_ERRO, yytext); } 

%%

 /* Variavel global para o token */
Token tok;

 /* Função para criar um token */
Token *token(int tipo, char *valor) {
    tok.tipo = tipo;
    strncpy(tok.atributo, valor, 50);
    tok.atributo[50] = '\0';
    return &tok;
}