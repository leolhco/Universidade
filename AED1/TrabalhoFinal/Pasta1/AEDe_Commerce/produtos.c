#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ecommerce.h"

//Funçao que cria a lista de produtos(LP).
ListaProdutos *criarProdutos(){
    ListaProdutos *p = (ListaProdutos*)malloc(sizeof(ListaProdutos));
    p->inicio = NULL;
    return p;
}
//Funçao que cria a lista de categoria(LC).
ListaCategorias *criarLcategoria(){
    ListaCategorias *lc = (ListaCategorias*)malloc(sizeof(ListaCategorias));
    lc->inicio = NULL;
    return lc;
}
//Funçao que verifica se a categoria esta presente em LC.
int categoriainLcategoria(char *categoria,ListaCategorias *lc){
    if(lc == NULL) return -1;
    NoCategoria *no = lc->inicio;
    while(no->prox != NULL){
        if(strcmp(no->cat.nome,categoria) == 0){
            return 1;
        }
        no = no->prox;
    }
    return 0;
}
//Funçao que adiciona as categorias no inicio do programa.
int categoriasIniciais(ListaCategorias *lc) {
    if(lc == NULL) return -2;

    Categoria cs[] = {"Eletronicos","Eletrodomesticos","Brinquedos","Esporte","Saude"};


    int i = 0;
    while(i < 5){
        insic(lc,cs[i]);
        i++;
    }

    return 0;
}
//Funçao que mostra os nomes das categorias.
void showcategorias(ListaCategorias *lc) {
    if(lc == NULL) return;
    NoCategoria *no = lc->inicio;
    while(no != NULL) {
        printf("%s\n",no->cat.nome);
        no = no->prox;
    }
}
//Funçao que adiciona as categorias em LC.
int insic(ListaCategorias *lc,Categoria categoria) {
    if(lc == NULL) return -1;
    NoCategoria *no = (NoCategoria*) malloc(sizeof(NoCategoria));
    strcpy(no->cat.nome, categoria.nome);
    no->prox = lc->inicio;
    lc->inicio = no;
    return 0;
}
//Funçao que verifica se LP esta vazia.
int lisvp(ListaProdutos *p){
    if (p == NULL) return -1;
    if (p->inicio == NULL) return 0;
    else return 1;
}
//Funçao que mostra os itens de LP.
int showp(ListaProdutos *p){
    if (p == NULL) return -1;
    if (lisvp(p) == 0) return 1;
    Noprodutos *no = p->inicio;
    int indice = 0;
    while(no != NULL){
        printf("Indice: %d\n",indice);
        printf("Nome: %s\n", no->mer.nome);
        printf("Descricao: %s\n", no->mer.descricao);
        printf("Categoria: %s\n", no->mer.categoria);
        printf("Valor Unitario: %.2f\n", no->mer.preco);
        printf("Nota de Avaliacao: %.2f\n", no->mer.avaliacao);
        printf("Quantidade em Estoque: %d\n", no->mer.estoque);
        printf("vendedor: %s\n", no->mer.vendedor);
        printf("Vendas: %d\n", no->mer.vendas);
        printf("--------------------------------------------------\n");
        no = no->prox;
        indice++;
    }
    return 0;
}
//Funçao que mostra os itens de LP baseado no nome.
int showbyname(ListaProdutos *p, char *nome){
    if (p == NULL) return -1;
    if (lisvp(p) == 0) return -2;
    Noprodutos *no = p->inicio;
    int encontrado = 0;
    int indice = 0;
    while (no != NULL) {
        if (strcmp(nome, no->mer.nome) == 0) {
           printf("Indice: %d\n",indice);
           printf("Nome: %s\n", no->mer.nome);
           printf("Descricao: %s\n", no->mer.descricao);
           printf("Valor Unitario: %.2f\n", no->mer.preco);
           printf("Quantidade em Estoque: %d\n", no->mer.estoque);
           printf("Nota de Avaliacao: %.2f\n", no->mer.avaliacao);
           printf("Categoria: %s\n", no->mer.categoria);
           printf("Vendedor: %s\n", no->mer.vendedor);
           printf("Vendas: %d\n", no->mer.vendas);
           printf("--------------------------------------------------\n");
           encontrado = 1;
        }
        indice++;
        no = no->prox;
    }
    if(!encontrado){
        printf("\nERRO! Produto nao encontrado.\n");
        return 1;
      }else{
        return 0;
    }
}
//Funçao que mostra os itens de LP baseado na categoria
int showbytype(ListaProdutos *p, char *categoria){
    if (p == NULL) return -1;
    if (lisvp(p) == 0) return -2;
    Noprodutos *no = p->inicio;
    int encontrado = 0;
    int indice = 0;
    strlwr(categoria);
    while (no != NULL) {
        if (strcmp(categoria, no->mer.categoria) == 0) {
           printf("Indice: %d\n",indice);
           printf("Nome: %s\n", no->mer.nome);
           printf("Descricao: %s\n", no->mer.descricao);
           printf("Valor Unitario: %.2f\n", no->mer.preco);
           printf("Quantidade em Estoque: %d\n", no->mer.estoque);
           printf("Nota de Avaliacao: %.2f\n", no->mer.avaliacao);
           printf("Categoria: %s\n", no->mer.categoria);
           printf("Vendedor: %s\n", no->mer.vendedor);
           printf("Vendas: %d\n", no->mer.vendas);
           printf("--------------------------------------------------\n");
           encontrado = 1;
        }
        no = no->prox;
        indice++;
    }
    if(!encontrado){
        printf("\nERRO! Produto nao encontrado.\n");
        return 1;
      }else{
        return 0;
    }
}
//Funçao que verifica se um item esta presente em LP.
int contem(ListaProdutos *p, char *item){
    if (p == NULL) return -1;
    if (lisvp(p) == 0) return -2;
    Noprodutos *no = p->inicio;
    while(no != NULL){
        if(strcmp(no->mer.nome, item) == 0)
            return 0;
        no = no->prox;
    }
    return 1;
}
//Função que verifica o produto com maior quantidade de vendas.
int maiorvProduto(ListaProdutos *p, Mercadoria *m){
    if (p == NULL) return -1;
    if (lisvp(p) == 0) return -2;
    Noprodutos *no = p->inicio;
    int v = 0;
    while(no->prox != NULL){
        if(v < no->mer.vendas){
            *m = no->mer;
            v = no->mer.vendas;
        }
        no = no->prox;
    }
    return 1;
}

