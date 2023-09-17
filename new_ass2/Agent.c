// Implementation of the Agent ADT

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Agent.h"
#include "Map.h"
#define LTP 3
// This struct stores information about an individual agent and can be
// used to store information that the agent needs to remember.
struct node {
    int city;
    struct node *next;
};
struct agent {
    char *name;
    int startLocation;
    int location;
    int maxStamina; // max stamina
    int stamina;    // current stamina
    int strategy;
    Map map;
    int *visited;   // array of cities visited
    bool *visitedDFS; // array of cities visited in DFS
    int *pred;      // array of predecessors DFS
    int theftLocation;
    int initialtheftLocation;
    struct node *path;      // path to thief
    int initialStrategy;
};


static struct move chooseRandomMove(Agent agent, Map m);
static int filterRoads(Agent agent, struct road roads[], int numRoads,
                       struct road legalRoads[]);
static struct move mstMove(Agent agent, Map m);
static struct move getNextMove(struct move move, Agent agent, 
                               struct road legalRoads[], int index, 
                               int *min_visited, int *min_stamina);
static struct move dfsMove(Agent agent, Map m);
static bool visitAllCity(Agent agent, Map m);
static void resetVisited(Agent agent, Map m);
static void sort(int numRoads, struct road roads[]);
static struct move dfsTraversal(struct move move, Agent agent,
                                int numRoads, struct road roads[], 
                                bool *newCity);
static struct move goBack(struct move move, Agent agent,
                          int numLegalRoads, struct road legalRoads[]);
static struct move ltpMove(Agent agent, Map m);
static void shortestPath(Agent agent, Map m, struct road roads[]);
static bool isvSetEmpty(bool vSet[], int numCities);
static int getMin(int dist[], bool vSet[], int numCities);
static int getTurn(int prev[], Agent agent, Map m);
////////////////////////////////////////////////////////////////////////

/**
 * Creates a new agent
 */
