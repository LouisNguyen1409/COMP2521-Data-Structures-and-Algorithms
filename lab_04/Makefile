# COMP2521 - Lab 04 Makefile

# !!! DO NOT MODIFY THIS FILE !!!

CC = clang
CFLAGS = -Wall -Werror -g -fsanitize=address,leak,undefined

.PHONY: all
all: runBst testBst

runBst: runBst.o bst.o Queue.o
	$(CC) $(CFLAGS) -o runBst runBst.o bst.o Queue.o

testBst: testBst.o bst.o Queue.o
	$(CC) $(CFLAGS) -o testBst testBst.o bst.o Queue.o

runBst.o: runBst.c bst.h
testBst.o: testBst.c bst.h

bst.o: bst.c bst.h Queue.h
Queue.o: Queue.c Queue.h

.PHONY: clean
clean:
	rm -f *.o runBst testBst

