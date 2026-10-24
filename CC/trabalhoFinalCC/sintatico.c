#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexico.h"
#include "sintatico.h"

// variaveis globais
static Token tokenAtual; // token de lookahead
static int totalErros = 0;
static int modoPanico = 0; // evita cascata de mensagens apos 1 erro

// nomes dos tokens usados nas mensagens de erro
static const char *legivel(TipoToken t)
{
    switch (t)
    {
    case TK_PROGRAMA:
        return "programa";
    case TK_INICIO:
        return "inicio";
    case TK_FIM:
        return "fim";
    case TK_VOID:
        return "void";
    case TK_INT:
        return "int";
    case TK_CHAR:
        return "char";
    case TK_FLOAT:
        return "float";
    case TK_SE:
        return "se";
    case TK_ENTAO:
        return "entao";
    case TK_E_SE:
        return "e_se";
    case TK_SENAO:
        return "senao";
    case TK_ENQUANTO:
        return "enquanto";
    case TK_FACA:
        return "faca";
    case TK_REPITA:
        return "repita";
    case TK_ATE:
        return "ate";
    case TK_PARA:
        return "para";
    case TK_PASSO:
        return "passo";
    case TK_ID:
        return "identificador";
    case TK_NUM_INT:
        return "num_int";
    case TK_NUM_FLOAT:
        return "num_float";
    case TK_CHAR_CONST:
        return "char_const";
    case TK_SOMA:
        return "+";
    case TK_SUB:
        return "-";
    case TK_MULT:
        return "*";
    case TK_DIV:
        return "/";
    case TK_POT:
        return "**";
    case TK_ATRIB:
        return "=";
    case TK_IGUAL:
        return "==";
    case TK_DIF:
        return "<>";
    case TK_MENOR:
        return "<";
    case TK_MAIOR:
        return ">";
    case TK_MENOR_IG:
        return "<=";
    case TK_MAIOR_IG:
        return ">=";
    case TK_ABRE_PAR:
        return "(";
    case TK_FECHA_PAR:
        return ")";
    case TK_PONTO_VIRGULA:
        return ";";
    case TK_DOIS_PONTOS:
        return ":";
    case TK_VIRGULA:
        return ",";
    case TK_EOF:
        return "fim de arquivo";
    default:
        return "?";
    }
}

// construçao da arvore
static NoArvore *novoNo(const char *rotulo)
{
    NoArvore *n = (NoArvore *)calloc(1, sizeof(NoArvore));
    snprintf(n->rotulo, MAX_ROTULO, "%s", rotulo);
    n->ehTerminal = 0;
    return n;
}
static NoArvore *novaFolha(Token t)
{
    NoArvore *n = (NoArvore *)calloc(1, sizeof(NoArvore));
    snprintf(n->rotulo, MAX_ROTULO, "%s", legivel(t.tipo));
    n->ehTerminal = 1;
    snprintf(n->lexema, sizeof n->lexema, "%s", t.lexema);
    n->linha = t.linha;
    n->coluna = t.coluna;
    return n;
}
// anexa filho como ultimo filho de pai (percorre a lista de irmaos)
static void addFilho(NoArvore *pai, NoArvore *filho)
{
    if (!pai || !filho)
        return;
    if (!pai->filho)
    {
        pai->filho = filho;
        return;
    }
    NoArvore *p = pai->filho;
    while (p->irmao)
    {
        p = p->irmao;
    }
    p->irmao = filho;
}

// erros
static void erroSintatico(const char *esperado)
{
    if (modoPanico)
        return;
    totalErros++;
    modoPanico = 1;
    fprintf(stderr,
            "Erro sintatico (linha %d, coluna %d): esperado %s, mas foi encontrado '%s' (%s).\n",
            tokenAtual.linha, tokenAtual.coluna, esperado,
            tokenAtual.lexema, legivel(tokenAtual.tipo));
}

// prox token
static void avancar(void)
{
    tokenAtual = proximo_token();
}

// consumaçao de tokens(ou nao)
static NoArvore *consumir(TipoToken tipo)
{
    if (tokenAtual.tipo == tipo)
    {
        NoArvore *folha = novaFolha(tokenAtual);
        avancar();
        modoPanico = 0;
        return folha;
    }
    erroSintatico(legivel(tipo));
    return NULL;
}

