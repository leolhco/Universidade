# Nome do executável
EXEC = programa_grafo

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -g

# Arquivos de objeto
OBJ = main.o grafo.o

# Regra principal
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

# Compilar main.o
main.o: main.c grafo.h
	$(CC) $(CFLAGS) -c main.c

# Compilar grafo.o
grafo.o: grafo.c grafo.h
	$(CC) $(CFLAGS) -c grafo.c

# Limpeza de arquivos temporários (objetos)
clean:
	rm -f *.o $(EXEC)

# Regra para limpar arquivos objeto e binário
