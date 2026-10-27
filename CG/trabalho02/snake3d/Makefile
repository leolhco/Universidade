CC      := gcc
CFLAGS  := -std=c11 -Wall -Wextra -O2 $(shell pkg-config --cflags sdl2)
LDFLAGS := $(shell pkg-config --libs sdl2) -lm

# Engine (unchanged) + game modules
SRC := \
	vec.c mat.c canvas.c camera.c mesh.c obj.c \
	raster.c shader.c program.c \
	arena.c snake.c render_util.c game.c \
	main.c

OBJ := $(SRC:.c=.o)
BIN := snake3d

.PHONY: all clean run

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(BIN)
	./$(BIN)

clean:
	rm -f $(OBJ) $(BIN)
