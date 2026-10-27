# Variáveis
CC = gcc
CFLAGS = -Wall -O2
OBJ = arvoreBinaria.o arvoreAVL.o pesquisaBinaria.o main.o 
DEPS = arvoreAVL.h arvoreBinaria.h estruturas.h pesquisaBinaria.h

# Verificar sistema operacional
ifeq ($(OS), Windows_NT)
    RM = del /Q
    EXEC = programa.exe
else
    RM = rm -f
    EXEC = programa
endif

# Alvo principal
all: $(EXEC)

# Compilação do executável
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ) -lm

# Compilação dos arquivos .o
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpar os arquivos gerados
clean:
	$(RM) $(OBJ) $(EXEC)

# Dependências adicionais
.PHONY: all clean

