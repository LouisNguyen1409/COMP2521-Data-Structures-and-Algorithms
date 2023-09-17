// runFb.c - a command-line interface to Friendbook

// !!! DO NOT MODIFY THIS FILE !!!

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Fb.h"
#include "List.h"

#define MAX 8192

static void processOptions(int argc, char *argv[]);
static void showUsage(char *progName);
static void showWelcomeMessage(void);
static bool getCommand(char *buf);
static char **tokenize(char *s, int *ntokens);
static void freeTokens(char **tokens);
static void showHelp(void);

static void runAddPerson(Fb fb, int argc, char *argv[]);
static void runListPeople(Fb fb, int argc, char *argv[]);
static void runFriend(Fb fb, int argc, char *argv[]);
static void runUnfriend(Fb fb, int argc, char *argv[]);
static void runFriendshipStatus(Fb fb, int argc, char *argv[]);
static void runNumFriends(Fb fb, int argc, char *argv[]);
static void runMutualFriends(Fb fb, int argc, char *argv[]);
static void runFriendRecs1(Fb fb, int argc, char *argv[]);
static void runFriendRecs2(Fb fb, int argc, char *argv[]);
static void showCmdHelp(void);

static void showList(List l);

////////////////////////////////////////////////////////////////////////

struct command {
    char  *code;
    void (*fn)(Fb, int, char **);
    char  *argHint;
    char  *helpMsg;
};

static struct command COMMANDS[] = {
    {"+", runAddPerson,         "<name>",
                                "add a new person"},
    {"l", runListPeople,        "",
                                "list the names of all people"},
    {"f", runFriend,            "<name1> <name2>",
                                "friend two people"},
    {"u", runUnfriend,          "<name1> <name2>",
                                "unfriend two people"},
    {"s", runFriendshipStatus,  "<name1> <name2>",
                                "get the friendship status of two people"},
    {"n", runNumFriends,        "<name>",
                                "get the number of friends a person has"},
    {"m", runMutualFriends,     "<name1> <name2>",
                                "list all mutual friends of two people"},
    {"r", runFriendRecs1,       "<name>",
                                "get friend recommendations for a person "
                                "based on mutual friends"},
    {"R", runFriendRecs2,       "<name>",
                                "get friend recommendations for a person "
                                "based on friendship closeness"},
    // Meta-commands
    {"?", NULL,                 "", "show this message"},
    {"q", NULL,                 "", "quit"},
};

////////////////////////////////////////////////////////////////////////

static bool echo = false;
static struct command *currCommand = NULL;

int main(int argc, char *argv[]) {
    processOptions(argc, argv);
    showWelcomeMessage();

    Fb fb = FbNew();
    bool done = false;
    char cmd[MAX + 1] = {0};

    while (!done && getCommand(cmd)) {
        if (echo) {
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
                    COMMANDS[i].fn(fb, ntokens, tokens);
                }
            }

            if (!validCommand) {
                printf("Unknown command '%s'\n", cmdName);
            }
        }
        freeTokens(tokens);
    }

    FbFree(fb);
}

static void processOptions(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            showUsage(argv[0]);
            exit(EXIT_SUCCESS);
        } else if (strcmp(argv[i], "-e") == 0) {
            echo = true;
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
    printf("Friendbook v1.0\n");
    printf("Enter ? to see the list of commands.\n");
}

