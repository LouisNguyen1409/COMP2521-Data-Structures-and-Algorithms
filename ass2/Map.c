// Implementation of the Map ADT

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Map.h"

struct map { 
    int nV; // number of cities
    int nE; // number of road
    int **roads; // adjacency matrix
    char **names; // names of cities
};

/**
 * Creates a new map with the given number of cities
 * Assumes that `numCities` is positive
 */
Map MapNew(int numCities) {
    Map m = malloc(sizeof(struct map));
    if (m == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    m->nV = numCities;
    m->nE = 0;

    m->roads = malloc(numCities * sizeof(int *));
    if (m->roads == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    m->names = malloc(numCities * sizeof(char *));
    if (m->names == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < numCities; i++) {
        m->roads[i] = calloc(numCities, sizeof(int));
        if (m->roads[i] == NULL) {
            fprintf(stderr, "error: out of memory\n");
            exit(EXIT_FAILURE);
        }
        m->names[i] = "unnamed";
    }
    return m;
}

/**
 * Frees all memory allocated to the given map
 */
void MapFree(Map m) {
    for (int i = 0; i < m->nV; i++) {
        free(m->roads[i]);
    }
    free(m->names);
    free(m->roads);
    free(m);
}

/**
 * Returns the number of cities on the given map
 */
int MapNumCities(Map m) {
    return m->nV;
}

/**
 * Returns the number of roads on the given map
 */
int MapNumRoads(Map m) {
    return m->nE;
}

/**
 * Sets the name of the given city
 * If the city's name has already been set, renames it
 */
void MapSetName(Map m, int city, char *name) {
    m->names[city] = name;
}

/**
 * Returns the name of the given city, or "unnamed" if the city's name
 * has not been set
 */
char *MapGetName(Map m, int city) {
    if (strcmp(m->names[city], "unnamed") != 0) {
        return m->names[city];
    }
    return m->names[city];
}

/**
 * Inserts a road between two cities with the given length
 * Does nothing if there is already a road between the two cities
 * Assumes that the cities are valid and are not the same
 * Assumes that the length of the road is positive
 */
void MapInsertRoad(Map m, int city1, int city2, int length) {
    if (m->roads[city1][city2] == 0) {
        m->roads[city1][city2] = length;
        m->roads[city2][city1] = length;
        m->nE++;
    }
}

/**
 * Returns the length of the road between two cities, or 0 if no such
 * road exists
 */
int MapContainsRoad(Map m, int city1, int city2) {
    return m->roads[city1][city2];
}

/**
 * Stores the roads connected to the given city in the given `roads`
 * array in any order and returns the number of roads stored. The `from`
 * field should be equal to `city` for all roads in the array.
 * Assumes that the roads array is at least as large as the number of
 * cities on the map.
 */
int MapGetRoadsFrom(Map m, int city, struct road roads[]) {
    int numRoads = 0;
    for (int i = 0; i < m->nV; i++) {
        if (city != i && m->roads[city][i] != 0) {
            struct road r;
            r.from = city;
            r.to = i;
            r.length = m->roads[city][i];
            roads[numRoads] = r;
            numRoads++;
        }
    }
    return numRoads;
}

/**
 * Displays the map
 * !!! DO NOT EDIT THIS FUNCTION !!!
 * This function will work once the other functions are working
 */
void MapShow(Map m) {
    printf("Number of cities: %d\n", MapNumCities(m));
    printf("Number of roads: %d\n", MapNumRoads(m));
    
    struct road *roads = malloc(MapNumRoads(m) * sizeof(struct road));
    if (roads == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);    
    }
    
    for (int i = 0; i < MapNumCities(m); i++) {
        printf("[%d] %s has roads to:", i, MapGetName(m, i));
        int numRoads = MapGetRoadsFrom(m, i, roads);
        for (int j = 0; j < numRoads; j++) {
            if (j > 0) {
                printf(",");
            }
            printf(" [%d] %s (%d)", roads[j].to, MapGetName(m, roads[j].to),
                   roads[j].length);
        }
        printf("\n");
    }
    
    free(roads);
}

