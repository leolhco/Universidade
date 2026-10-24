:- use_module(library(http/thread_httpd)).
:- use_module(library(http/http_dispatch)).
:- use_module(library(http/http_parameters)).
:- use_module(library(http/html_write)). 
:- use_module(library(uri)).

:- dynamic(nomeCliente/2).
:- dynamic(telCliente/2).
:- dynamic(pedido/7).


:- http_handler(root(processa_pedido), fazPed, []).
:- http_handler(root(cancelar_ped), cancelaPed, []).

:- initialization(carregaPedidos).

servidor(Porta) :-
    http_server(http_dispatch, [port(Porta)]).

fazPed(R) :-
     http_parameters(R, [
        nomeCliente(C, []),
        telCliente(T, []),
        emailCliente(E, []),
        tamanho(S, []),
        ing(I, [list(multiple)]),
        tempo(H, []),
        obs(O, [])
    ]),
    format('Content-type: text/plain~n~n'),
    format('Pedido recebido com sucesso!~n'),
    format('Nome: ~w~n', [C]),
    format('Telefone: ~w~n', [T]),
    format('E-mail: ~w~n', [E]),
    format('Tamanho: ~w~n', [S]),
    format('Ingredientes: ~w~n', [I]),
    format('Tempo: ~w~n', [H]),
    format('Observações: ~w~n', [O]).
    assertz(pedido(C, T, E, S, I, H, O)),
    salvaPedidos.
    
cancelaPed(R) :-
    http_parameters(R, [
        nomeCliente(C, []),
        telCliente(T, []),
        emailCliente(E, [])
    ]),
    format('Content-type: text/plain~n~n'),
    format('Pedido cancelado com sucesso!~n'),
    format('Nome: ~w~n', [C]),
    format('Telefone: ~w~n', [T]),
    format('Email: ~w~n', [E]).
    retract(pedido(C, T, E, _, _, _, _)),
    salvaPedidos.


salvaPedidos :-
    tell('pedidos.pl'),
    listing(pedido/7),
    told.


carregaPedidos :-
    exists_file('pedidos.pl'),
    consult('pedidos.pl').