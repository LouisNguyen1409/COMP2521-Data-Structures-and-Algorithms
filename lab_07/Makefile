# COMP2521 Lab 8 Makefile

CC = clang
CFLAGS = -Wall -Werror -g -fsanitize=address,leak,undefined

OBJS1 = testGraphMst.o Graph.o Pq.o
OBJS2 = gridPlanner.o Graph.o planner.o Pq.o

.PHONY: all
all: testGraphMst gridPlanner

testGraphMst: $(OBJS1)
	$(CC) $(CFLAGS) -o testGraphMst $(OBJS1)

gridPlanner: $(OBJS2)
	$(CC) $(CFLAGS) -o gridPlanner $(OBJS2) -lm

testGraphMst.o: testGraphMst.c Graph.h
gridPlanner.o: gridPlanner.c place.h planner.h

Graph.o: Graph.c Graph.h Pq.h
planner.o: planner.c planner.h Graph.h place.h Pq.h
Pq.o: Pq.c Pq.h Graph.h

.PHONY: clean
clean:
	rm -f testGraphMst gridPlanner $(OBJS1) $(OBJS2)

