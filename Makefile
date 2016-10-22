CC = gcc
CFLAGS = -std=c99 -ggdb -Wall -Wextra

all: interpreter
	$(CC) $(CFLAGS) -o interpreter interpreter.c