Agent AgentNew(int start, int stamina, int strategy, Map m, char *name) {
    if (start >= MapNumCities(m)) {
        fprintf(stderr, "error: starting city (%d) is invalid\n", start);
        exit(EXIT_FAILURE);
    }
    
    Agent agent = malloc(sizeof(struct agent));
    if (agent == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    
    agent->startLocation = start;
    agent->location = start;
    agent->maxStamina = stamina;
    agent->stamina = stamina;
    agent->strategy = strategy;
    agent->map = m;
    agent->name = strdup(name);
    agent->visited = calloc(MapNumCities(m), sizeof(int));
    if (agent->visited == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    agent->visited[start] += 1;
    agent->visitedDFS = calloc(MapNumCities(m), sizeof(bool));
    if (agent->visitedDFS == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < MapNumCities(m); i++) {
        agent->visitedDFS[i] = false;
    }
    agent->pred = calloc(MapNumCities(m), sizeof(int));
    if (agent->pred == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < MapNumCities(m); i++) {
        agent->pred[i] = -1;
    }
    agent->theftLocation = -1;
    agent->initialtheftLocation = -1;
    agent->path = NULL;
    agent->initialStrategy = strategy;
    return agent;
}

/**
 * Frees all memory associated with the agent
 * NOTE: You should not free the map because the map is owned by the
 *       main program, and the main program will free it
 */
void AgentFree(Agent agent) {
    free(agent->name);
    free(agent->visited);
    free(agent->visitedDFS);
    free(agent->pred);
    struct node *curr = agent->path;
    while (curr != NULL) {
        struct node *temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(agent);
}

////////////////////////////////////////////////////////////////////////
// Gets information about the agent
// NOTE: It is expected that these functions do not need to be modified

/**
 * Gets the name of the agent
 */
char *AgentName(Agent agent) {
    return agent->name;
}

/**
 * Gets the current location of the agent
 */
int AgentLocation(Agent agent) {
    return agent->location;
}

/**
 * Gets the amount of stamina the agent currently has
 */
int AgentStamina(Agent agent) {
    return agent->stamina;
}

////////////////////////////////////////////////////////////////////////
// Making moves

/**
 * Calculates the agent's next move
 * NOTE: Does NOT actually carry out the move
 */
struct move AgentGetNextMove(Agent agent, Map m) {
    //Switch back to initial strategy
    if (agent->strategy == LTP) {
        if (agent->location == agent->theftLocation || agent->path == NULL) {
            agent->strategy = agent->initialStrategy;
            agent->theftLocation = -1;
        }
    }
    // Switch to least turn path strategy
    if (agent->theftLocation != -1) {
        agent->strategy = LTP;
    }
    switch (agent->strategy) {
        case STATIONARY:             return (struct move){agent->location, 0};
        case RANDOM:                 return chooseRandomMove(agent, m);
        case CHEAPEST_LEAST_VISITED: return mstMove(agent, m);
        case DFS:                    return dfsMove(agent, m);
        case LTP:                    return ltpMove(agent, m);
        default:
            printf("error: strategy not implemented yet\n");
            exit(EXIT_FAILURE);
    }
}

static struct move chooseRandomMove(Agent agent, Map m) {
    struct road *roads = malloc(MapNumCities(m) * sizeof(struct road));
    struct road *legalRoads = malloc(MapNumCities(m) * sizeof(struct road));

    // Get all roads to adjacent cities
    int numRoads = MapGetRoadsFrom(m, agent->location, roads);

    // Filter out roads that the agent does not have enough stamina for
    int numLegalRoads = filterRoads(agent, roads, numRoads, legalRoads);

    struct move move;
    if (numLegalRoads > 0) {
        // Sort the roads using insertion sort
        for (int i = 1; i < numLegalRoads; i++) {
            struct road r = legalRoads[i];
            int j = i;
            while (j > 0 && r.to < legalRoads[j - 1].to) {
                legalRoads[j] = legalRoads[j - 1];
                j--;
            }
            legalRoads[j] = r;
        }
        
        // nextMove is randomly chosen from the legal roads
        int k = rand() % numLegalRoads;
        move = (struct move){legalRoads[k].to, legalRoads[k].length};
    } else {
        // The agent must stay in the same location
        move = (struct move){agent->location, 0};
    }
    
    free(legalRoads);
    free(roads);
    return move;
}

// Takes an array with all the possible roads and puts the ones the agent
// has enough stamina for into the legalRoads array
// Returns the number of legal roads
static int filterRoads(Agent agent, struct road roads[], int numRoads,
                       struct road legalRoads[]) {
    int numLegalRoads = 0;
    for (int i = 0; i < numRoads; i++) {
        if (roads[i].length <= agent->stamina) {
            legalRoads[numLegalRoads++] = roads[i];
        }
    }
    return numLegalRoads;
}

/**
 * Executes a given move by updating the agent's internal state
 */
void AgentMakeNextMove(Agent agent, struct move move) {
    if (move.to == agent->location) {
        agent->stamina = agent->maxStamina;
    } else {
        agent->stamina -= move.staminaCost;
    }
    agent->location = move.to;
    agent->visited[agent->location] += 1;
}

/**
    Stage 1: CHEAPEST_LEAST_VISITED strategy
*/
static struct move mstMove(Agent agent, Map m) {
    struct road *roads = malloc(MapNumCities(m) * sizeof(struct road));
    if (roads == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    struct road *legalRoads = malloc(MapNumCities(m) * sizeof(struct road));
    if (legalRoads == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    int numRoads = MapGetRoadsFrom(m, agent->location, roads);
    int numLegalRoads = filterRoads(agent, roads, numRoads, legalRoads);
    struct move move = (struct move){agent->location, 0};
    int min_visited = 100000;
    int min_stamina = 100000;
    if (numLegalRoads > 0) {
        for (int i = 0; i < numLegalRoads; i++) {
            move = getNextMove(move, agent, legalRoads, i, &min_visited,
                                &min_stamina);
        }
    } else {
        move = (struct move){agent->location, 0};
    }
    free(legalRoads);
    free(roads);
    return move;
}

/**
    Calculate agent next move for CHEAPEST_LEAST_VISITED strategy
*/
static struct move getNextMove(struct move move, Agent agent, 
                               struct road legalRoads[], int index, 
                               int *min_visited, int *min_stamina) {
    if (agent->visited[legalRoads[index].to] < *min_visited) {
        *min_visited = agent->visited[legalRoads[index].to];
        *min_stamina = legalRoads[index].length;
        move = (struct move){legalRoads[index].to, legalRoads[index].length};
    } else if (agent->visited[legalRoads[index].to] == *min_visited) {
        if (legalRoads[index].length < *min_stamina) {
            *min_stamina = legalRoads[index].length;
            move = (struct move){legalRoads[index].to, legalRoads[index].length};
        }
    }
    return move;
}

/** 
    Stage 2: DFS strategy
*/
static struct move dfsMove(Agent agent, Map m) {
    struct road *roads = malloc(MapNumCities(m) * sizeof(struct road));
    if (roads == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    struct road *legalRoads = malloc(MapNumCities(m) * sizeof(struct road));
    if (legalRoads == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    int numRoads = MapGetRoadsFrom(m, agent->location, roads);
    int numLegalRoads = filterRoads(agent, roads, numRoads, legalRoads);
    bool newCity = false;
    resetVisited(agent, m);
    struct move move = (struct move){agent->location, 0};
    if (numLegalRoads > 0) {
        // sort by index destination city
        sort(numRoads, roads);
        move = dfsTraversal(move, agent, numRoads, roads, &newCity);
        if (agent->stamina < move.staminaCost) {
            agent->visited[move.to] = false;
            move = (struct move){agent->location, 0};
        }
        // Go backward
        if (newCity == false) {
            move = goBack(move, agent, numLegalRoads, legalRoads);
        }
    } else {
        move = (struct move){agent->location, 0};
    }
    free(legalRoads);
    free(roads);
    return move;
}

/**
    Check the visited list that all the city is visited.
*/
static bool visitAllCity(Agent agent, Map m) {
    for (int i = 0; i < MapNumCities(m); i++) {
        if (agent->visited[i] == false) {
            return false;
        }
    }
    return true;
}
/**
    Reset the visited list to non-visited
*/
static void resetVisited(Agent agent, Map m) {
    bool visitAll = visitAllCity(agent, m);
    if (visitAll == true) {
        for (int i = 0; i < MapNumCities(m); i++) {
            agent->visitedDFS[i] = false;
        }
        for (int i = 0; i < MapNumCities(m); i++) {
            agent->pred[i] = -1;
        }
    }
}

/**
    Intersertion sort the road list by the distination index
*/
static void sort(int numRoads, struct road roads[]) {
    for (int i = 1; i < numRoads; i++) {
        struct road r = roads[i];
        int j = i;
        while (j > 0 && r.to < roads[j - 1].to) {
            roads[j] = roads[j - 1];
            j--;
        }
        roads[j] = r;
    }

}

/**
    Calculate agent next move for DFS strategy
*/
static struct move dfsTraversal(struct move move, Agent agent,
                                int numRoads, struct road roads[], 
                                bool *newCity) {
    for (int i = 0; i < numRoads; i++) {
        if (agent->visited[roads[i].to] == false) {
            move = (struct move){roads[i].to, roads[i].length};
            agent->visited[roads[i].to] = true;
            agent->pred[roads[i].to] = agent->location;
            *newCity = true;
            return move;
        }
    }
    return move;
}

/**
    Go back the city that alr visited
*/
static struct move goBack(struct move move, Agent agent,
                          int numLegalRoads, struct road legalRoads[]) {
    int k = agent->pred[agent->location];
    for (int i = 0; i < numLegalRoads; i++) {
        if (legalRoads[i].to == k) {
            move = (struct move){legalRoads[i].to, legalRoads[i].length};
            return move;
        }
    }
    return move;
}

/**
    Stage 3: Least Turns Path
*/
static struct move ltpMove(Agent agent, Map m) {
    struct road *roads = malloc(MapNumCities(m) * sizeof(struct road));
    if (roads == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    struct road *legalRoads = malloc(MapNumCities(m) * sizeof(struct road));
    if (legalRoads == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    // get the shortest path to the informants  
    if (agent->path == NULL ||
        agent->initialtheftLocation != agent->theftLocation) {
        agent->initialtheftLocation = agent->theftLocation;
        shortestPath(agent, m, roads);
    }
    int numRoads = MapGetRoadsFrom(m, agent->location, roads);
    int numLegalRoads = filterRoads(agent, roads, numRoads, legalRoads);
    struct move move = (struct move){agent->location, 0};
    struct node *curr = agent->path;
    if (numLegalRoads > 0) {
        for (int i = 0; i < numLegalRoads; i++) {
            if (curr->city == legalRoads[i].to) {
                move = (struct move){legalRoads[i].to, legalRoads[i].length};
                agent->path = curr->next;
                free(curr);
                break;
            }
        }
    } else {
        move = (struct move){agent->location, 0};
    }
    free(legalRoads);
    free(roads);
    return move;
}

/**
    Get the shortest path to the informants  
*/
static void shortestPath(Agent agent, Map m, struct road roads[]) {
    int dist[MapNumCities(m)];
    int prev[MapNumCities(m)];
    bool vSet[MapNumCities(m)];
    int turns[MapNumCities(m)];
    int turnPrev[MapNumCities(m)];
    bool turnvSet[MapNumCities(m)];
    for (int i = 0; i < MapNumCities(m); i++) {
        dist[i] = 100000;
        prev[i] = -1;
        vSet[i] = false;
        turns[i] = 100000;
        turnvSet[i] = false;
        turnPrev[i] = -1;
    }

    dist[agent->location] = 0;
    while (!isvSetEmpty(vSet, MapNumCities(m))) {
        int v = getMin(dist, vSet, MapNumCities(m));
        int numRoads = MapGetRoadsFrom(m, v, roads);
        for (int i = 0; i < numRoads; i++) {
            if (vSet[roads[i].to] == false && 
                dist[v] + roads[i].length < dist[roads[i].to]) {
                dist[roads[i].to] = dist[v] + roads[i].length;
                prev[roads[i].to] = v;
            }
        }
        vSet[v] = true;
    }

    turns[agent->location] = 0;
    while (!isvSetEmpty(turnvSet, MapNumCities(m))) {
        int v = getMin(turns, turnvSet, MapNumCities(m));
        int numRoads = MapGetRoadsFrom(m, v, roads);
        for (int i = 0; i < numRoads; i++) {
            if (turnvSet[roads[i].to] == false && 
                turns[v] + 1 < turns[roads[i].to]) {
                turns[roads[i].to] = turns[v] + 1;
                turnPrev[roads[i].to] = v;
            }
        }
        turnvSet[v] = true;
    }

    int j = agent->theftLocation;
    if (getTurn(prev, agent, m) > getTurn(turnPrev, agent, m)) {
        while (turnPrev[j] != -1) {
            struct node *n_path = malloc(sizeof(struct node));
            if (n_path == NULL) {
                fprintf(stderr, "error: out of memory\n");
                exit(EXIT_FAILURE);
            }
            n_path->city = j;
            n_path->next = agent->path;
            agent->path = n_path;
            j = turnPrev[j];
        }
    } else {
        while (prev[j] != -1) {
            struct node *n_path = malloc(sizeof(struct node));
            if (n_path == NULL) {
                fprintf(stderr, "error: out of memory\n");
                exit(EXIT_FAILURE);
            }
            n_path->city = j;
            n_path->next = agent->path;
            agent->path = n_path;
            j = prev[j];
        }
    }
}

/**
    Check is all the cities are visited in vSet
*/
static bool isvSetEmpty(bool vSet[], int numCities) {
    for (int i = 0; i < numCities; i++) {
        if (vSet[i] == false) {
            return false;
        }
    }
    return true;
}

/**
    Get the minimum distance from the distance list but not yet visited
*/
static int getMin(int dist[], bool vSet[], int numCities) {
    int min = 100000;
    int min_index;
    for (int i = 0; i < numCities; i++) {
        if (vSet[i] == false && dist[i] <= min) {
            min = dist[i];
            min_index = i;
        }
    }
    return min_index;
}

/**
    Get the number of turns from the distance list
*/
static int getTurn(int prev[], Agent agent, Map m) {
    int turn = 1;
    struct node *head = NULL;
    int location = agent->theftLocation;
    while (prev[location] != -1) {
        struct node *n_path = malloc(sizeof(struct node));
        if (n_path == NULL) {
            fprintf(stderr, "error: out of memory\n");
            exit(EXIT_FAILURE);
        }
        n_path->city = location;
        n_path->next = head;
        head = n_path;
        location = prev[location];
    }
    struct node *n_path = malloc(sizeof(struct node));
    if (n_path == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    n_path->city = agent->location;
    n_path->next = head;
    head = n_path;
    struct node *curr = head;
    int stamina = agent->stamina;
    while (curr->next != NULL) {
        if (stamina < MapContainsRoad(m, curr->city, curr->next->city)) {
            stamina = agent->maxStamina;
        } else {
            stamina -= MapContainsRoad(m, curr->city, curr->next->city);
            curr = curr->next;
        }
        turn += 1;
    }
    while (head != NULL) {
        struct node *temp = head;
        head = head->next;
        free(temp);
    }
    return turn;
}
////////////////////////////////////////////////////////////////////////
// Learning information

/**
 * Tells the agent where the thief is
 */
void AgentTipOff(Agent agent, int thiefLocation) {
    agent->initialtheftLocation = agent->theftLocation;
    agent->theftLocation = thiefLocation;
}

////////////////////////////////////////////////////////////////////////
// Displaying state

/**
 * Prints information about the agent (for debugging purposes)
 */
void AgentShow(Agent agent) {
    // TODO: You can implement this function however you want
    //       You can leave this function blank if you want
    printf("Agent %s is at %d with %d stamina and %d strategy\n", agent->name,
           agent->location, agent->stamina, agent->strategy);
}

////////////////////////////////////////////////////////////////////////
