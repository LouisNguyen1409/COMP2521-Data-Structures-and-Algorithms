# Makefile
# COMP2521 23T2 Assignment 1

# DO NOT modify this file except where described below

CC = clang

CFLAGS0 = -Wall -Werror -g
CFLAGS1 = -Wall -Werror -g -fsanitize=address,leak,undefined
CFLAGS2 = -Wall -Werror -g -fsanitize=memory,undefined -fsanitize-memory-track-origins

# If you want to use valgrind, change this to $(CFLAGS0)
# If you want to use the MemorySanitizer, change this to $(CFLAGS2)
# - MemorySanitizer detects uninitialized memory accesses
# You should change back to $(CFLAGS1) when you are done
CFLAGS = $(CFLAGS1)

.PHONY: all
all: testMset

testMset: testMset.c Mset.c Mset.h MsetStructs.h
	$(CC) $(CFLAGS) -o testMset testMset.c Mset.c

.PHONY: clean
clean:
	rm -f testMset