static bool getCommand(char *buf) {
    printf("> ");
    if (fgets(buf, MAX, stdin) != NULL) {
        int len = strlen(buf);
        if (len > 0 && buf[len - 1] != '\n') {
            buf[len] = '\n';
            buf[len + 1] = '\0';
        }
        return true;
    } else {
        return false;
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

static void runAddPerson(Fb fb, int argc, char *argv[]) {
    if (argc != 2) {
        showCmdHelp();
        return;
    }

    char *name = argv[1];

    if (FbAddPerson(fb, name)) {
        printf("%s was successfully added to Friendbook!\n", name);
    } else {
        printf("There is already a person named %s\n", name);
    }
}

static void runListPeople(Fb fb, int argc, char *argv[]) {
    if (argc != 1) {
        showCmdHelp();
        return;
    }

    List l = FbGetPeople(fb);
    printf("People:\n");
    showList(l);
    ListFree(l);
}

static void runFriend(Fb fb, int argc, char *argv[]) {
    if (argc != 3) {
        showCmdHelp();
        return;
    }

    char *name1 = argv[1];
    char *name2 = argv[2];
    if (!FbHasPerson(fb, name1)) {
        printf("error: there is no person named '%s'\n", name1);
        return;
    }
    if (!FbHasPerson(fb, name2)) {
        printf("error: there is no person named '%s'\n", name2);
        return;
    }

    if (FbFriend(fb, name1, name2)) {
        printf("Successfully friended %s and %s!\n", name1, name2);
    } else {
        printf("Could not friend %s and %s - they are already friends.\n",
               name1, name2);
    }
}

static void runUnfriend(Fb fb, int argc, char *argv[]) {
    if (argc != 3) {
        showCmdHelp();
        return;
    }

    char *name1 = argv[1];
    char *name2 = argv[2];
    if (!FbHasPerson(fb, name1)) {
        printf("error: there is no person named '%s'\n", name1);
        return;
    }
    if (!FbHasPerson(fb, name2)) {
        printf("error: there is no person named '%s'\n", name2);
        return;
    }

    if (FbUnfriend(fb, name1, name2)) {
        printf("Successfully unfriended %s and %s!\n", name1, name2);
    } else {
        printf("Could not unfriend %s and %s - they are not friends.\n",
               name1, name2);
    }
}

static void runFriendshipStatus(Fb fb, int argc, char *argv[]) {
    if (argc != 3) {
        showCmdHelp();
        return;
    }

    char *name1 = argv[1];
    char *name2 = argv[2];
    if (!FbHasPerson(fb, name1)) {
        printf("error: there is no person named '%s'\n", name1);
        return;
    }
    if (!FbHasPerson(fb, name2)) {
        printf("error: there is no person named '%s'\n", name2);
        return;
    }

    bool status = FbIsFriend(fb, name1, name2);
    printf("%s and %s %s friends.\n", name1, name2,
                                      status ? "are" : "are not");
}

static void runNumFriends(Fb fb, int argc, char *argv[]) {
    if (argc != 2) {
        showCmdHelp();
        return;
    }

    char *name = argv[1];
    if (!FbHasPerson(fb, name)) {
        printf("error: there is no person named '%s'\n", name);
        return;
    }

    int res = FbNumFriends(fb, name);
    printf("%s has %d friend%s.\n", name, res, res == 1 ? "" : "s");
}

static void runMutualFriends(Fb fb, int argc, char *argv[]) {
    if (argc != 3) {
        showCmdHelp();
        return;
    }

    char *name1 = argv[1];
    char *name2 = argv[2];
    if (!FbHasPerson(fb, name1)) {
        printf("error: there is no person named '%s'\n", name1);
        return;
    }
    if (!FbHasPerson(fb, name2)) {
        printf("error: there is no person named '%s'\n", name2);
        return;
    }

    List l = FbMutualFriends(fb, name1, name2);
    printf("%s and %s's mutual friends:\n", name1, name2);
    ListSort(l);
    showList(l);
    ListFree(l);
}

static void runFriendRecs1(Fb fb, int argc, char *argv[]) {
    if (argc != 2) {
        showCmdHelp();
        return;
    }

    char *name = argv[1];
    if (!FbHasPerson(fb, name)) {
        printf("error: there is no person named '%s'\n", name);
        return;
    }

    struct recommendation *recs = calloc(FbNumPeople(fb), sizeof(*recs));
    int numRecs = FbFriendRecs1(fb, name, recs);

    printf("%s's friend recommendations:\n", name);
    for (int i = 0; i < numRecs; i++) {
        printf("\t%-20s%4d mutual friends\n", recs[i].name,
               recs[i].numMutualFriends);
    }

    free(recs);
}

static void runFriendRecs2(Fb fb, int argc, char *argv[]) {
    if (argc != 2) {
        showCmdHelp();
        return;
    }

    char *name = argv[1];
    if (!FbHasPerson(fb, name)) {
        printf("error: there is no person named '%s'\n", name);
        return;
    }

    List l = FbFriendRecs2(fb, name);
    printf("%s's friend recommendations:\n", name);
    showList(l);
    ListFree(l);
}

static void showCmdHelp(void) {
    printf("Usage: %s %s\n", currCommand->code, currCommand->argHint);
}

////////////////////////////////////////////////////////////////////////

static void showList(List l) {
    ListIterator it = ListItNew(l);
    while (ListItHasNext(it)) {
        char *name = ListItNext(it);
        printf("\t%s\n", name);
    }
    ListItFree(it);
}

