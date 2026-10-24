CC = gcc
CFLAGS = -Wall -Wextra -std=c99

sintatico: main.o sintatico.o lexico.o
	$(CC) $(CFLAGS) -o sintatico main.o sintatico.o lexico.o

main.o: main.c sintatico.h lexico.h
	$(CC) $(CFLAGS) -c main.c
sintatico.o: sintatico.c sintatico.h lexico.h
	$(CC) $(CFLAGS) -c sintatico.c
lexico.o: lexico.c lexico.h
	$(CC) $(CFLAGS) -c lexico.c

clean:
	rm -f *.o sintatico
