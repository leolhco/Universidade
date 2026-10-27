#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

typedef struct {
    char estado[3];     
    char cidade[100];   
    char numero[10];  
    char cargo[50];     
    char nome[100];    
    char nomeUrna[100];
    char siglaPartido[10]; 
    char genero[10]; 
    char grauInstrucao[50];
    char corRaca[50]; 
} Candidato;

typedef struct No {
    Candidato candidato;
    struct No *esquerda;
    struct No *direita;
    int altura;
} No;

typedef struct {
    Candidato *candidatos;
    int tamanho;
    int capacidade;
} EstruturaAux;

#endif