//Funçao que altera o estoque, a avaliaçao e o numero de vendas.
int remestoque(ListaProdutos *p, char *it, float nota, int qtd){
    if (p == NULL) return -1;
    if (lisvp(p) == 0) return -2;
    Noprodutos *no = p->inicio;
    while(strcmp(it, no->mer.nome) != 0){
        no = no->prox;
    }
    no->mer.estoque -= qtd;
    no->mer.avaliacao = ((no->mer.vendas * no->mer.avaliacao) + nota) / (no->mer.vendas + 1);
    no->mer.vendas += qtd;
    return 0;
}
//Funçao que insere um produto em LP.
int inserirProduto(ListaProdutos *p, Mercadoria me){
    if(p == NULL) return -2;

    Noprodutos *no = (Noprodutos*) malloc (sizeof(Noprodutos));
    no->mer = me;
    no->prox = p->inicio;
    p->inicio = no;
    return 0;
}
//Funçao que insere um item no final de LP.
int inserirProdfinal(ListaProdutos *p, Mercadoria me){
    if(p == NULL) return -2;
    if(lisvp(p) == 0) inserirProduto(p,me);
    Noprodutos *aux = p->inicio;
    while (aux->prox != NULL){
        aux = aux->prox;
    }
    Noprodutos *no = (Noprodutos*) malloc(sizeof(Noprodutos));
    no->mer = me;
    no->prox = aux->prox;
    aux->prox = no;
    return 0;
}
//Funçao que busca um item em LP.
int buspos(ListaProdutos *p, int pos, Mercadoria *retorno){
    if (p == NULL) return -2;
    if (lisvp(p) == 0) return -1;

    Noprodutos *no = p->inicio;
    int contador = 0;

    while(contador < pos){
        no = no->prox;
        contador++;
    }

    *retorno = no->mer;
    return 0;
}
//Funçao que insere os 5 produtos recomendados na lista de produtos recomendaveis(LPR).
int percorretipo5(ListaProdutos *p, char *categoria,ListaProdutos *m){
    if (p == NULL) return -1;
    if (lisvp(p) == 0) return -2;
    Noprodutos *no = p->inicio;
    int indice = 0;
    while (no != NULL && indice < 5) {
        if(strcmp(no->mer.categoria,categoria) == 0){
           inserirProduto(m,no->mer);
           indice++;
        }
        no = no->prox;
    }
    return 0;
}
//Funçao que insere os produtos pre cadastrados no programa.
int produtosIniciais(ListaProdutos *p){
    if(p == NULL) return -2;

        Mercadoria produtos[] = {
        {"Notebook SuperTech", "Potente notebook com processador de ultima geracao.", "Eletronicos", 3000.00, 4.6, 10, 0, 12, "EletronicosTopTech"},
        {"Notebook SuperTech", "Potente notebook com processador de ultima geracao.", "Eletronicos", 3500.00, 4.2, 16, 0, 21, "Tecnolife"},
        {"Smart TV UltraHD", "Televisao com resolucao 4K e tecnologia de ponta.", "Eletronicos", 2500.00, 4.8, 10, 0, 20, "EletronicosTopTech"},
        {"Smart TV UltraHD", "Televisao com resolucao 4K e tecnologia de ponta.", "Eletronicos", 2500.00, 4.3, 10, 0, 33, "Tecnolife"},
        {"Fone de Ouvido Bluetooth", "Fone sem fio com cancelamento de ruido e longa duracao de bateria.", "Eletronicos", 250.00, 4.0, 15, 0, 80, "EletronicosTopTech"},
        {"Fone de Ouvido Bluetooth", "Fone sem fio com cancelamento de ruido e longa duracao de bateria.", "Eletronicos", 200.00, 4.4, 10, 0, 24, "Tecnolife"},
        {"Console de Jogos GamerX", "Console de videogame com graficos de alta definicao e jogos exclusivos.", "Eletronicos", 4000.00, 4.7, 10, 0, 8, "EletronicosTopTech"},
        {"Console de Jogos GamerX", "Console de videogame com graficos de alta definicao e jogos exclusivos.", "Eletronicos", 3500.00, 4.9, 19, 0, 8, "Tecnolife"},
        {"Camera Digital Profissional", "Camera com sensor de alta resolucao e recursos avancados para fotografia.", "Eletronicos", 3500.00, 4.9, 10, 0, 15, "EletronicosTopTech"},
        {"Camera Digital Profissional", "Camera com sensor de alta resolucao e recursos avancados para fotografia.", "Eletronicos", 2600.00, 4.1, 16, 0, 25, "Tecnolife"},

        {"Maquina de Lavar Roupa", "Maquina automatica com capacidade para 10kg de roupas.", "Eletrodomesticos", 1500.00, 4.5, 10, 0, 22, "EletroFrio"},
        {"Maquina de Lavar Roupa", "Maquina automatica com capacidade para 10kg de roupas.", "Eletrodomesticos", 1800.00, 3.9, 21, 0, 15, "EletroHouse"},
        {"Aspirador de Po Robotico", "Aspirador inteligente que opera de forma autonoma.", "Eletrodomesticos", 800.00, 4.3, 10, 0, 30, "EletroFrio"},
        {"Aspirador de Po Robotico", "Aspirador inteligente que opera de forma autonoma.", "Eletrodomesticos", 600.00, 4.0, 17, 0, 30, "EletroHouse"},
        {"Geladeira Side by Side", "Geladeira de alta capacidade com design moderno.", "Eletrodomesticos", 3200.00, 4.7, 10, 0, 18, "EletroFrio"},
        {"Geladeira Side by Side", "Geladeira de alta capacidade com design moderno.", "Eletrodomesticos", 3500.00, 4.3, 10, 0, 20, "EletroHouse"},
        {"Fogao Cooktop 5 Bocas", "Fogao com queimadores eficientes e design elegante.", "Eletrodomesticos", 1200.00, 4.6, 10, 0, 25, "EletroFrio"},
        {"Fogao Cooktop 5 Bocas", "Fogao com queimadores eficientes e design elegante.", "Eletrodomesticos", 1400.00, 4.8, 11, 0, 28, "EletroHouse"},
        {"Forno Eletrico Multifuncional", "Forno com diversas funcoes de cozimento e controle digital.", "Eletrodomesticos", 900.00, 4.8, 10, 0, 20, "EletroFrio"},
        {"Forno Eletrico Multifuncional", "Forno com diversas funcoes de cozimento e controle digital.", "Eletrodomesticos", 850.00, 4.7, 15, 0, 49, "EletroHouse"},

        {"Carrinho de Controle Remoto", "Carrinho com controle remoto e alta velocidade.", "Brinquedos", 150.00, 4.4, 10, 0, 40, "BrincaZoom"},
        {"Carrinho de Controle Remoto", "Carrinho com controle remoto e alta velocidade.", "Brinquedos", 120.00, 4.0, 17, 0, 28, "ToyTopia"},
        {"Boneca Interativa", "Boneca que fala e interage com criancas.", "Brinquedos", 250.00, 4.6, 10, 0, 30, "BrincaZoom"},
        {"Boneca Interativa", "Boneca que fala e interage com criancas.", "Brinquedos", 220.00, 4.2, 16, 0, 20, "ToyTopia"},
        {"Quebra-Cabeca Desafio", "Quebra-cabeca com mil pecas para desafiar sua mente.", "brinquedos", 80.00, 4.5, 10, 0, 35, "BrincaZoom"},
        {"Quebra-Cabeca Desafio", "Quebra-cabeca com mil pecas para desafiar sua mente.", "Brinquedos", 65.00, 4.1, 18, 0, 25, "ToyTopia"},
        {"Boneco Articulado HeroiX", "Boneco colecionavel com articulacoes e detalhes realistas.", "Brinquedos", 50.00, 4.6, 10, 10, 35, "BrincaZoom" },
        {"Boneco Articulado HeroiX", "Boneco colecionavel com articulacoes e detalhes realistas.", "Brinquedos", 50.00, 4.3, 20, 19, 39, "KND" },
        {"Kit Criativo de Artesanato", "Conjunto com materiais para criar artesanatos diversos.", "Brinquedos", 60.00, 4.5, 11, 10, 28, "BrincaZoom" },
        {"Kit Criativo de Artesanato", "Conjunto com materiais para criar artesanatos diversos.", "Brinquedos", 60.00, 4.8, 12, 13, 21, "KND" },
        {"Kit Pintura Infantil", "Kit completo de pintura para criancas.", "Brinquedos", 90.00, 4.3, 10, 0, 20, "BrincaZoom"},
        {"Kit Pintura Infantil", "Kit completo de pintura para criancas.", "Brinquedos", 75.00, 4.0, 14, 0, 30, "ToyTopia"},
        {"Patinete Infantil Colorido", "Patinete resistente com design atrativo para criancas.", "Brinquedos", 120.00, 4.8, 12, 10, 25, "BrincaZoom" },
        {"Patinete Infantil Colorido", "Patinete resistente com design atrativo para criancas.", "Brinquedos", 110.00, 4.5, 11, 15, 21, "KND" },
        {"Bicicleta Infantil", "Bicicleta colorida com rodinhas de apoio.", "Brinquedos", 300.00, 4.7, 10, 0, 12, "BrincaZoom"},
        {"Bicicleta Infantil", "Bicicleta colorida com rodinhas de apoio.", "Brinquedos", 280.00, 4.4, 16, 0, 18, "ToyTopia"},

        {"Monitor Cardiaco Inteligente", "Monitor de frequencia cardiaca com conectividade Bluetooth.", "Saude", 180.00, 4.6, 10, 10, 32, "SaudeEmCasa" },
        {"Monitor Cardiaco Inteligente", "Monitor de frequencia cardiaca com conectividade Bluetooth.", "Saude", 170.00, 4.5, 10, 67, 32, "GoodLife" },
        {"Massageador Shiatsu", "Massageador com tecnologia Shiatsu para relaxamento muscular.", "Saude", 250.00, 4.7, 10, 10, 20, "SaudeEmCasa" },
        {"Massageador Shiatsu", "Massageador com tecnologia Shiatsu para relaxamento muscular.", "Saude", 210.00, 4.0, 10, 15, 20, "GoodLife" },
        {"Kit Primeiros Socorros", "Kit completo para emergencias medicas em casa ou viagens.", "Saude", 120.00, 4.5, 10, 10, 25, "SaudeEmCasa" },
        {"Kit Primeiros Socorros", "Kit completo para emergencias medicas em casa ou viagens.", "Saude", 150.00, 4.8, 19, 10, 30, "GoodLife" },
        {"Balanca Digital de Precisao", "Balanca com alta precisao para controle de peso e saude.", "Saude", 70.00, 4.4, 10, 10, 40, "SaudeEmCasa" },
        {"Balanca Digital de Precisao", "Balanca com alta precisao para controle de peso e saude.", "Saude", 60.00, 4.8, 20, 10, 50, "GoodLife" },
        {"Termometro Infravermelho", "Termometro sem contato para medicao rapida e precisa de temperatura.", "Saude", 100.00, 4.8, 10, 10, 18, "SaudeEmCasa" },
        {"Termometro Infravermelho", "Termometro sem contato para medicao rapida e precisa de temperatura.", "Saude", 150.00, 4.6, 11, 10, 33, "GoodLife" },

        {"Bicicleta Mountain Bike", "Bicicleta robusta para trilhas e aventuras off-road.", "Esporte", 1500.00, 4.6, 10, 0, 15, "BikeAventura" },
        {"Bicicleta Mountain Bike", "Bicicleta robusta para trilhas e aventuras off-road.", "Esporte", 1300.00, 4.9, 16, 0, 11, "EuroBike" },
        {"Tenis de Corrida Profissional", "Tenis leve e confortavel para corridas de longa distancia.", "Esporte", 300.00, 4.8, 10, 0, 28, "BikeAventura" },
        {"Tenis de Corrida Profissional", "Tenis leve e confortavel para corridas de longa distancia.", "Esporte", 300.00, 4.9, 13, 0, 39, "EuroBike" },
        {"Bola de Basquete Oficial", "Bola oficial para jogos de basquete em quadras profissionais.", "Esporte", 150.00, 4.7, 10, 0, 32, "BikeAventura" },
        {"Bola de Basquete Oficial", "Bola oficial para jogos de basquete em quadras profissionais.", "Esporte", 150.00, 4.3, 15, 0, 39, "EuroBike" },
        {"Skate Longboard Freestyle", "Skate longboard para manobras e estilo livre.", "Esporte", 250.00, 4.5, 10, 0, 20, "BikeAventura" },
        {"Skate Longboard Freestyle", "Skate longboard para manobras e estilo livre.", "Esporte", 300.00, 4.8, 21, 0, 26, "EuroBike" },
        {"Luvas de Boxe Profissional", "Luvas de alta qualidade para treinos e competicoes de boxe.", "Esporte", 180.00, 4.9, 10, 0, 15, "BikeAventura" },
        {"Luvas de Boxe Profissional", "Luvas de alta qualidade para treinos e competicoes de boxe.", "Esporte", 200.00, 5.0, 13, 0, 40, "EuroBike" }
    };

    int i = 0;
    while(i < 56){
        strlwr(produtos[i].categoria);
        inserirProduto(p,produtos[i]);
        i++;
    }
    return 0;

    }
