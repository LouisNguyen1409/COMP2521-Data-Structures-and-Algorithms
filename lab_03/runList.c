// runList.c - a command-line interface to the List ADT

// !!! DO NOT MODIFY THIS FILE !!!

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"

#define MAX 64

static void processOptions(int argc, char *argv[]);
static void showUsage(char *progname);
static void showWelcomeMessage(void);
static int getCommand(char *buf);
static char **tokenize(char *s, int *ntokens);
static void freeTokens(char **tokens);
static void showHelp(void);

static void runAddStart(List l, int argc, char *argv[]);
static void runAddEnd(List l, int argc, char *argv[]);
static void runDeleteStart(List l, int argc, char *argv[]);
static void runDeleteEnd(List l, int argc, char *argv[]);
static void runFirst(List l, int argc, char *argv[]);
static void runLast(List l, int argc, char *argv[]);
static void runSize(List l, int argc, char *argv[]);
static void runContains(List l, int argc, char *argv[]);
static void runShow(List l, int argc, char *argv[]);
static void showCmdHelp(void);

////////////////////////////////////////////////////////////////////////

struct command {
	char  *code;
	void (*fn)(List, int, char **);
	char  *argHint;
	char  *helpMsg;
};

static struct command COMMANDS[] = {
	{"+s", runAddStart,    "<num>", "add an element to the start"},
	{"+e", runAddEnd,      "<num>", "add an element to the end"},
	{"-s", runDeleteStart, "",      "delete an element from the start"},
	{"-e", runDeleteEnd,   "",      "delete an element from the end"},
	{"f",  runFirst,       "",      "get the first element"},
	{"l",  runLast,        "",      "get the last element"},
	{"s",  runSize,        "",      "get the size of the list"},
	{"c",  runContains,    "<num>", "check if an element is in the list"},
	{"p",  runShow,        "",      "print the list"},
	{"?",  NULL,           "",      "show this message"},
	{"q",  NULL,           "",      "quit"},
};

////////////////////////////////////////////////////////////////////////

static bool ECHO = false;
static struct command *currCommand = NULL;

int main(int argc, char *argv[]) {
	processOptions(argc, argv);
	showWelcomeMessage();

	List l = ListNew();
	bool done = false;
	char cmd[MAX + 1] = {0};

	while (!done && getCommand(cmd)) {
		if (ECHO) {
		    printf("%s", cmd);
		}

		int ntokens = 0;
		char **tokens = tokenize(cmd, &ntokens);
		if (ntokens == 0) {
			free(tokens);
			continue;
		}
		
		char *cmdName = tokens[0];

		// Meta-commands
		if (strcmp(cmdName, "?") == 0) {
			showHelp();
		} else if (strcmp(cmdName, "q") == 0) {
			done = true;
		
		// Actual commands
		} else {
			bool validCommand = false;

			int numCommands = sizeof(COMMANDS) / sizeof(struct command);
			for (int i = 0; i < numCommands; i++) {
				if (strcmp(cmdName, COMMANDS[i].code) == 0) {
					validCommand = true;
					currCommand = &COMMANDS[i];
					COMMANDS[i].fn(l, ntokens, tokens);
				}
			}

			if (!validCommand) {
				printf("Unknown command '%s'\n", cmdName);
			}
		}
		freeTokens(tokens);
	}

	ListFree(l);
}

static void processOptions(int argc, char *argv[]) {
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-e") == 0) {
			ECHO = true;
		} else {
			showUsage(argv[0]);
			exit(EXIT_FAILURE);
		}
	}
}

static void showUsage(char *progName) {
	printf("Usage: %s [options]...\n"
	       "Options:\n"
	       "    -h      show this help message\n"
	       "    -e      echo - echo all commands\n",
	       progName);
}

static void showWelcomeMessage(void) {
	printf("Interactive List Tester\n");
	printf("Enter ? to see the list of commands.\n");
}

static int getCommand(char *buf) {
	printf("> ");
	if (fgets(buf, MAX, stdin) != NULL) {
		int len = strlen(buf);
		if (len > 0 && buf[len - 1] != '\n') {
			buf[len] = '\n';
			buf[len + 1] = '\0';
		}
		return 1;
	} else {
		return 0;
	}
}