// prototipos dos nao-terminais
static NoArvore *programa(void);
static NoArvore *bloco(void);
static NoArvore *tipo(void);
static NoArvore *declaracoes(void);
static NoArvore *declaracao(void);
static NoArvore *lista_ids(void);
static NoArvore *lista_ids_l(void);
static NoArvore *comandos(void);
static NoArvore *comando(void);
static NoArvore *cmd(void);
static NoArvore *atribuicao(void);
static NoArvore *expr(void);
static NoArvore *expr_l(void);
static NoArvore *termo(void);
static NoArvore *termo_l(void);
static NoArvore *fator(void);
static NoArvore *fator_l(void);
static NoArvore *base(void);
static NoArvore *primario(void);
static NoArvore *constante(void);
static NoArvore *selecao(void);
static NoArvore *lista_e_se(void);
static NoArvore *parte_senao(void);
static NoArvore *enquanto(void);
static NoArvore *repita(void);
static NoArvore *para(void);
static NoArvore *sinal(void);
static NoArvore *condicao(void);
static NoArvore *op_rel(void);

// predicados sobre o lookahead
static int ehInicioComando(TipoToken t)
{
    return t == TK_ID || t == TK_SE || t == TK_ENQUANTO || t == TK_REPITA || t == TK_PARA;
}

static int ehTipo(TipoToken t)
{
    return t == TK_VOID || t == TK_INT || t == TK_CHAR || t == TK_FLOAT;
}

// <programa> ::= <tipo> programa ( ) <bloco>
static NoArvore *programa(void)
{
    NoArvore *n = novoNo("<programa>");
    addFilho(n, tipo());
    addFilho(n, consumir(TK_PROGRAMA));
    addFilho(n, consumir(TK_ABRE_PAR));
    addFilho(n, consumir(TK_FECHA_PAR));
    addFilho(n, bloco());
    return n;
}

// <bloco> ::= inicio <declaracoes> <comandos> fim
static NoArvore *bloco(void)
{
    NoArvore *n = novoNo("<bloco>");
    addFilho(n, consumir(TK_INICIO));
    addFilho(n, declaracoes());
    addFilho(n, comandos());
    addFilho(n, consumir(TK_FIM));
    return n;
}

// <tipo> ::= void | int | char | float
static NoArvore *tipo(void)
{
    NoArvore *n = novoNo("<tipo>");
    switch (tokenAtual.tipo)
    {
    case TK_VOID:
        addFilho(n, consumir(TK_VOID));
        break;
    case TK_INT:
        addFilho(n, consumir(TK_INT));
        break;
    case TK_CHAR:
        addFilho(n, consumir(TK_CHAR));
        break;
    case TK_FLOAT:
        addFilho(n, consumir(TK_FLOAT));
        break;
    default:
        erroSintatico("um tipo (void, int, char ou float)");
    }
    return n;
}

// <declaracoes> ::= <declaracao> <declaracoes> | ε
static NoArvore *declaracoes(void)
{
    NoArvore *n = novoNo("<declaracoes>");
    if (ehTipo(tokenAtual.tipo))
    {
        addFilho(n, declaracao());
        addFilho(n, declaracoes());
    }
    else
    {
        addFilho(n, novoNo("ε"));
    }
    return n;
}

// <declaracao> ::= <tipo> : <lista_ids> ;
static NoArvore *declaracao(void)
{
    NoArvore *n = novoNo("<declaracao>");
    addFilho(n, tipo());
    addFilho(n, consumir(TK_DOIS_PONTOS));
    addFilho(n, lista_ids());
    addFilho(n, consumir(TK_PONTO_VIRGULA));
    return n;
}

// <lista_ids> ::= id <lista_ids'>
static NoArvore *lista_ids(void)
{
    NoArvore *n = novoNo("<lista_ids>");
    addFilho(n, consumir(TK_ID));
    addFilho(n, lista_ids_l());
    return n;
}

