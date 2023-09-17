// runBst.c - a command-line interface to the BST module

// !!! DO NOT MODIFY THIS FILE !!!

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"

#define MAX 1024

static void processOptions(int argc, char *argv[]);
static void showUsage(char *progname);
static void showWelcomeMessage(void);
static int getCommand(char *buf);
static char **tokenize(char *s, int *ntokens);
static void freeTokens(char **tokens);
static void showHelp(void);

static void runInsert(struct node **t, int argc, char *argv[]);
static void runFind(struct node **t, int argc, char *argv[]);
static void runPrint(struct node **t, int argc, char *argv[]);
static void runNumNodes(struct node **t, int argc, char *argv[]);
static void runNumLeaves(struct node **t, int argc, char *argv[]);
static void runRange(struct node **t, int argc, char *argv[]);
static void runDeleteLeaves(struct node **t, int argc, char *argv[]);
static void runInOrder(struct node **t, int argc, char *argv[]);
static void runPreOrder(struct node **t, int argc, char *argv[]);
static void runPostOrder(struct node **t, int argc, char *argv[]);
static void runLevelOrder(struct node **t, int argc, char *argv[]);
static void showCmdHelp(void);

////////////////////////////////////////////////////////////////////////

typedef struct command {
	char  *code;
	void (*fn)(struct node **, int, char **);
	char  *argHint;
	char  *helpMsg;
} Command;

static Command COMMANDS[] = {
	{"+", runInsert,       "<num>...",  "insert values in the given order"},
	{"f", runFind,         "<num>",     "check if a value is in the BST"},
	{"p", runPrint,        "",          "print the BST"},
	{"n", runNumNodes,     "",          "get the size of the BST"},
	{"l", runNumLeaves,    "",          "get the number of leaves in the BST"},
	{"r", runRange,        "",          "get the range of the BST"},
	{"d", runDeleteLeaves, "",          "delete all leaves in the BST"},
	{"I", runInOrder,      "",          "print the in-order traversal of the BST"},
	{"P", runPreOrder,     "",          "print the pre-order traversal of the BST"},
	{"O", runPostOrder,    "",          "print the post-order traversal of the BST"},
	{"L", runLevelOrder,   "",          "print the level-order traversal of the BST"},
	{"?", NULL,            "",          "show this message"},
	{"q", NULL,            "",          "quit"},
};

////////////////////////////////////////////////////////////////////////

static bool ECHO = false;
static Command *currCommand = NULL;

int main(int argc, char *argv[]) {
	processOptions(argc, argv);
	showWelcomeMessage();

	struct node *t = bstNew();
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

			int numCommands = sizeof(COMMANDS) / sizeof(Command);
			for (int i = 0; i < numCommands; i++) {
				if (strcmp(cmdName, COMMANDS[i].code) == 0) {
					validCommand = true;
					currCommand = &COMMANDS[i];
					COMMANDS[i].fn(&t, ntokens, tokens);
				}
			}

			if (!validCommand) {
				printf("Unknown command '%s'\n", cmdName);
			}
		}
		freeTokens(tokens);
	}

	bstFree(t);
}

static void processOptions(int argc, char *argv[]) {
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-h") == 0) {
			showUsage(argv[0]);
			exit(EXIT_SUCCESS);
		} else if (strcmp(argv[i], "-e") == 0) {
			ECHO = true;
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
	printf("Interactive BST Tester\n");
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
	char *separators = " \t\n";
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
	int numCommands = sizeof(COMMANDS) / sizeof(Command);
	for (int i = 0; i < numCommands; i++) {
		printf("%5s %-18s %s\n", COMMANDS[i].code, COMMANDS[i].argHint,
		                         COMMANDS[i].helpMsg);
	}
	printf("\n");
}

////////////////////////////////////////////////////////////////////////
// Commands

static void runInsert(struct node **t, int argc, char *argv[]) {
	if (argc < 2) {
		showCmdHelp();
		return;
	}

	int elem = 0;
	char c;
	for (int i = 1; i < argc; i++) {
		if (sscanf(argv[i], "%d%c", &elem, &c) != 1) {
			printf("Error: Invalid value '%s'\n", argv[i]);
			return;
		}
	}
	
	for (int i = 1; i < argc; i++) {
		sscanf(argv[i], "%d", &elem);
		*t = bstInsert(*t, elem);
		printf("Inserted %d\n", elem);
	}
}

static void runFind(struct node **t, int argc, char *argv[]) {
	if (argc != 2) {
		showCmdHelp();
		return;
	}

	int elem = 0;
	char c;
	if (sscanf(argv[1], "%d%c", &elem, &c) != 1) {
		printf("Error: Invalid value '%s'\n", argv[1]);
		return;
	}

	bool result = bstFind(*t, elem);
	printf("%d is%s in the BST\n", elem, result ? "" : " not");
}

static void runPrint(struct node **t, int argc, char *argv[]) {
	if (argc != 1) {
		showCmdHelp();
		return;
	}
	
	bstShow(*t);
}

static void runNumNodes(struct node **t, int argc, char *argv[]) {
	if (argc != 1) {
		showCmdHelp();
		return;
	}

	int numNodes = bstNumNodes(*t);
	printf("The BST contains %d %s\n", numNodes,
	       numNodes == 1 ? "node" : "nodes");
}

static void runNumLeaves(struct node **t, int argc, char *argv[]) {
	if (argc != 1) {
		showCmdHelp();
		return;
	}

	int numLeaves = bstNumLeaves(*t);
	printf("The BST contains %d %s\n", numLeaves,
	       numLeaves == 1 ? "leaf" : "leaves");
}

static void runRange(struct node **t, int argc, char *argv[]) {
	if (argc != 1) {
		showCmdHelp();
		return;
	}

	int range = bstRange(*t);
	printf("The range of the BST is %d\n", range);
}

static void runDeleteLeaves(struct node **t, int argc, char *argv[]) {
	if (argc != 1) {
		showCmdHelp();
		return;
	}

	*t = bstDeleteLeaves(*t);
	printf("Deleted all the leaves in the BST\n");
}

static void runInOrder(struct node **t, int argc, char *argv[]) {
	if (argc != 1) {
		showCmdHelp();
		return;
	}

	printf("In-order traversal: ");
	bstInOrder(*t);
	printf("\n");
}

static void runPreOrder(struct node **t, int argc, char *argv[]) {
	if (argc != 1) {
		showCmdHelp();
		return;
	}

	printf("Pre-order traversal: ");
	bstPreOrder(*t);
	printf("\n");
}

static void runPostOrder(struct node **t, int argc, char *argv[]) {
	if (argc != 1) {
		showCmdHelp();
		return;
	}

	printf("Post-order traversal: ");
	bstPostOrder(*t);
	printf("\n");
}

static void runLevelOrder(struct node **t, int argc, char *argv[]) {
	if (argc != 1) {
		showCmdHelp();
		return;
	}

	printf("Level-order traversal: ");
	bstLevelOrder(*t);
	printf("\n");
}

static void showCmdHelp(void) {
    printf("Usage: %s %s\n", currCommand->code, currCommand->argHint);
}

////////////////////////////////////////////////////////////////////////

