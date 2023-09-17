// Main program for testing the Map ADT

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Map.h"

void testSetName(void);
void testInsertRoad(void);
void testGetRoadsFrom(void);
void generateMatrix(Map m, int **arr);
void testMap();

int main(int argc, char *argv[]) {
	testSetName();
	testInsertRoad();
	testGetRoadsFrom();
	testMap();
}

void testSetName(void) {
	Map m = MapNew(5);

	char name1[] = "sydney";
	assert(strcmp(MapGetName(m, 0), "unnamed") == 0);
	MapSetName(m, 0, name1);

	// Overwriting the name1 string with something random
	strcpy(name1, "???");
	assert(strcmp(MapGetName(m, 0), "sydney") == 0);

	char name2[] = "canberra";
	assert(strcmp(MapGetName(m, 4), "unnamed") == 0);
	MapSetName(m, 4, name2);

	// Overwriting the name2 string with something random
	strcpy(name2, "???");
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
	printf("Pass testInsertRoad\n");
}

void generateMatrix(Map m, int **arr) {
	int numCities = MapNumCities(m);
	int **Matrix = calloc(numCities * numCities, sizeof(int*));
	for (int i = 0; i < numCities; i++) Matrix[i] = calloc(numCities, sizeof(int));

	for (int i = 0; i < numCities; i++) {
		for (int j = 0; j < numCities; j++) {
			Matrix[i][j] = 0;
		}
	}
	for (int i = 0; i < numCities; i++) {
		struct road *roads = calloc(numCities, sizeof(struct road));
		int numRoads = MapGetRoadsFrom(m, i, roads);
		for (int k = 0; k < numRoads; k++) {
			Matrix[roads[k].from][roads[k].to] = roads[k].length;
			Matrix[roads[k].to][roads[k].from] = roads[k].length;
		}
		free(roads);
	}

	// printf("created graph has Matrix:\n");
	// for (int i = 0; i < numCities; i++) {
	// 	for (int j = 0; j < numCities; j++) {
	// 		printf("%d ", Matrix[i][j]);
	// 	}
	// 	printf("\n");
	// }

	printf("now check that they are equal\n");
	for (int i = 0; i < numCities; i++) {
		for (int j = 0; j < numCities; j++) {
			int num1 = Matrix[i][j];
			int num2 = arr[i][j];
			assert(num1 == num2);
		}
	}
	for (int i = 0 ; i < numCities; i++) free(Matrix[i]);
	free(Matrix);
	printf("assert passed\n");
}

void testMap() {
	srand(time(NULL));

	int mapSize = rand() % 20;
	Map m = MapNew(mapSize);
	int **adjMatrix = calloc(mapSize, sizeof(int*));
	for (int i = 0; i < mapSize; i++) adjMatrix[i] = calloc(mapSize, sizeof(int));

	for (int i = 0; i < mapSize; i++) {
		for (int j = i + 1; j < mapSize; j++) {
			int hasRoad = rand() % 2;
			if (hasRoad) {
				int length = rand() % 100;
				MapInsertRoad(m, i, j, length);
				adjMatrix[i][j] = length;
				adjMatrix[j][i] = length;
			} else adjMatrix[i][j] = 0;
		}
	}

	generateMatrix(m, adjMatrix);

	// printf("expected matrix:\n");
	// for (int i = 0; i < mapSize; i++) {
	// 	for (int j = 0; j < mapSize; j++) {
	// 		printf("%d ", adjMatrix[i][j]);
	// 	}
	// 	printf("\n");
	// }

	for (int i = 0 ; i < mapSize; i++) free(adjMatrix[i]);
	free(adjMatrix);
	printf("\n\n");
}