# COMP2521 Lab 7 Makefile

# !!! DO NOT MODIFY THIS FILE !!!

CC = clang
CFLAGS = -Wall -Werror -g -fsanitize=address,leak,undefined

.PHONY: all
all: solveBfs solveDfs solveDfsBacktrack solveKeepLeft

solveBfs: solver.c solveBfs.c Maze.o Queue.o matrix.o
	$(CC) $(CFLAGS) solver.c solveBfs.c Maze.o Queue.o matrix.o -o solveBfs

solveDfs: solver.c solveDfs.c Maze.o Stack.o matrix.o
	$(CC) $(CFLAGS) solver.c solveDfs.c Maze.o Stack.o matrix.o -o solveDfs

solveDfsBacktrack: solver.c solveDfsBacktrack.c Maze.o matrix.o
	$(CC) $(CFLAGS) solver.c solveDfsBacktrack.c Maze.o matrix.o -o solveDfsBacktrack

solveKeepLeft: solver.c solveKeepLeft.c Maze.o matrix.o
	$(CC) $(CFLAGS) solver.c solveKeepLeft.c Maze.o matrix.o -o solveKeepLeft

.PHONY: clean
clean:
	rm -f solveBfs solveDfs solveDfsBacktrack solveKeepLeft
