# Makefile
# COMP2521 23T2 Assignment 2
#
# HOW TO USE
# Read all the comments below and edit the Makefile accordingly

CC = clang

CFLAGS0 = -Wall -Werror -g
CFLAGS1 = -Wall -Werror -g -fsanitize=address,leak,undefined
CFLAGS2 = -Wall -Werror -g -fsanitize=memory,undefined -fsanitize-memory-track-origins

# If you want to use GDB or valgrind, change this to $(CFLAGS0)
# If you want to use the MemorySanitizer, change this to $(CFLAGS2)
# - MemorySanitizer detects uninitialized memory accesses
# You should change back to $(CFLAGS1) when you are done
# Whenever you change this, use `make -B` to force recompilation
CFLAGS = $(CFLAGS1)

# List all your supporting .c files here. Do NOT include .h files in this list.
# Example: SUPPORTING_FILES = hello.c world.c
SUPPORTING_FILES = 

.PHONY: all
all: testMap game

testMap: testMap.c Map.c
	$(CC) $(CFLAGS) -o testMap testMap.c Map.c

game: game.c Agent.c Map.c $(SUPPORTING_FILES)
	$(CC) $(CFLAGS) -o game game.c Agent.c Map.c $(SUPPORTING_FILES)

.PHONY: clean
clean:
	rm -f *.o testMap game

