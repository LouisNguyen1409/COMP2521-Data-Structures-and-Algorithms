// Interface to the Agent ADT

// !!! DO NOT MODIFY THIS FILE !!!

#ifndef AGENT_H
#define AGENT_H

#include "Map.h"

// Constants to represent search strategies used by the agents
#define STATIONARY             -1 // Useful for debugging
#define RANDOM                  0
#define CHEAPEST_LEAST_VISITED  1
#define DFS                     2

typedef struct agent *Agent;

struct move {
    int to;
    int staminaCost;
};

////////////////////////////////////////////////////////////////////////

/**
 * Creates a new agent
 */
Agent AgentNew(int start, int stamina, int strategy, Map m, char *name);

/**
 * Frees all memory associated with the agent
 */
void AgentFree(Agent agent);

////////////////////////////////////////////////////////////////////////
// Gets information about the agent

/**
 * Gets the name of the agent
 */
char *AgentName(Agent agent);

/**
 * Gets the current location of the agent
 */
int AgentLocation(Agent agent);

/**
 * Gets the amount of stamina the agent currently has
 */
int AgentStamina(Agent agent);

////////////////////////////////////////////////////////////////////////
// Making moves

/**
 * Calculates the agent's next move
 * NOTE: Does NOT actually carry out the move
 */
struct move AgentGetNextMove(Agent agent, Map m);

/**
 * Executes a given move
 */
void AgentMakeNextMove(Agent agent, struct move move);

////////////////////////////////////////////////////////////////////////
// Learning information

/**
 * Tells the agent where the thief is
 */
void AgentTipOff(Agent agent, int thiefLocation);

////////////////////////////////////////////////////////////////////////
// Displaying state

/**
 * Prints information about the agent (for debugging purposes)
 */
void AgentShow(Agent agent);

////////////////////////////////////////////////////////////////////////

#endif