static char **tokenize(char *s, int *ntokens) {
	char *separators = " \t\r\n";
	*ntokens = 0;

	char **tokens = calloc((strlen(s) + 1), sizeof(*tokens));
	assert(tokens != NULL);

	while (*s != '\0') {
		s += strspn(s, separators);

		if (*s == '\0') {
		    break;
		}

		size_t length = strcspn(s, separators);

		char *token = strndup(s, length);
		assert(token != NULL);
		s += length;

		tokens[*ntokens] = token;
		(*ntokens)++;
	}

	tokens[*ntokens] = NULL;

	tokens = realloc(tokens, (*ntokens + 1) * sizeof(*tokens));
	assert(tokens != NULL);

	return tokens;
}

static void freeTokens(char **tokens) {
	for (int i = 0; tokens[i] != NULL; i++) {
		free(tokens[i]);
	}
	free(tokens);
}

static void showHelp(void) {
	printf("Commands:\n");
	int numCommands = sizeof(COMMANDS) / sizeof(struct command);
	for (int i = 0; i < numCommands; i++) {
		printf("%5s %-18s %s\n", COMMANDS[i].code, COMMANDS[i].argHint,
		                         COMMANDS[i].helpMsg);
	}
	printf("\n");
}

////////////////////////////////////////////////////////////////////////
// Commands

static void runAddStart(List l, int argc, char *argv[]) {
	if (argc != 2) {
		showCmdHelp();
		return;
	}

	int elem = 0;
	char c;
	if (sscanf(argv[1], "%d%c", &elem, &c) != 1) {
		showCmdHelp();
		return;
	}

	ListAddStart(l, elem);
	printf("Added %d to the start of the list\n", elem);
}

static void runAddEnd(List l, int argc, char *argv[]) {
	if (argc != 2) {
		showCmdHelp();
		return;
	}

	int elem = 0;
	char c;
	if (sscanf(argv[1], "%d%c", &elem, &c) != 1) {
		showCmdHelp();
		return;
	}

	ListAddEnd(l, elem);
	printf("Added %d to the end of the list\n", elem);
}

static void runDeleteStart(List l, int argc, char *argv[]) {
	if (argc != 1) {
		showCmdHelp();
		return;
	}

	if (ListSize(l) == 0) {
		printf("Error: The list is empty!\n");
		return;
	}

	int elem = ListDeleteStart(l);
	printf("Deleted %d from the start of the list\n", elem);
}

static void runDeleteEnd(List l, int argc, char *argv[]) {
	if (argc != 1) {
		showCmdHelp();
		return;
	}

	if (ListSize(l) == 0) {
		printf("Error: The list is empty!\n");
		return;
	}

	int elem = ListDeleteEnd(l);
	printf("Deleted %d from the end of the list\n", elem);
}

static void runFirst(List l, int argc, char *argv[]) {
	if (argc != 1) {
		showCmdHelp();
		return;
	}

	if (ListSize(l) == 0) {
		printf("Error: The list is empty!\n");
		return;
	}

	int elem = ListFirst(l);
	printf("The first element in the list is %d\n", elem);
}

static void runLast(List l, int argc, char *argv[]) {
	if (argc != 1) {
		showCmdHelp();
		return;
	}

	if (ListSize(l) == 0) {
		printf("Error: The list is empty!\n");
		return;
	}

	int elem = ListLast(l);
	printf("The last element in the list is %d\n", elem);
}

static void runSize(List l, int argc, char *argv[]) {
	if (argc != 1) {
		showCmdHelp();
		return;
	}

	int size = ListSize(l);
	printf("The size of the list is %d\n", size);
}

static void runContains(List l, int argc, char *argv[]) {
	if (argc != 2) {
		showCmdHelp();
		return;
	}

	int elem = 0;
	char c;
	if (sscanf(argv[1], "%d%c", &elem, &c) != 1) {
		showCmdHelp();
		return;
	}

	bool res = ListContains(l, elem);
	printf("%d %s in the list\n", elem, res ? "is" : "is not");
}

static void runShow(List l, int argc, char *argv[]) {
	if (argc != 1) {
		showCmdHelp();
		return;
	}

	ListShow(l);
	printf("\n");
}

static void showCmdHelp(void) {
    printf("Usage: %s %s\n", currCommand->code, currCommand->argHint);
}

////////////////////////////////////////////////////////////////////////

