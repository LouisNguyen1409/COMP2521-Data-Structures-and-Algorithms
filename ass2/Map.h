// Interface to the Map ADT
// Cities are identified by integers between 0 and N - 1 where N is the
// number of cities. All roads are bidirectional.
// Cities can be given names via the MapSetName function.

// !!! DO NOT MODIFY THIS FILE !!!

#ifndef MAP_H
#define MAP_H

struct road {
    int from;
    int to;
    int length;
};

typedef struct map *Map;

/**
 * Creates a new map with the given number of cities
 * Assumes that `numCities` is positive
 */
Map MapNew(int numCities);

/**
 * Frees all memory allocated to the given map
 */
void MapFree(Map m);

/**
 * Returns the number of cities on the given map
 */
int MapNumCities(Map m);

/**
 * Returns the number of roads on the given map
 */
int MapNumRoads(Map m);

/**
 * Sets the name of the given city
 * If the city's name has already been set, renames it
 */
void MapSetName(Map m, int city, char *name);

/**
 * Returns the name of the given city, or "unnamed" if the city's name
 * has not been set
 */
char *MapGetName(Map m, int city);

/**
 * Inserts a road between two cities with the given length
 * Does nothing if there is already a road between the two cities
 * Assumes that the cities are valid and are not the same
 * Assumes that the length of the road is positive
 */
void MapInsertRoad(Map m, int city1, int city2, int length);

/**
 * Returns the length of the road between two cities, or 0 if no such
 * road exists
 */
int MapContainsRoad(Map m, int city1, int city2);

/**
 * Stores the roads connected to the given city in the given `roads`
 * array in any order and returns the number of roads stored. The `from`
 * field should be equal to `city` for all roads in the array.
 * Assumes that the roads array is at least as large as the number of
 * cities on the map.
 */
int MapGetRoadsFrom(Map m, int city, struct road roads[]);

/**
 * Displays the map
 */
void MapShow(Map m);

#endif

