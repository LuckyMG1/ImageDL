CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRC = src/main.c src/url_parser.c src/socket_setup.c src/communication.c
OBJ = $(patsubst src/%.c, build/%.o, $(SRC))
OUT = build/imagedl
INSTALL_PATH = /usr/local/bin/imagedl

all: build $(OUT)

build:
	mkdir -p build

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(OUT)

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

install: $(OUT)
	sudo cp $(OUT) $(INSTALL_PATH)
	sudo chmod 755 $(INSTALL_PATH)

uninstall:
	sudo rm -f $(INSTALL_PATH)
clean:
	rm -rf build

