// game.c - the client program.
// This reads in data from a file to create a map of cities and roads,
// then reads in data to create 5 agents: 4 detectives and a thief.
// It then runs a simulation where the thief and detectives move
// through the cities.

// !!! DO NOT MODIFY THIS FILE !!!

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Agent.h"
#include "Map.h"

// DO NOT RELY ON THESE VALUES.
// These values are intended to be used by game.c ONLY. They may be
// changed during autotesting.
#define MAX_LINE 100
#define MAX_CITY_NAME 30
#define MAX_AGENT_NAME 30

#define NUM_DETECTIVES 4
#define THIEF 0
#define D1 1
#define D2 2
#define D3 3
#define D4 4

// Game status
#define CONTINUE  0
#define WIN      -1
#define LOSE     -2
#define OVER     -3

typedef struct state {
    Map map;
    bool *informants;
    Agent agents[NUM_DETECTIVES + 1];
    int getaway;
    int cycle;
    int maxCycles;
    int status;
} State;

static void readMap(char *filename, State *s);
static void readAgents(char *filename, State *s);
static void displayGameState(State *s);
static int  checkGameState(State *s);
static bool checkWin(State *s);
static bool checkLose(State *s);
static void run(State *s);
static void step(State *s);
static void displayStats(State *s);
static void freeResources(State *s);

int main(int argc, char *argv[]) {
    if (argc < 4 || argc > 5) {
        printf("usage: %s <city data file> <agent data file> <cycles> [seed]\n",
               argv[0]);
        exit(EXIT_FAILURE);
    }

    State s;
    s.cycle = 0;
    s.maxCycles = atoi(argv[3]);
    s.status = CONTINUE;

    int seed = time(NULL);
    if (argc == 5) {
        seed = atoi(argv[4]);
    }
    srand(seed);

    readMap(argv[1], &s);
    readAgents(argv[2], &s);

    printf("\nDETECTIVE ACADEMY 2521");
    printf("\n\nRed alert! A thief is on the run.\n");
    printf("Detectives, to your cars. You have %d hours.\n\n", s.maxCycles);
    displayGameState(&s);

    if (checkGameState(&s) != CONTINUE) {
        freeResources(&s);
        return 0;
    }

    char command[MAX_LINE + 2];
    printf("Enter command: ");
    scanf("%10s", command);

    while (strcmp(command, "quit") != 0) {
        if (strcmp(command, "display") == 0) {
             displayGameState(&s);
        } else if (strcmp(command, "run") == 0) {
             run(&s);
        } else if (strcmp(command, "step") == 0) {
             step(&s);
        } else if (strcmp(command, "stats") == 0) {
             displayStats(&s);
        } else if (strcmp(command, "map") == 0) {
             MapShow(s.map);
             printf("\n");
        }

        if (s.status != CONTINUE) break;
        printf("Enter command: ");
        scanf("%10s", command);
    }

    freeResources(&s);
}

/**
 * Reads in city data from the file with the given filename
 */
