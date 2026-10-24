%{
#include <stdio.h>
#include "Lexer.h"      // Analisador lexico
#define YYSTYPE double  // Define tipo da pilha
void yyerror (char *);  // Prototipo da funcao de erro
%}

%token NUM
%left '+' '-'
%left '*' '/'
%right NEGAR

%%
lines : lines expr '\n' { printf("= %.2f\n", $2); }
      | lines '\n'      { return 0; }
      |
      | error '\n'      { yyerror("Erro na ultima linha"); yyerrok; }
      ;

expr  : expr '+' expr        { printf("+ "); $$ = $1 + $3; }
      | expr '-' expr        { printf("- "); $$ = $1 - $3; }
      | expr '*' expr        { printf("* "); $$ = $1 * $3; }
      | expr '/' expr        { printf("/ "); $$ = $1 / $3; }
      | '(' expr ')'         { $$ = $2; }
      | '-' expr %prec NEGAR { printf("(-) "); $$ = -$2; }
      | NUM                  { printf("%g ", $1); $$ = $1; }
      ;
%%

/* yacc error handler */
void yyerror(char * s) { 
    fprintf (stderr, "%s\n", s); 
}

int main(void) {
    printf("\nDigite a expressao desejada:\n");
    return yyparse(); // chama o analisador sintatico
}