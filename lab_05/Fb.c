// Implementation of the FriendBook ADT

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Fb.h"
#include "List.h"
#include "Map.h"
#include "Queue.h"

#define DEFAULT_CAPACITY 1 // DO NOT change this line

struct adjNode {
    int v;
    struct adjNode *next;
};

// DO NOT modify this struct
struct fb {
    int numPeople;
    int capacity;

    char **names; // the id of a person is simply the index
                  // that contains their name in this array
    
    Map nameToId; // maps names to ids

    struct adjNode **adj; // adjacency lists, kept in increasing order
};

static void increaseCapacity(Fb fb);
static char *myStrdup(char *s);
static int nameToId(Fb fb, char *name);

static struct adjNode *adjListInsert(struct adjNode *l, int v);
static struct adjNode *newAdjNode(int v);
static bool inAdjList(struct adjNode *l, int v);
static void freeAdjList(struct adjNode *l);
struct adjNode *free_friend(struct adjNode *head, int id);
bool nameInArray (char *name, struct recommendation recs[], int len, int *pos);
void sort(struct recommendation recs[],int length);
////////////////////////////////////////////////////////////////////////

// Creates a new instance of FriendBook
Fb FbNew(void) {
    Fb fb = malloc(sizeof(*fb));
    if (fb == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    fb->numPeople = 0;
    fb->capacity = DEFAULT_CAPACITY;
    
    fb->names = calloc(fb->capacity, sizeof(char *));
    if (fb->names == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    
    fb->nameToId = MapNew();

    fb->adj = calloc(fb->capacity, sizeof(struct adjNode *));
    if (fb->adj == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    return fb;
}

void FbFree(Fb fb) {
    for (int i = 0; i < fb->capacity; i++) {
        freeAdjList(fb->adj[i]);
    }
    free(fb->adj);

    MapFree(fb->nameToId);

    for (int i = 0; i < fb->numPeople; i++) {
        free(fb->names[i]);
    }
    free(fb->names);
    
    free(fb);
}

int FbNumPeople(Fb fb) {
    return fb->numPeople;
}

bool FbAddPerson(Fb fb, char *name) {
    if (fb->numPeople == fb->capacity) {
        increaseCapacity(fb);
    }

    if (!MapContains(fb->nameToId, name)) {
        int id = fb->numPeople++;
        fb->names[id] = myStrdup(name);
        MapSet(fb->nameToId, name, id);
        return true;
    } else {
        return false;
    }
}

static void increaseCapacity(Fb fb) {
    int newCapacity = fb->capacity * 2;
    
    fb->names = realloc(fb->names, newCapacity * sizeof(char *));
    if (fb->names == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    for (int i = fb->capacity; i < newCapacity; i++) {
        fb->names[i] = NULL;
    }
    
    fb->adj = realloc(fb->adj, newCapacity * sizeof(struct adjNode));
    if (fb->adj == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    for (int i = fb->capacity; i < newCapacity; i++) {
        fb->adj[i] = NULL;
    }
    
    fb->capacity = newCapacity;
}

bool FbHasPerson(Fb fb, char *name) {
    return MapContains(fb->nameToId, name);
}

List FbGetPeople(Fb fb) {
    List l = ListNew();
    for (int id = 0; id < fb->numPeople; id++) {
        ListAppend(l, fb->names[id]);
    }
    return l;
}

bool FbFriend(Fb fb, char *name1, char *name2) {
    int id1 = nameToId(fb, name1);
    int id2 = nameToId(fb, name2);
    assert(id1 != id2);

    if (!inAdjList(fb->adj[id1], id2)) {
        fb->adj[id1] = adjListInsert(fb->adj[id1], id2);
        fb->adj[id2] = adjListInsert(fb->adj[id2], id1);
        return true;
    } else {
        return false;
    }
}

bool FbIsFriend(Fb fb, char *name1, char *name2) {
    int id1 = nameToId(fb, name1);
    int id2 = nameToId(fb, name2);
    return inAdjList(fb->adj[id1], id2);
}

////////////////////////////////////////////////////////////////////////
// Your tasks

int FbNumFriends(Fb fb, char *name) {
    int id = nameToId(fb, name);
    int numfriends = 0;
    struct adjNode *curr = fb->adj[id];
    while (curr != NULL) {
        numfriends++;
        curr = curr->next;
    }
    return numfriends;
}

bool FbUnfriend(Fb fb, char *name1, char *name2) {
    int id_1 = nameToId(fb, name1);
    int id_2 = nameToId(fb, name2);
    bool is_friend = FbIsFriend(fb, name1, name2);
    if (is_friend == false) {
        return is_friend;
    }
    fb->adj[id_1] = free_friend(fb->adj[id_1], id_2);
    fb->adj[id_2] = free_friend(fb->adj[id_2], id_1);
    return is_friend;
}

struct adjNode *free_friend(struct adjNode *head, int id) {
    struct adjNode *curr = head;
    struct adjNode *pre = NULL;
    if (head->v == id) {
        head = head->next;
        free(curr);
        return head;
    }
    while (curr != NULL && curr->v != id) {
        pre = curr;
        curr = curr->next;
    }

    pre->next = curr->next;
    free(curr);
    return head;
}


List FbMutualFriends(Fb fb, char *name1, char *name2) {
    int id_1 = nameToId(fb, name1);
    int id_2 = nameToId(fb, name2);
    struct adjNode *curr_1 = fb->adj[id_1];
    List l = ListNew();
    while (curr_1 != NULL) {
        struct adjNode *curr_2 = fb->adj[id_2];
        while (curr_2 != NULL) {
            if (curr_1->v == curr_2->v) {
                ListAppend(l, fb->names[curr_1->v]);
            }
            curr_2 = curr_2->next;
        }
        curr_1 = curr_1->next;
    }
    return l;
}

void sort(struct recommendation recs[],int length) {
    int temp;
    for (int i = 0; i < length; i++) {     
        for (int j = i + 1; j < length; j++) {     
            if(recs[i].numMutualFriends < recs[j].numMutualFriends) {    
                temp = recs[i].numMutualFriends;    
                recs[i].numMutualFriends = recs[j].numMutualFriends;    
                recs[j].numMutualFriends = temp;    
            }     
        }     
    }    
}

int FbFriendRecs1(Fb fb, char *name, struct recommendation recs[]) {
    int id = nameToId(fb, name);
    struct adjNode *curr = fb->adj[id];
    int i = 0;
    int pos = 0;
    while (curr != NULL) {
        struct adjNode *sub_curr = fb->adj[curr->v];
        while (sub_curr != NULL) {
            char *friend = fb->names[sub_curr->v];
            if (!FbIsFriend(fb, name, friend) && sub_curr->v != id) {
                if (nameInArray(friend, recs, i, &pos) == true) {
                    recs[pos].numMutualFriends += 1;
                } else {
                    recs[i].name = friend;
                    recs[i].numMutualFriends = 1; 
                    i++;
                }
            }
            sub_curr = sub_curr->next;
        }
        curr = curr->next;
    }
    sort(recs, i);
    return i;
}


bool nameInArray (char *name, struct recommendation recs[], int len, int *pos) {
    for (int i = 0; i <= len; i++) {
        if (recs[i].name == name) {
            *pos = i;
            return true;
        }
    }
    return false;
}
////////////////////////////////////////////////////////////////////////
// Optional task

List FbFriendRecs2(Fb fb, char *name) {
    // TODO: Complete this function
    List l = ListNew();
    return l;
}

////////////////////////////////////////////////////////////////////////
// Helper Functions

static char *myStrdup(char *s) {
    char *copy = malloc((strlen(s) + 1) * sizeof(char));
    if (copy == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    return strcpy(copy, s);
}

// Converts a name to an ID. Raises an error if the name doesn't exist.
static int nameToId(Fb fb, char *name) {
    if (!MapContains(fb->nameToId, name)) {
        fprintf(stderr, "error: person '%s' does not exist!\n", name);
        exit(EXIT_FAILURE);
    }
    return MapGet(fb->nameToId, name);
}

static struct adjNode *adjListInsert(struct adjNode *l, int v) {
    if (l == NULL || v < l->v) {
        struct adjNode *new = newAdjNode(v);
        new->next = l;
        return new;
    } else if (v == l->v) {
        return l;
    } else {
        l->next = adjListInsert(l->next, v);
        return l;
    }
}

static struct adjNode *newAdjNode(int v) {
    struct adjNode *n = malloc(sizeof(*n));
    if (n == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    n->v = v;
    n->next = NULL;
    return n;
}

static bool inAdjList(struct adjNode *l, int v) {
    for (struct adjNode *n = l; n != NULL && n->v <= v; n = n->next) {
        if (n->v == v) {
            return true;
        }
    }
    return false;
}

static void freeAdjList(struct adjNode *l) {
    struct adjNode *n = l;
    while (n != NULL) {
        struct adjNode *temp = n;
        n = n->next;
        free(temp);
    }
}