// <lista_ids'> ::= , id <lista_ids'> | ε
static NoArvore *lista_ids_l(void)
{
    NoArvore *n = novoNo("<lista_ids'>");
    if (tokenAtual.tipo == TK_VIRGULA)
    {
        addFilho(n, consumir(TK_VIRGULA));
        addFilho(n, consumir(TK_ID));
        addFilho(n, lista_ids_l());
    }
    else
    {
        addFilho(n, novoNo("ε"));
    }
    return n;
}

// <comandos> ::= <comando> <comandos> | ε
static NoArvore *comandos(void)
{
    NoArvore *n = novoNo("<comandos>");
    if (ehInicioComando(tokenAtual.tipo))
    {
        addFilho(n, comando());
        addFilho(n, comandos());
    }
    else
    {
        addFilho(n, novoNo("ε"));
    }
    return n;
}

// <comando> ::= <atribuicao> | <selecao> | <enquanto> | <repita> | <para>
static NoArvore *comando(void)
{
    NoArvore *n = novoNo("<comando>");
    switch (tokenAtual.tipo)
    {
    case TK_ID:
        addFilho(n, atribuicao());
        break;
    case TK_SE:
        addFilho(n, selecao());
        break;
    case TK_ENQUANTO:
        addFilho(n, enquanto());
        break;
    case TK_REPITA:
        addFilho(n, repita());
        break;
    case TK_PARA:
        addFilho(n, para());
        break;
    default:
        erroSintatico("um comando (id, se, enquanto, repita ou para)");
    }
    return n;
}

// <cmd> ::= <comando> | <bloco>
static NoArvore *cmd(void)
{
    NoArvore *n = novoNo("<cmd>");
    if (tokenAtual.tipo == TK_INICIO)
        addFilho(n, bloco());
    else if (ehInicioComando(tokenAtual.tipo))
        addFilho(n, comando());
    else
        erroSintatico("um comando ou um bloco (inicio)");
    return n;
}

// <atribuicao> ::= id = <expr> ;
static NoArvore *atribuicao(void)
{
    NoArvore *n = novoNo("<atribuicao>");
    addFilho(n, consumir(TK_ID));
    addFilho(n, consumir(TK_ATRIB));
    addFilho(n, expr());
    addFilho(n, consumir(TK_PONTO_VIRGULA));
    return n;
}

// <expr> ::= <termo> <expr'>
static NoArvore *expr(void)
{
    NoArvore *n = novoNo("<expr>");
    addFilho(n, termo());
    addFilho(n, expr_l());
    return n;
}

// <expr'> ::= + <termo> <expr'> | - <termo> <expr'> | ε
static NoArvore *expr_l(void)
{
    NoArvore *n = novoNo("<expr'>");
    if (tokenAtual.tipo == TK_SOMA || tokenAtual.tipo == TK_SUB)
    {
        addFilho(n, consumir(tokenAtual.tipo));
        addFilho(n, termo());
        addFilho(n, expr_l());
    }
    else
    {
        addFilho(n, novoNo("ε"));
    }
    return n;
}

// <termo> ::= <fator> <termo'>
static NoArvore *termo(void)
{
    NoArvore *n = novoNo("<termo>");
    addFilho(n, fator());
    addFilho(n, termo_l());
    return n;
}

// <termo'> ::= * <fator> <termo'> | / <fator> <termo'> | ε
static NoArvore *termo_l(void)
{
    NoArvore *n = novoNo("<termo'>");
    if (tokenAtual.tipo == TK_MULT || tokenAtual.tipo == TK_DIV)
    {
        addFilho(n, consumir(tokenAtual.tipo));
        addFilho(n, fator());
        addFilho(n, termo_l());
    }
    else
    {
        addFilho(n, novoNo("ε"));
    }
    return n;
}

// <fator> ::= <base> <fator'>
static NoArvore *fator(void)
{
    NoArvore *n = novoNo("<fator>");
    addFilho(n, base());
    addFilho(n, fator_l());
    return n;
}

// <fator'> ::= ** <fator> | ε
static NoArvore *fator_l(void)
{
    NoArvore *n = novoNo("<fator'>");
    if (tokenAtual.tipo == TK_POT)
    {
        addFilho(n, consumir(TK_POT));
        addFilho(n, fator());
    }
    else
    {
        addFilho(n, novoNo("ε"));
    }
    return n;
}

