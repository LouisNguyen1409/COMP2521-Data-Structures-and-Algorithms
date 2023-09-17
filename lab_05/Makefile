# COMP2521 - Lab 05 Makefile

# !!! DO NOT MODIFY THIS FILE !!!

CC = clang
CFLAGS = -Wall -Werror -g -fsanitize=address,leak,undefined

COMMON = Fb.o List.o Map.o Queue.o

.PHONY: all
all: runFb

runFb: runFb.o $(COMMON)
	$(CC) $(CFLAGS) -o runFb runFb.o $(COMMON)

runFb.o: runFb.c Fb.h List.h

Fb.o: Fb.c Fb.h List.h Map.h Queue.h
List.o: List.c List.h
Map.o: Map.c Map.h
Queue.o: Queue.c Queue.h

.PHONY: clean
clean:
	rm -f *.o runFb

