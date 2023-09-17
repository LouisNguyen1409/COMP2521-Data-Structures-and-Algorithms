// Main program for testing the Map ADT

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Map.h"

void testSetName(void);
void testInsertRoad(void);
void testGetRoadsFrom(void);

int main(int argc, char *argv[]) {
	testSetName();
	testInsertRoad();
	testGetRoadsFrom();
}

void testSetName(void) {
	Map m = MapNew(5);

	assert(strcmp(MapGetName(m, 0), "unnamed") == 0);
	MapSetName(m, 0, "sydney");
	assert(strcmp(MapGetName(m, 0), "sydney") == 0);

	assert(strcmp(MapGetName(m, 4), "unnamed") == 0);
	MapSetName(m, 4, "canberra");
	assert(strcmp(MapGetName(m, 4), "canberra") == 0);

	MapFree(m);
	printf("Pass testSetName\n");
}

void testInsertRoad(void) {
	Map m = MapNew(5);

	assert(MapNumCities(m) == 5);

	MapInsertRoad(m, 0, 1, 10);
	MapInsertRoad(m, 0, 2, 14);
	MapInsertRoad(m, 1, 3, 13);

	assert(MapNumRoads(m) == 3);

	assert(MapContainsRoad(m, 0, 1) == 10);
	assert(MapContainsRoad(m, 0, 2) == 14);
	assert(MapContainsRoad(m, 0, 3) == 0);

	MapFree(m);
	printf("Pass testInsertRoad\n");
}

void testGetRoadsFrom(void) {
	Map m = MapNew(5);

	MapInsertRoad(m, 0, 1, 10);
	MapInsertRoad(m, 0, 2, 14);
	MapInsertRoad(m, 1, 3, 13);

	struct road roads[5];
	int numRoads = MapGetRoadsFrom(m, 0, roads);
	assert(numRoads == 2);

	// Only two roads so a simple swap will sort them
	if (roads[0].to > roads[1].to) {
		struct road temp = roads[0];
		roads[0] = roads[1];
		roads[1] = temp;
	}

	assert(roads[0].from == 0 && roads[0].to == 1 && roads[0].length == 10);
	assert(roads[1].from == 0 && roads[1].to == 2 && roads[1].length == 14);

	MapFree(m);
	printf("Pass testGetRoadsFrom\n");
}

