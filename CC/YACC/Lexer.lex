%option noyywrap
%option outfile="Lexer.c" header-file="Lexer.h"

%{
#define YYSTYPE double
#include "y.tab.h"
#include <stdlib.h> // Necessario para a funcao atof
%}

DIGITO [0-9]

%%
[\t]       { /* ignora tabulacao e espaco */ }

{DIGITO}+([.]{DIGITO}+)?  { yylval = atof(yytext); return NUM; }

\n          { return yytext[0]; }
.           { return yytext[0]; }
%%

// Seção de Código VAZIA