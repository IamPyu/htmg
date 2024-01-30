CC:=gcc
CFLAGS+=-Wall -fPIC -shared
CFLAGS+=-lSDL2 -lSDL2_image -lSDL2_mixer

SRC:=$(shell find src -name "*.c")

CBIN:=bin/libhtmg.so

all: build test

build:
	@mkdir -p bin
	@$(CC) $(CFLAGS) $(SRC) -o $(CBIN)

test: build
	@$(CC) -Lbin -lhtmg tests/test.c -o tests/test
	@LD_LIBRARY_PATH=bin ./tests/test
