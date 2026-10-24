/*
INTEGRANTES:
  CAIO OLIVEIRA LIMA - 12411BCC065
  DIOGO KOICHI CRUZ YONEMOTO - 12311BCC010
  JOAO VICTOR DAVI DE OLIVEIRA - 12311BCC015
  LEONARDO HENRIQUE CARVALHO OLIVEIRA - 12311BCC003
  YAN LUCAS SANTOS MARRA - 12311BCC013
*/

:-dynamic(telefone_de/2).

menu:-
	consult('kb.pl'),
	repeat,
	mostrar_op(X),
	(X =:= 8 ->
	!;
	executar_op(X),
		fail).

mostrar_op(X):-
	nl,
	write('1 - Obter o telefone de um assinante'),
	nl,
	write('2 - Adicionar um assinante'),
	nl,
	write('3 - Atualizar o telefone de um assinante'),
	nl,
	write('4 - Remover um assinante'),
	nl,
	write('5 - Listar todos os assinantes'),
	nl,
	write('6 - Buscar assinantes por prefixo de telefone'),
	nl,
	write('7 - Validar se o telefone pertence a algum assinante'),
	nl,
	write('8 - Sair'),
	nl,
	nl,
	ler(X).

ler(X):-
	scan(Aux),
	name(X, Aux).

scan(Aux):-
	get0(C),
	tratar(C, Aux).

tratar(-1, []):-
	!. 
tratar(10, []):-
	!.
tratar(13, []):-
	!.
tratar(C, [C|R]):-
	scan(R).

existe(X):-
	telefone_de(X, _).

tam(X, Y):-
	atom_length(X, T),
	validar(T, Y).

validar(8, _):-
	!.
validar(_, X):-
	nl,
	write('Digite um valor valido'),
	cadastroN(X).         

cadastroN(X):-
	nl,
	write('Digite o numero: '),
	ler(Y),
	tam(Y, X),
	(numero_existe(Y) ->
	write('O numero ja existe na base de dados.'),
		cadastroN(X);
	assertz(telefone_de(X, Y)),
		tell('kb.pl'),
		listing(telefone_de/2),
		told).

remT(X):-
	nl,
	retract(telefone_de(X, _)),
	tell('kb.pl'),
	listing(telefone_de/2),
	told.

atualizeT(X):-
		remT(X),
	cadastroN(X).

executar_op(1):-
	nl,
	write('Digite o nome do assinante: '),
	ler(X),
	(existe(X) ->
	telefone_de(X, Y),
		write('Nome: '),
		write(X),
		nl,
		write('Numero: '),
		write(Y),
		nl;
	cadastroN(X)),
	write(X),
	write(' esta cadastrado.'),
	nl,
	!.

executar_op(2):-
	nl,
	write('Digite o nome do assinante: '),
	ler(X),
	(existe(X) ->
	write('O Assinante ja existe na base de dados.');
	cadastroN(X)),
	write(X),
	write(' cadastrado com sucesso!'),
	nl,
	!.

executar_op(3):-
	nl,
	write('Digite o nome do assinante: '),
	ler(X),
	(existe(X) ->
	atualizeT(X),
		write(X),
		write(' atualizado com sucesso!');
	write('O assinante nao existe na base de dados.')),
	nl,
	!.

executar_op(4):-
	nl,
	write('Digite o nome do assinante: '),
	ler(X),
	(existe(X) ->
	 remT(X),
		write(X),
		write(' removido com sucesso!');
		write('O assinante nao existe na base de dados.')),
	nl,
	!.

/*REQUISITO EXTRA*/
executar_op(5):-
	nl,
	write('Lista de assinantes cadastrados:'),
	nl,
	lista_assinantes.
executar_op(5):-
	nl,
	write('Fim da lista de assinantes cadastrados.'),
	nl,
	!.

/*REQUISITO EXTRA*/
executar_op(6):-
	nl,
	write('Digite o prefixo(Os 4 primeiros digitos): '),
	ler(X),
	telefone_de(Y, Z),
	sub_atom(Z, 0, 4, _, X),
	write('Nome: '),
	write(Y),
	nl,
	write('Numero: '),
	write(Z),
	nl,
	fail.
executar_op(6):-
	nl,
	write('Fim da busca por prefixo.'),
	nl,
	!.

/*REQUISITO EXTRA*/
executar_op(7) :-
	nl,
	write('Digite o numero: '),
	ler(X),
	(busca_pelo_numero(X) ->
	write('O numero existe na base de dados.');
	write('O numero nao existe na base de dados.')),
	nl,
	!.

exexecutar_op(_):-
	write('Digite um valor valido').

numero_existe(X):-
	telefone_de(_, X).

busca_pelo_numero(X):-
	telefone_de(Y, X),
	write('Nome: '),
	write(Y),
	nl,
	write('Numero: '),
	write(X),
	nl.

lista_assinantes:-
	telefone_de(X, Y),
	write('Nome: '),
	write(X),
	nl,
	write('Numero: '),
	write(Y),
	nl,
	fail.