CC ?= clang

SRC := $(wildcard src/*.c)
OBJ := $(patsubst src/%.c, build/%.o, $(SRC))
BIN := build/xinput-transformd
SCRIPT := $(wildcard script/*)

CFLAGS ?= -g -O0 -Wall -Werror -pedantic
LDFLAGS ?= -flto -lX11

.PHONY: build clean install

build: $(BIN)

clean:
	rm -f ./build/*

install:
	cp $(BIN) $(SCRIPT) /usr/local/bin

$(BIN): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $(BIN)

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@
