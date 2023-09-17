// testIntList.c - a program for testing IntListInsertInOrder

// !!! DO NOT MODIFY THIS FILE !!!

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "IntList.h"

static void processArgs(int argc, char *argv[]);
static void usage(char *progName);
static IntList readIntList(void);

static FILE *out;

int main(int argc, char *argv[]) {
	// process options
	processArgs(argc, argv);

	// read the list
	fprintf(out, "Enter list (must be in ascending order): ");
	IntList l = readIntList();
	if (!IntListIsSorted(l)) {
		fprintf(out, "error: the list is not in ascending order\n");
		IntListFree(l);
		return EXIT_FAILURE;
	}

	// read the number to be inserted
	fprintf(out, "Enter number to insert: ");
	int num;
	if (scanf("%d", &num) != 1) {
		fprintf(out, "error: failed to read number\n");
		IntListFree(l);
		return EXIT_FAILURE;
	}

	fprintf(out, "\n");
	fprintf(out, "Original list:\n");
	IntListPrint(l, out);

	fprintf(out, "List after inserting %d:\n", num);
	IntListInsertInOrder(l, num);
	IntListPrint(l, out);

	if (!IntListOK(l)) {
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
		IntListFree(l);
		return EXIT_FAILURE;
	}

	IntListFree(l);
	fclose(out);
}

static void processArgs(int argc, char *argv[]) {
	char *outFileName = NULL;
	
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
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
	printf("usage: %s [-o outfile]\n", progName);
}

static IntList readIntList(void) {
	char *line = NULL;
	size_t n = 0;
	if (getline(&line, &n, stdin) < 0) {
		fprintf(stderr, "error: failed to read list\n");
		free(line);
		exit(EXIT_FAILURE);
	}

	IntList l = IntListNew();
	char *start = line;
	char *token = strtok(line, " \t");
	while (token != NULL) {
		int num;
		if (sscanf(token, "%d", &num) == 1) {
			IntListAppend(l, num);
		} else {
			break;
		}
		token = strtok(NULL, " \t");
	}

	free(start);
	return l;
}

