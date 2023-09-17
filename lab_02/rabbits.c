
#include <stdio.h>
#include <stdlib.h>

long long rabbits(int month);

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s <month>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	int months = 0;
	char c;
	if (sscanf(argv[1], "%d %c", &months, &c) != 1 || months < 0) {
		fprintf(stderr, "error: invalid number of months\n");
		exit(EXIT_FAILURE);
	}

	long long numRabbits = rabbits(months);
	printf("Number of rabbits after %d month(s): %lld\n",
	       months, numRabbits);

	return 0;
}

// !!! DO NOT MODIFY THE CODE ABOVE !!!
////////////////////////////////////////////////////////////////////////
// Your task

// Returns the number of rabbits after the given number of months
long long rabbits(int months) {
	// TODO
	if (months == 0) {
		return 2;
	} else if (months == 1) {
		return 2;
	}
	return rabbits(months - 1) + rabbits(months - 2);
}

