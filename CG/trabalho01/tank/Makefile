CC = gcc
CCFLAGS = -Wall -Wextra -Werror -pedantic -Wpointer-arith -O3
LDFLAGS = -lm -lSDL2 

LIB = ../lib
LIB_SRC = $(LIB)/src
LIB_INCLUDE = $(LIB)/include

SRC = ./

BUILD = ./build
BIN = ./bin
TARGET = $(BIN)/app

DIRS = $(LIB_SRC) $(SRC)

SOURCES := $(shell find $(DIRS) -maxdepth 1 -name '*.c')

OBJECTS := $(patsubst %.c, $(BUILD)/%.o, $(notdir $(SOURCES)))

INCLUDES = -I$(LIB_INCLUDE) -I../

vpath %.c $(DIRS)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(TARGET)
	@echo "Built target: $@"

$(BUILD)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CCFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(BUILD) $(BIN)
	@echo "Cleaned build and bin directories"
