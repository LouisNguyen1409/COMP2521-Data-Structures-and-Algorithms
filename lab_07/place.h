// Definition of places and power lines 

// !!! DO NOT MODIFY THIS FILE !!!

#ifndef PLACE_H
#define PLACE_H

#include <stdbool.h>

#define MAX_PLACE_NAME 31

struct place {
    char name[MAX_PLACE_NAME + 1];
    int  x;
    int  y;
};

struct powerLine {
    struct place p1;
    struct place p2;
};

#endif
