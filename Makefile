# Snake Game Makefile for x64

CC := gcc
NASM := nasm
CFLAGS := -Wall -Wextra -O2 -fPIC -m64 -Iinclude
NASMFLAGS := -f elf64
LDFLAGS := -m64

SOURCES := src/main.c src/game.c src/graphics.c src/input.c
ASM_SOURCES := src/collision.asm
OBJECTS := $(SOURCES:.c=.o) $(ASM_SOURCES:.asm=.o)
TARGET := bin/snake

.PHONY: all build clean run debug

all: build

build: $(TARGET)

$(TARGET): $(OBJECTS) | bin
	$(CC) $(LDFLAGS) -o $@ $^

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/%.o: src/%.asm
	$(NASM) $(NASMFLAGS) -o $@ $<

bin:
	mkdir -p bin

run: build
	./$(TARGET)

debug: CFLAGS += -g -DDEBUG
debug: build
	gdb ./$(TARGET)

clean:
	rm -f src/*.o
	rm -rf bin

.PHONY: help
help:
	@echo "Snake Game Makefile"
	@echo "Targets:"
	@echo "  make build  - Build the game"
	@echo "  make run    - Build and run the game"
	@echo "  make debug  - Build with debugging symbols and run with gdb"
	@echo "  make clean  - Clean build artifacts"
