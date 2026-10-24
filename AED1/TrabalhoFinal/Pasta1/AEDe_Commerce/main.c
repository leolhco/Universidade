#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ecommerce.h"

//Diogo Vieira de Castro (12311BCC002)
//Guilherme Willians Silva (12311BCC031)
//Leonardo H. C. Oliveira (12311BCC003)
//Paulo Otávio Guerreiro Souza (12311BCC007)

float notaS = 0.0;
int qtdNotaS = 0;
float mediaNotas = 0;

float calcularMediaNotas() {
    if (qtdNotaS == 0) {
        return 0.0;  // Retorna 0 se nenhuma nota foi registrada para evitar divisão por zero
    }
    return notaS / qtdNotaS;
}

int boleto = 0;
int pix = 0;
int cartao = 0;

int main(){
    srand(time(NULL)); /*Função da biblioteca stdlib.h que inicializa o gerador de números aleatórios srand
                         com uma semente baseada no tempo atual obtido pela função time(NULL) da biblioteca time.h .*/

    ListaProdutos *lp = criarProdutos();
    ListaProdutos *recomenda = criarProdutos();
    ListaCategorias *lcategorias = criarLcategoria();
    Listausuario *lu = criarlu();
    Carrinho *carrinho1 = criarc();
    Vendedor *vendedor1 = criarv();
    Nousuario *conta;
    Novendedor *contav;
    Pilhahistorico* hc = criarhist();

    produtosIniciais(lp);
    usuariosIniciais(lu);
    vendedoresIniciais(vendedor1);
    categoriasIniciais(lcategorias);


    int escolha;
    printf("------------- SEJA BEM VINDO! -------------\n");

    while(escolha != 1){
        printf("\n(1) Fazer login como cliente\n(2) Cadastrar cliente\n(3) Fazer login como vendedor\n(4) Cadastrar vendedor\n");
        fflush(stdin);
        printf("\nEscolha: ");
        scanf("%d", &escolha);
        switch (escolha){
            case 1: { //Faz login como cliente.
                system("cls");

                printf ("Contas cadastradas previamente:\n\nUsuario: professor\nSenha: professor\n");
                printf("----------------------------------\n");
                printf("Usuario: monitor\nSenha: monitor\n");

                char usuario[20];
                char senha[25];
                printf("\nDigite o seu usuario: ");
                fflush(stdin);
                fgets(usuario, 20, stdin);
                printf("\nDigite a sua senha: ");
                fflush(stdin);
                fgets(senha, 25, stdin);
                fflush(stdin);
                int tamusuario = strlen(usuario);
                int tamsenha = strlen(senha);

                usuario[tamusuario - 1] = '\0'; //Substitui o "Enter" digitado pelo usuario da string por '\0'.
                senha[tamsenha - 1] = '\0'; //Substitui o "Enter" digitado pelo usuario da string por '\0'.


                int encontrado = bususer(lu, usuario, senha, &conta);

                if (encontrado == -3){
                    escolha = 0;

                    system("cls");

                    printf("\nSua senha est� incorreta \n");
                }
                else if (encontrado == -4){
                    escolha = 0;

                    system("cls");

                    printf("\nUsuario nao existe, verifique se digitou corretamente.\n\n");
                }

                break;
            }

            case 2: { //Cadastra um novo usuario.

                system("cls");

                Cliente newc;

                printf("\nDigite o seu nome\n\n");
                fflush(stdin);
                fgets(newc.nome, 30, stdin);
                int tamnewc = strlen(newc.nome);
                newc.nome[tamnewc - 1] = '\0'; //Substitui o "Enter" digitado pelo usuario da string por '\0'.

                printf("\nDigite o seu usuario\n\n");
                fflush(stdin);
                fgets(newc.us, 20, stdin);
                int tamus = strlen(newc.us);
                newc.us[tamus - 1] = '\0'; //Substitui o "Enter" digitado pelo usuario da string por '\0'.

                printf("\nDigite a sua senha\n\n");
                fgets(newc.senha, 25, stdin);
                int tams = strlen(newc.senha);
                newc.senha[tams - 1] = '\0'; //Substitui o "Enter" digitado pelo usuario da string por '\0'.

                insiu(lu, newc); //Insere a conta em LU.

                break;
            }

            case 3: { //Faz login como vendedor.
                system("cls");

                printf ("Contas cadastradas previamente:\n\nLoja: professorv\nSenha: professorv\n");

                char nome[20];
                char senha[25];
                printf("\nDigite o nome da loja: ");
                fflush(stdin);
                fgets(nome, 30, stdin);
                printf("\n\nDigite a senha: ");
                fflush(stdin);
                fgets(senha, 25, stdin);
                fflush(stdin);
                int tamloja = strlen(nome);
                int tamsenha = strlen(senha);

                nome[tamloja - 1] = '\0'; //Substitui o "Enter" digitado pelo usuario da string por '\0'.
                senha[tamsenha - 1] = '\0'; //Substitui o "Enter" digitado pelo usuario da string por '\0'.


                int encontrado = busvendedor(vendedor1, nome, senha, &contav);

                if (encontrado == -3){
                    escolha = 0;

                    system("cls");

                    printf("\nSua senha est� incorreta \n");
                }
                else if (encontrado == -4 || encontrado == -2){
                    escolha = 0;

                    system("cls");

                    printf("\nLoja nao existe, verifique se digitou corretamente.\n\n");
                }

                break;
            }

            case 4: {

                system("cls");

                Vendedor newv;

                printf("\nDigite o nome da loja\n\n");
                fflush(stdin);
                fgets(newv.nome, 30, stdin);
                int tamnewv = strlen(newv.nome);
                newv.nome[tamnewv - 1] = '\0'; //Substitui o "Enter" digitado pelo usuario da string por '\0'.

                printf("\nDigite a senha\n\n");
                fgets(newv.senha, 25, stdin);
                int tams = strlen(newv.senha);
                newv.senha[tams - 1] = '\0'; //Substitui o "Enter" digitado pelo usuario da string por '\0'.

                printf("\nCategoria de vendas\n\n");
                fgets(newv.tipo, 25, stdin);
                int tamt = strlen(newv.tipo);
                newv.tipo[tamt - 1] = '\0'; //Substitui o "Enter" digitado pelo usuario da string por '\0'.

                insiv(vendedor1, newv); //Insere a conta em LV.
                system("cls");

                break;
            }



            default:
                system("cls");

                printf("\nDigite uma opcao valida!\n\n");
                break;
        }

            while(escolha == 3){
              system("cls");
              printf("\n(1) Adicionar produto\n");
              printf("\n(2) Voltar tela inicial\n");
              int opcao = 0;
              printf("\nEscolha: ");
              scanf("%d",&opcao);
              if(opcao == 1) {
                system("cls");
                Mercadoria produto1;
                printf("\nDigite o nome do produto: ");
                fflush(stdin);
                fgets(produto1.nome,40,stdin);
                printf("\nDigite a categoria do produto: ");
                fflush(stdin);
                int tampnome = strlen(produto1.nome);
                produto1.nome[tampnome - 1] = '\0';  //Substitui o "Enter" digitado pelo usuario da string por '\0'.
                fgets(produto1.categoria,40,stdin);
                int tampcat = strlen(produto1.categoria);
                produto1.categoria[tampcat - 1] = '\0';  //Substitui o "Enter" digitado pelo usuario da string por '\0'.
                printf("\nDigite a descricao do produto: ");
                fflush(stdin);
                fgets(produto1.descricao,40,stdin);
                int tampdescricao = strlen(produto1.descricao);
                produto1.descricao[tampdescricao - 1] = '\0';  //Substitui o "Enter" digitado pelo usuario da string por '\0'.
                printf("\nDigite o preco: ");
                fflush(stdin);
                scanf("%f",&produto1.preco);
                printf("\nDigite a quantidade em estoque: ");
                fflush(stdin);
                scanf("%d",&produto1.estoque);
                strcpy(produto1.vendedor,contav->loja.nome);
                produto1.carrinho = 0;
                produto1.avaliacao = 0.0;
                produto1.vendas = 0;
                inserirProdfinal(lp,produto1);
                int a = categoriainLcategoria(produto1.categoria,lcategorias);
                if (a == 0){
                    Categoria t;
                    strlwr(produto1.categoria);
                    strcpy(t.nome,produto1.categoria);
                    insic(lcategorias,t);
                }
                system("cls");
              }else {
                  escolha = 0;
                  system("cls");
                  printf("Saindo\n");
                  fflush(stdin);
              }
        }
    }

    if(strcmp(conta->cl.nome,"professor") == 0 ) {
        Mercadoria m1;
        buspos(lp,42,&m1);
        inserirProduto(hc,m1);
    }else if(strcmp(conta->cl.nome,"monitor") == 0 ) {
        Mercadoria m1;
        buspos(lp,18,&m1);
        inserirProduto(hc,m1);
    }

    system("cls"); //Busca as Recomendaçoes.
    printf("\nProdutos recomendados :\n\n");
    fflush(stdin);
    int rel = 0;
    if(lisvp(hc) == 0){ //Caso a  pilha historico estiver vazia, adiciona 5 produtos aleatorios na lista de recomendaveis.
        Mercadoria m1;
        Mercadoria m2;
        Mercadoria m3;
        Mercadoria m4;
        Mercadoria m5;
        rel = rand() % 55;
        buspos(lp,rel,&m1);
        rel = rand() % 55;
        buspos(lp,rel,&m2);
        rel = rand() % 55;
        buspos(lp,rel,&m3);
        rel = rand() % 55;
        buspos(lp,rel,&m4);
        rel = rand() % 55;
        buspos(lp,rel,&m5);

        inserirProduto(recomenda,m1);
        inserirProduto(recomenda,m2);
        inserirProduto(recomenda,m3);
        inserirProduto(recomenda,m4);
        inserirProduto(recomenda,m5);
    }else {
        percorretipo5(lp, hc->topo->mer.categoria,recomenda);
    }
    showp(recomenda);
    char resposta;
    printf("\nDeseja colocar algum dos itens no carrinho? s(sim)/n(nao)\n\n"); //Recomenda 5 produtos relacionados ao usuario, e verifica se o ele quer colocar algum no carrinho.
    fflush(stdin);
    scanf("%c", &resposta);
    if (resposta == 's' || resposta == 'S'){
        printf("\nQual? (Digite o indice)\n\n");
        int indice;
        scanf("%d", &indice);
        printf("\nQuantos?\n\n");
        int qtd;
        scanf("%d", &qtd);
        Mercadoria ret;
        buspos(recomenda, indice, &ret);
        insc(carrinho1, qtd, ret);
        system("cls");
    }
    else if (resposta == 'n' || resposta == 'N'){
        system("cls");
    }
    escolha = 0;

    while(escolha != 7){
        printf("\nMenu Principal\n");
        printf("\n1 - Mostrar todos os produtos\n2 - Procurar produto pelo nome\n3 - Procurar produto pela categoria\n4 - Mostrar carrinho\n5 - Historico de compras\n6 - Relatorios\n7 - Sair\n\n");
        fflush(stdin);
        scanf("%d", &escolha);
        switch (escolha){
            case 1:{ //Exibe todos os produtos na tela e verifica se o usuario quer colocar algum no carrinho.

                system("cls");
                showp(lp);
                printf("\nDeseja colocar algum dos itens no carrinho? s(sim)/n(nao)\n\n");
                fflush(stdin);
                scanf("%c", &resposta);
                int qtd = 0;
                if (resposta == 's' || resposta == 'S'){
                    printf("\nQual? (Digite o indice)\n\n");
                    int indice;
                    scanf("%d", &indice);
                    printf("\nQuantos?\n\n");
                    int qtd;
                    scanf("%d", &qtd);
                    Mercadoria ret;
                    buspos(lp, indice, &ret);
                    insc(carrinho1, qtd , ret);


                }
                else if (resposta == 'n' || resposta == 'N'){
                    system("cls");
                    printf("\nVoltando ao menu principal\n\n");
                    escolha = 0;
                }
                else{
                    system("cls");
                    printf("\nEscolha invalida! Voltando ao menu principal\n\n");
                    escolha = 0;
                }
                system("cls");
                   if (qtd>0) printf("\nProduto adicionado ao carrinho com sucesso, indo para -o menu!\n\n");
                break;
            }

            case 2:{ //Permite que o usuario faça uma busca por nome da lista de produtos.

                system("cls");
                char prodname[40];
                printf("\nDigite o nome do produto:\n\n");
                fflush(stdin);
                fgets(prodname, 40, stdin);
                int qtd = 0;
                int tamname = strlen(prodname);
                prodname[tamname - 1] = '\0';  //Substitui o "Enter" digitado pelo usuario da string por '\0'.

                system("cls");

                if(showbyname(lp, prodname) == 1){
                    printf("\nNao encontramos nenhum produto com esse nome, tente novamente\n\n");
                    break;
                }
                printf("\nDeseja colocar algum dos itens no carrinho? s(sim)/n(nao)\n\n");
                fflush(stdin);
                scanf("%c", &resposta);
                if (resposta == 's' || resposta == 'S'){
                    printf("\nQual? (Digite o indice)\n\n");
                    int indice;
                    scanf("%d", &indice);
                    printf("\nQuantos?\n\n");
                    scanf("%d", &qtd);
                    Mercadoria ret;
                    buspos(lp, indice, &ret);
                    insc(carrinho1, qtd, ret);
                }
                else if (resposta == 'n' || resposta == 'N'){
                    system("cls");
                    printf("\nVoltando ao menu principal\n\n");
                    escolha = 0;
                }
                else{
                    system("cls");
                    printf("\nOpcao invalida! Voltando ao menu principal\n\n");
                    escolha = 0;
                }
                system("cls");
                   if (qtd>0) printf("\nProduto adicionado ao carrinho com sucesso, retornando ao menu!\n\n");
                break;
            }

            case 3:{  //Permite que o usuario faça uma busca por categoria da lista de produtos.

                system("cls");
                char categoria[40];
                printf("\nCategorias existentes:\n");
                showcategorias(lcategorias);
                printf("\nDigite a categoria :\n\n");
                fflush(stdin);
                fgets(categoria, 40, stdin);
                int qtd = 0;
                int tamcategoria = strlen(categoria);
                categoria[tamcategoria - 1] = '\0';  //Substitui o "Enter" digitado pelo usuario da string por '\0'.

                if(showbytype(lp, categoria) == 1){
                    system("cls");
                    printf("\nEssa categoria nao existe, tente novamente\n\n");
                    break;
                }
                printf("\nDeseja colocar algum dos itens no carrinho? s(sim)/n(nao)\n\n");
                fflush(stdin);
                scanf("%c", &resposta);
                if (resposta == 's' || resposta == 'S'){
                    printf("\nQual? (Digite o indice)\n\n");
                    int indice;
                    scanf("%d", &indice);
                    printf("\nQuantos?\n\n");
                    scanf("%d", &qtd);
                    Mercadoria ret;
                    buspos(lp, indice, &ret);
                    insc(carrinho1, qtd, ret);

                }
                else if (resposta == 'n' || resposta == 'N'){
                    system("cls");
                    printf("\nVoltando ao menu principal\n\n");
                    escolha = 0;
                }
                else{
                    system("cls");
                    printf("\eEscolha invalida! Voltando ao menu principal\n\n");
                    escolha = 0;
                }
                system("cls");

                if (qtd>0) printf("\nProduto adicionado ao carrinho com sucesso, retornando ao menu!\n\n");
                break;
            }

            case 4:{  //Acessa o carrinho, permitindo deletar um produto ou confirmar compra.
                system("cls");
                showc(carrinho1);
                printf("\nD - Deletar produto do carrinho\nC - Confirmar compra\nS - Sair do carrinho\n\n");
                char opc;
                fflush(stdin);
                scanf("%c", &opc);
                if(lisvc(carrinho1) == 0 && opc != 's' && opc != 'S'){
                    system("cls");
                    printf("Nao existe nenhum item no carrinho.\n\n");
                    break;
                }
                if (opc == 'd' || opc == 'D'){
                    printf("\nDigite o indice: \n\n");
                    int indice;
                    scanf("%d", &indice);
                    printf("\nQuantos?\n\n");
                    int qtd;
                    scanf("%d", &qtd);
                    if (indice <= tamc(carrinho1)) remqtdc(carrinho1,qtd, indice);
                    system("cls");
                    break;
                }
                if (opc == 'c' || opc == 'C'){
                    printf("\nR$ %.2f", totalc(carrinho1));
                    printf("\nDeseja finalizar a compra? s(sim)/n(nao)\n\n");
                    fflush(stdin);
                    char opconfirmar;
                    scanf("%c", &opconfirmar);
                    if(opconfirmar == 's' || opconfirmar == 'S'){
                        int entregue = 1;
                        int pagamento;
                        printf("Qual a forma de pagamento?\n(1) - Cartao de credito\n(2) - Pix\n(3) - Boleto\n");
                        scanf("%d",&pagamento);
                        printf("\nPagamento efetuado com sucesso!\n");
                        printf("\nMuito obrigado pela compra!\n\n");
                        if(pagamento == 1){
                            cartao++;
                        }else if(pagamento == 2){
                            pix++;
                        }else if(pagamento == 3){
                            boleto++;
                        }

                        while(entregue != 0){
                            char verifica;
                            printf("Confirme que o produto foi entregue! (S) Sim (N) Nao\n");
                            fflush(stdin);
                            scanf("%c",&verifica);
                            if(verifica == 'S'||verifica == 's'){
                                entregue = 0;
                            }
                        }
                        int nota;
                        Nocarrinho* no = carrinho1->inicio;
                        while(no != NULL){
                            Mercadoria m;
                            m = no->mer;
                            no = no->prox;
                            push(hc, m);
                        }
                        while(lisvc(carrinho1) != 0){
                            char *produtoRemover = retornafinalizarcompra(carrinho1);
                            int qtdCarrinho = retornaqtdcompra(carrinho1);
                            printf("\nAvalie o produto %s comprado de 1 a 5:\n\n", produtoRemover);
                            fflush(stdin);
                            scanf("%d",&nota);
                            switch (nota)
                            {
                            case 1:
                                printf("\nQualidade insatisfatória. O produto não atendeu às expectativas, apresentando diversos problemas.\n\n");
                                break;

                            case 2:
                                printf("\nQualidade razoável. O produto possui algumas falhas, mas ainda é utilizável com algumas limitações.\n\n");
                                break;

                            case 3:
                                printf("\nBoa qualidade. O produto atende às necessidades básicas, mas possui margem para melhorias.\n\n");
                                break;

                            case 4:
                                printf("Qualidade muito boa. O produto superou as expectativas, oferecendo um desempenho satisfatório.\n\n");
                                break;
                            case 5:
                                printf("Excelente qualidade. O produto é altamente recomendado, atendendo completamente às expectativas e oferecendo uma experiência excepcional.\n\n");
                                break;

                            default:
                                printf("Nota inválida. Por favor, escolha uma nota de 1 a 5.\n\n");
                                break;
                            }
                            nota = 0;
                            printf("De 1 a 5, o quanto voce recomenda o e-commerce?\n");
                            fflush(stdin);
                            scanf("%d", &nota);

                            float nota0 = (float)nota;
                             switch (nota)
                            {
                            case 1:
                                printf("Experiencia insatisfatoria. O e-commerce apresentou problemas frequentes e nao atendeu as expectativas.\n\n");
                                notaS = notaS + nota0;
                                qtdNotaS++;
                                mediaNotas = calcularMediaNotas();
                                printf("\nSaindo...\n");
                                break;

                            case 2:
                                printf("Recomendacao razoavel. O e-commerce tem potencial, mas alguns aspectos precisam ser melhorados para uma experiencia mais satisfatoria.\n\n");
                                notaS = notaS + nota0;
                                qtdNotaS++;
                                mediaNotas = calcularMediaNotas();
                                printf("\nSaindo...\n");
                                break;

                            case 3:
                                printf("Recomendacao positiva. O e-commerce oferece uma boa variedade de produtos e um servico satisfatorio.\n\n");
                                notaS = notaS + nota0;
                                qtdNotaS++;
                                mediaNotas = calcularMediaNotas();
                                printf("\nSaindo...\n");
                                break;

                            case 4:
                                printf("Recomendacao muito boa. O e-commerce e confiavel, oferece uma excelente experiencia de compra e bom suporte ao cliente.\n\n");
                                notaS = notaS + nota0;
                                qtdNotaS++;
                                mediaNotas = calcularMediaNotas();
                                printf("\nSaindo...\n");
                                break;

                            case 5:
                                printf("Recomendacao excepcional. O e-commerce se destaca pela qualidade dos produtos, facilidade de navegacao e atendimento ao cliente exemplar. Altamente recomendado!\n\n");
                                notaS = notaS + nota0;
                                qtdNotaS++;
                                mediaNotas = calcularMediaNotas();
                                printf("\nSaindo...\n");
                                break;

                            default:
                                printf("Nota inválida. Por favor, escolha uma nota de 1 a 5.\n\n");
                            }
                            remestoque(lp, produtoRemover, nota, qtdCarrinho);
                            remposc(carrinho1,0);
                            printf("Esperamos que possa retornar mais vezes, ate a proxima!\n\n");
                        }
                        system("cls");
                        break;
                    }
                    else if (opconfirmar == 'n' || opconfirmar == 'N'){
                        system("cls");
                        printf("\nVoltando ao menu principal\n\n");
                        escolha = 0;
                        break;
                    }
                    else{
                        system("cls");
                        printf("\nEscolha invalida! Voltando ao menu principal\n\n");
                        escolha = 0;
                        break;
                    }
                }
                if (opc == 's' || opc == 'S'){
                    system("cls");
                    printf("\nVoltando ao menu principal\n\n");
                    escolha = 0;
                    break;
                }
                printf("\nOpcao invalida! Voltando ao menu principal\n\n");
                escolha = 0;

            }
            case 5:{ //Mostra o historico de compras.
                system("cls");
                showhist(hc);
                break;
            }

            case 6: {
                system("cls");
                Mercadoria m;
                maiorvProduto(lp,&m);
                printf("Nota media e-commerce : %.2f\n",mediaNotas);
                printf("\nProduto mais vendido: %s ,quantidade de vendas: %d\n",m.nome,m.vendas);
                printf("\nPagamentos feitos no Pix: %d\n",pix);
                printf("Pagamentos feitos no Cartao: %d\n",cartao);
                printf("Pagamentos feitos no Boleto: %d\n",boleto);

                char aperte;
                printf("\n(1) Voltar: ");
                fflush(stdin);
                scanf("%c",&aperte);
                system("cls");
                break;
            }

            case 7:{ //Sai do programa.
                printf("\nSaindo...\n");
                break;
            }
            default:
                system("cls");
                printf("\nDigite uma opcao valida!\n\n");
                break;
        }
    }

    system("Pause");
    return 0;
}