static void readMap(char *filename, State *s) {
    FILE *fp;
    fp = fopen (filename, "r"); // open data file
    if (fp == NULL) {
        fprintf(stderr, "error: failed to open '%s'\n", filename);
        exit(EXIT_FAILURE);
    }

    // First line of file has the number of vertices
    int numCities;
    fscanf(fp, "%d", &numCities);

    s->map = MapNew(numCities);
    s->informants = calloc(numCities, sizeof(bool));
    if (s->informants == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    // scan through file and insert roads into map
    int city = 0;
    int dest = 0;
    int dist = 0;
    char informant;
    char name[MAX_CITY_NAME + 1];

    for (int i = 0; i < numCities; i++) {    
        fscanf(fp, "%d", &city);

        while (fscanf(fp, "%d %d", &dest, &dist) == 2) {
            MapInsertRoad(s->map, city, dest, dist);
        }

        fscanf(fp, " %c %30[^\n]", &informant, name);
        MapSetName(s->map, i, name);
        if (informant == 'i') {
            s->informants[i] = true;
        }
    }

    fclose(fp);
}

// Initialises the thief and 4 detectives from a data file
static void readAgents(char *filename, State *s) {
    FILE *fp;
    fp = fopen(filename, "r"); // open data file
    if (fp == NULL) {
        fprintf(stderr, "error: failed to open '%s'\n", filename);
        exit(EXIT_FAILURE);
    }

    int stamina;
    int start;
    int strategy;
    char name[MAX_AGENT_NAME + 1];

    fscanf(fp, "%d %d %d %30[^\n]", &stamina, &start, &s->getaway, name);
    s->agents[THIEF] = AgentNew(start, stamina, RANDOM, s->map, name);

    for (int i = 1; i <= NUM_DETECTIVES; i++) {
        fscanf(fp, "%d %d %d %30[^\n]", &stamina, &start, &strategy, name);
        s->agents[i] = AgentNew(start, stamina, strategy, s->map, name);
        if (s->informants[start]) {
            AgentTipOff(s->agents[i], AgentLocation(s->agents[THIEF]));
        }
    }

    fclose(fp);
}

// Display information about the current state of the game
static void displayGameState(State *s) {
    printf("Hour %d\n", s->cycle);
    
    // Print the current location of each agent
    printf("  T  D1  D2  D3  D4\n");
    for (int i = 0; i <= NUM_DETECTIVES; i++) {
        printf("%3d%c", AgentLocation(s->agents[i]),
               s->informants[AgentLocation(s->agents[i])] ? '*' : ' ');
    }
    printf("\n\n");
}

static int checkGameState(State *s) {
    if (checkWin(s)) {
        printf("YOU WIN - THIEF CAUGHT!\n");
        return WIN;
    } else if (checkLose(s)) {
        printf("GAME OVER: YOU LOSE - THIEF GOT TO GETAWAY\n");
        return LOSE;
    } else if (s->cycle >= s->maxCycles) {
        printf("GAME OVER: YOU LOSE - TIME IS UP\n");
        return OVER;
    } else {
        return CONTINUE;
    }
}

static bool checkWin(State *s) {
    int thiefLocation = AgentLocation(s->agents[THIEF]);
    for (int i = 1; i <= NUM_DETECTIVES; i++) {
        int detectiveLocation = AgentLocation(s->agents[i]);
        if (detectiveLocation == thiefLocation) {
            printf("%s caught the thief in %s (%d)\n",
                   AgentName(s->agents[i]),
                   MapGetName(s->map, detectiveLocation), detectiveLocation);
            return true;
        }
    }
    return false;
}

static bool checkLose(State *s) {
    int thiefLocation = AgentLocation(s->agents[THIEF]);
    
    if (thiefLocation == s->getaway) {
        printf("%s got away to %s (%d)\n", AgentName(s->agents[THIEF]),
               MapGetName(s->map, thiefLocation), thiefLocation);
        return true;
    }
    return false;
}

// runs the game until the maximum number of cycles have completed
static void run(State *s) {
    while (s->cycle < s->maxCycles && s->status == CONTINUE) {
        step(s);
    }
}

// step through one cycle of the game
static void step(State *s) {
    s->cycle++;
    for (int i = 0; i <= NUM_DETECTIVES; i++) {
        struct move nextMove = AgentGetNextMove(s->agents[i], s->map);
        AgentMakeNextMove(s->agents[i], nextMove);
        if (i > 0 && s->informants[nextMove.to]) {
            AgentTipOff(s->agents[i], AgentLocation(s->agents[THIEF]));
        }
    }

    displayGameState(s);
    s->status = checkGameState(s);
}

static void displayStats(State *s) {
    printf("Hour %d\n", s->cycle);
    for (int i = 0; i <= NUM_DETECTIVES; i++) {
        int loc = AgentLocation(s->agents[i]);
        printf("%s is at [%d] %s with %d stamina\n",
               AgentName(s->agents[i]),
               loc, MapGetName(s->map, loc), 
               AgentStamina(s->agents[i]));
    }
    printf("\n");
}

static void freeResources(State *s) {
    for (int i = 0; i <= NUM_DETECTIVES; i++) {
        AgentFree(s->agents[i]);
    }
    free(s->informants);
    MapFree(s->map);
}