// <base> ::= - <base> | <primario>
static NoArvore *base(void)
{
    NoArvore *n = novoNo("<base>");
    if (tokenAtual.tipo == TK_SUB)
    {
        addFilho(n, consumir(TK_SUB));
        addFilho(n, base());
    }
    else
    {
        addFilho(n, primario());
    }
    return n;
}

// <primario> ::= id | <constante> | ( <expr> )
static NoArvore *primario(void)
{
    NoArvore *n = novoNo("<primario>");
    switch (tokenAtual.tipo)
    {
    case TK_ID:
        addFilho(n, consumir(TK_ID));
        break;
    case TK_NUM_INT:
    case TK_NUM_FLOAT:
    case TK_CHAR_CONST:
        addFilho(n, constante());
        break;
    case TK_ABRE_PAR:
        addFilho(n, consumir(TK_ABRE_PAR));
        addFilho(n, expr());
        addFilho(n, consumir(TK_FECHA_PAR));
        break;
    default:
        erroSintatico("um identificador, constante ou '('");
    }
    return n;
}

// <constante> ::= num_int | num_float | char_const
static NoArvore *constante(void)
{
    NoArvore *n = novoNo("<constante>");
    switch (tokenAtual.tipo)
    {
    case TK_NUM_INT:
        addFilho(n, consumir(TK_NUM_INT));
        break;
    case TK_NUM_FLOAT:
        addFilho(n, consumir(TK_NUM_FLOAT));
        break;
    case TK_CHAR_CONST:
        addFilho(n, consumir(TK_CHAR_CONST));
        break;
    default:
        erroSintatico("uma constante (num_int, num_float ou char_const)");
    }
    return n;
}

// <selecao> ::= se ( <condicao> ) entao <cmd> <lista_e_se> <parte_senao>
static NoArvore *selecao(void)
{
    NoArvore *n = novoNo("<selecao>");
    addFilho(n, consumir(TK_SE));
    addFilho(n, consumir(TK_ABRE_PAR));
    addFilho(n, condicao());
    addFilho(n, consumir(TK_FECHA_PAR));
    addFilho(n, consumir(TK_ENTAO));
    addFilho(n, cmd());
    addFilho(n, lista_e_se());
    addFilho(n, parte_senao());
    return n;
}

// <lista_e_se> ::= e_se ( <condicao> ) entao <cmd> <lista_e_se> | ε
static NoArvore *lista_e_se(void)
{
    NoArvore *n = novoNo("<lista_e_se>");
    if (tokenAtual.tipo == TK_E_SE)
    {
        addFilho(n, consumir(TK_E_SE));
        addFilho(n, consumir(TK_ABRE_PAR));
        addFilho(n, condicao());
        addFilho(n, consumir(TK_FECHA_PAR));
        addFilho(n, consumir(TK_ENTAO));
        addFilho(n, cmd());
        addFilho(n, lista_e_se());
    }
    else
    {
        addFilho(n, novoNo("ε"));
    }
    return n;
}

// <parte_senao> ::= senao <cmd> | ε
static NoArvore *parte_senao(void)
{
    NoArvore *n = novoNo("<parte_senao>");
    if (tokenAtual.tipo == TK_SENAO)
    {
        addFilho(n, consumir(TK_SENAO));
        addFilho(n, cmd());
    }
    else
    {
        addFilho(n, novoNo("ε"));
    }
    return n;
}

// <enquanto> ::= enquanto ( <condicao> ) faca <cmd>
static NoArvore *enquanto(void)
{
    NoArvore *n = novoNo("<enquanto>");
    addFilho(n, consumir(TK_ENQUANTO));
    addFilho(n, consumir(TK_ABRE_PAR));
    addFilho(n, condicao());
    addFilho(n, consumir(TK_FECHA_PAR));
    addFilho(n, consumir(TK_FACA));
    addFilho(n, cmd());
    return n;
}

