// Algorithms to design electrical grids

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "place.h"
#include "Pq.h"

////////////////////////////////////////////////////////////////////////
// Your task
static bool isvSetEmpty (bool vSet[], int numCities);
static double distance(int x1, int y1, int x2, int y2);
static int findMinDistIndex(int dist[], bool vSet[], int numCities);
/**
 * Designs  a minimal cost electrical grid that will deliver electricity
 * from a power plant to all the given cities. Power lines must be built
 * between cities or between a city and a power plant.  Cost is directly
 * proportional to the total length of power lines used.
 * Assumes  that  numCities  is at least 1 (numCities is the size of the
 * cities array).
 * Stores the power lines that need to be built in the given  powerLines
 * array, and returns the number of power lines stored. Assumes that the
 * powerLines array is large enough to store all required power lines.
 */
int planGrid1(struct place cities[], int numCities,
              struct place powerPlant,
              struct powerLine powerLines[]) {
    numCities++;
    int dist[numCities];
    int prev[numCities];
    bool vSet[numCities];
    for (int i = 0; i < numCities; i++) {
        dist[i] = 1000000;
        prev[i] = -1;
        vSet[i] = false;
    }

    dist[0] = 0;
    int npl = 0;
    while (!isvSetEmpty(vSet, numCities)) {
        int vertex = findMinDistIndex(dist, vSet, numCities);
        struct place city;
        if (vertex == 0) {
            city = powerPlant;
        } else {
            city = cities[vertex - 1];
        }
        for (int i = 0; i < numCities; i++) {
            struct place n_city;
            if (i == 0) {
                n_city = powerPlant;
            } else {
                n_city = cities[i - 1];
            }
            if (!(city.x == n_city.x && city.y == n_city.y) && !vSet[i]) {
                int length = distance(city.x, city.y, n_city.x, n_city.y);
                if (dist[i] > length) {
                    dist[i] = length;
                    prev[i] = vertex;
                }
            }
        };
        vSet[vertex] = true;
    }

    for (int i = 0; i < numCities; i++) {
        if (prev[i] != -1) {
            struct place city = cities[i - 1];
            struct place n_city;
            if (prev[i] == 0) {
                n_city = powerPlant;
            } else {
                n_city = cities[prev[i] - 1];
            }
            powerLines[npl].p2 = city;
            powerLines[npl].p1 = n_city;
            npl++;
        }

    }
    return npl;
}
static bool isvSetEmpty (bool vSet[], int numCities) {
    for (int i = 0; i < numCities; i++) {
        if (vSet[i] == false) {
            return false;
        }
    }
    return true;
}
static double distance(int x1, int y1, int x2, int y2) {
    return sqrt(pow((double)(x1 - x2),2) + pow((double)(y1 - y2),2));
}
static int findMinDistIndex(int dist[], bool vSet[], int numCities) {
    int min = 1000000;
    int minIndex = -1;
    for (int i = 0; i < numCities; i++) {
        if (vSet[i] == false && dist[i] <= min) {
            min = dist[i];
            minIndex = i;
        }
    }
    return minIndex;
}

////////////////////////////////////////////////////////////////////////
// Optional task

/**
 * Designs  a minimal cost electrical grid that will deliver electricity
 * to all the given cities.  Power lines must be built between cities or
 * between a city and a power plant.  Cost is directly  proportional  to
 * the  total  length of power lines used.  Assume that each power plant
 * generates enough electricity to supply all cities, so not  all  power
 * plants need to be used.
 * Assumes  that  numCities and numPowerPlants are at least 1 (numCities
 * and numPowerPlants are the sizes of the cities and powerPlants arrays
 * respectively).
 * Stores the power lines that need to be built in the given  powerLines
 * array, and returns the number of power lines stored. Assumes that the
 * powerLines array is large enough to store all required power lines.
 */
int planGrid2(struct place cities[], int numCities,
              struct place powerPlants[], int numPowerPlants,
              struct powerLine powerLines[]) {
    // TODO: Complete this function
    return 0;
}
