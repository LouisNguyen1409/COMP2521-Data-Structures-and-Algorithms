// sortIntList.c - a program for testing IntListSortedCopy

// !!! DO NOT MODIFY THIS FILE !!!

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "IntList.h"

static void processArgs(int argc, char *argv[], bool *verbose);
static void usage(char *progName);

static FILE *out;

int main(int argc, char *argv[]) {
	// process options
	bool verbose = false;
	processArgs(argc, argv, &verbose);

	// read in the list
	IntList list = IntListRead(stdin);
	if (verbose) {
		fprintf(out, "Original:\n");
		IntListPrint(list, out);
	}

	// make a sorted copy of the list
	IntList sortedList = IntListSortedCopy(list);
	IntListFree(list);

	if (verbose) fprintf(out, "Sorted:\n");
	IntListPrint(sortedList, out);

	// make sure the list is consistent/sorted
	bool ok = IntListOK(sortedList);
	IntListFree(sortedList);

	if (!ok) {
		fprintf(out,
		        "\n"
		        "#####  ####   ####   #####  ####\n"
		        "#      #   #  #   #  #   #  #   #\n"
		        "####   ####   ####   #   #  ####\n"
		        "#      #  #   #  #   #   #  #  #\n"
		        "#####  #   #  #   #  #####  #   #\n"
		        "\n"
		        "error: IntListOK returned false, which means the list "
		        "was not updated correctly. Please see the IntListOK "
		        "function for details.\n");
		exit(EXIT_FAILURE);
	}
}

static void processArgs(int argc, char *argv[], bool *verbose) {
	char *outFileName = NULL;

	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-v") == 0) {
			*verbose = true;
		} else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
			i++;
			outFileName = argv[i];
		} else {
			usage(argv[0]);
			exit(EXIT_FAILURE);
		}
	}

	out = stdout;
	if (outFileName != NULL) {
		out = fopen(outFileName, "w");
		if (out == NULL) {
			fprintf(stderr, "error: failed to open '%s'\n", outFileName);
			exit(EXIT_FAILURE);
		}
	}
}

static void usage(char *progName) {
	printf("usage: %s [-v] [-o outfile]\n", progName);
}