// <repita> ::= repita <cmd> ate ( <condicao> ) ;
static NoArvore *repita(void)
{
    NoArvore *n = novoNo("<repita>");
    addFilho(n, consumir(TK_REPITA));
    addFilho(n, cmd());
    addFilho(n, consumir(TK_ATE));
    addFilho(n, consumir(TK_ABRE_PAR));
    addFilho(n, condicao());
    addFilho(n, consumir(TK_FECHA_PAR));
    addFilho(n, consumir(TK_PONTO_VIRGULA));
    return n;
}

// <para> ::= para id = num_int ate num_int passo <sinal> num_int <cmd>
static NoArvore *para(void)
{
    NoArvore *n = novoNo("<para>");
    addFilho(n, consumir(TK_PARA));
    addFilho(n, consumir(TK_ID));
    addFilho(n, consumir(TK_ATRIB));
    addFilho(n, consumir(TK_NUM_INT));
    addFilho(n, consumir(TK_ATE));
    addFilho(n, consumir(TK_NUM_INT));
    addFilho(n, consumir(TK_PASSO));
    addFilho(n, sinal());
    addFilho(n, consumir(TK_NUM_INT));
    addFilho(n, cmd());
    return n;
}

// <sinal> ::= + | -
static NoArvore *sinal(void)
{
    NoArvore *n = novoNo("<sinal>");
    if (tokenAtual.tipo == TK_SOMA)
        addFilho(n, consumir(TK_SOMA));
    else if (tokenAtual.tipo == TK_SUB)
        addFilho(n, consumir(TK_SUB));
    else
        erroSintatico("um sinal (+ ou -)");
    return n;
}

// <condicao> ::= <expr> <op_rel> <expr>
static NoArvore *condicao(void)
{
    NoArvore *n = novoNo("<condicao>");
    addFilho(n, expr());
    addFilho(n, op_rel());
    addFilho(n, expr());
    return n;
}

// <op_rel> ::= == | <> | < | > | <= | >=
static NoArvore *op_rel(void)
{
    NoArvore *n = novoNo("<op_rel>");
    switch (tokenAtual.tipo)
    {
    case TK_IGUAL:
        addFilho(n, consumir(TK_IGUAL));
        break;
    case TK_DIF:
        addFilho(n, consumir(TK_DIF));
        break;
    case TK_MENOR:
        addFilho(n, consumir(TK_MENOR));
        break;
    case TK_MAIOR:
        addFilho(n, consumir(TK_MAIOR));
        break;
    case TK_MENOR_IG:
        addFilho(n, consumir(TK_MENOR_IG));
        break;
    case TK_MAIOR_IG:
        addFilho(n, consumir(TK_MAIOR_IG));
        break;
    default:
        erroSintatico("um operador relacional (==, <>, <, >, <= ou >=)");
    }
    return n;
}

// ponto de entrada
NoArvore *analisar(void)
{
    totalErros = 0;
    modoPanico = 0;
    avancar();
    NoArvore *raiz = programa();
    if (tokenAtual.tipo != TK_EOF)
    {
        modoPanico = 0;
        erroSintatico("fim de arquivo (tokens em excesso após o programa)");
    }
    return raiz;
}

int sint_total_erros(void)
{
    return totalErros;
}

// impressao
static void imprimeRec(NoArvore *n, int nivel)
{
    if (!n)
        return;
    for (int i = 0; i < nivel; i++)
        printf("  ");
    if (n->ehTerminal)
        printf("%s  \"%s\"  (%d,%d)\n", n->rotulo, n->lexema, n->linha, n->coluna);
    else
        printf("%s\n", n->rotulo);
    for (NoArvore *f = n->filho; f; f = f->irmao)
        imprimeRec(f, nivel + 1);
}
void imprime_arvore(NoArvore *raiz)
{
    printf("\n===================== ARVORE DE DERIVACAO =====================\n");
    imprimeRec(raiz, 0);
    printf("===============================================================\n");
}

void libera_arvore(NoArvore *n)
{
    if (!n)
        return;
    NoArvore *f = n->filho;
    while (f)
    {
        NoArvore *prox = f->irmao;
        libera_arvore(f);
        f = prox;
    }
    free(n);
}
