# COMP2521 - Lab 02 Makefile

# !!! DO NOT MODIFY THIS FILE !!!

CC = clang
CFLAGS = -Wall -Werror -g -fsanitize=address,leak,undefined

.PHONY: all
all: gcd rabbits listTail listMax listSum listInsertOrdered listInsertNth

gcd: gcd.c
rabbits: rabbits.c
listTail: listTail.c
listMax: listMax.c
listSum: listSum.c
listInsertOrdered: listInsertOrdered.c
listInsertNth: listInsertNth.c

.PHONY: clean
clean:
	rm -f gcd rabbits listTail listMax listSum listInsertOrdered listInsertNth

