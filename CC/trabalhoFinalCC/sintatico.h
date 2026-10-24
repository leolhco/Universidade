#ifndef SINTATICO_H
#define SINTATICO_H

#include "lexico.h"

#define MAX_ROTULO 32

// no da arvore
// -filho: ponteiro para o primeiro filho
// -irmao: ponteiro para o próximo irmão
typedef struct NoArvore {
    char  rotulo[MAX_ROTULO];
    int   ehTerminal;
    char  lexema[MAX_LEXEMA];
    int   linha, coluna;
    struct NoArvore *filho; 
    struct NoArvore *irmao; 
} NoArvore;

// interface
NoArvore *analisar(void);

void imprime_arvore(NoArvore *raiz);

void libera_arvore(NoArvore *raiz);

int  sint_total_erros(void);

#endif
