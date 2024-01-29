CC:=gcc

CFLAGS+=-Wall -fPIC -shared
CFLAGS+=-lSDL2

SRC:=$(shell find src -name "*.c")

CBIN:=bin/libhtmg.so
ARBIN:=bin/libhtmg.a

.phony: build
all: build test

build:
	@mkdir -p bin
	@$(CC) $(CFLAGS) $(SRC) -o $(CBIN)

test: build
	@$(CC) -Lbin -lhtmg tests/test.c -o tests/test
	@./tests/test
