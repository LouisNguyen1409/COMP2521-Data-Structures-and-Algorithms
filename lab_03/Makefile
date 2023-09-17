# COMP2521 - Lab 03 Makefile

# !!! DO NOT MODIFY THIS FILE !!!

CC = clang
CFLAGS = -Wall -Werror -g -fsanitize=address,leak,undefined

.PHONY: all
all: sortIntList runList

sortIntList: sortIntList.o IntList.o
	$(CC) $(CFLAGS) -o sortIntList sortIntList.o IntList.o

sortIntList.o: sortIntList.c IntList.h
IntList.o: IntList.c IntList.h

runList: runList.o List.o
	$(CC) $(CFLAGS) -o runList runList.o List.o

runList.o: runList.c List.h
List.o: List.c List.h

.PHONY: clean
clean:
	rm -rf sortIntList runList *.o

