# COMP2521 - Lab 01 Makefile

# !!! DO NOT MODIFY THIS FILE !!!

CC = clang
CFLAGS = -Wall -Werror -g -fsanitize=address,leak,undefined

.PHONY: all
all: testIntList sortIntList

testIntList: testIntList.o IntList.o
	$(CC) $(CFLAGS) -o testIntList testIntList.o IntList.o

sortIntList: sortIntList.o IntList.o
	$(CC) $(CFLAGS) -o sortIntList sortIntList.o IntList.o

testIntList.o: testIntList.c IntList.h
sortIntList.o: sortIntList.c IntList.h
IntList.o: IntList.c IntList.h

.PHONY: clean
clean:
	rm -f testIntList sortIntList *.o

