CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude
SRC = src/main.c src/url_parser.c src/socket_setup.c src/communication.c
OBJ = $(patsubst src/%.c, build/%.o, $(SRC))
OUT = build/program

all: build $(OUT)

build:
	mkdir -p build

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(OUT)

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build

