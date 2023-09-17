// DFS maze solver

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cell.h"
#include "matrix.h"
#include "Maze.h"
#include "Stack.h"

static bool isCell(Maze m, struct cell c);
static void getPath(struct cell **pred, struct cell src, struct cell dest, Maze m);

bool solve(Maze m) {
    int row = MazeHeight(m);
    int col = MazeWidth(m);
    bool **visited = createBoolMatrix(row, col);
    struct cell **pred = createCellMatrix(row, col);
    struct cell src = MazeGetStart(m);
    Stack s = StackNew();
    StackPush(s, src);
    bool found = false;
    while (!found && !StackIsEmpty(s)) {
        struct cell curr = StackPop(s);
        bool dest = MazeVisit(m, curr);
        if (dest == true) {
            getPath(pred, src, curr, m);
            found = true;
            break;
        }

        if (visited[curr.row][curr.col]) {
            continue;
        }
        visited[curr.row][curr.col] = true;

        struct cell neighbors[4] = {
            {curr.row - 1, curr.col},
            {curr.row, curr.col + 1},
            {curr.row + 1, curr.col},
            {curr.row, curr.col - 1}
        };
        for (int w = 0; w < 4; w++) {
            struct cell n = neighbors[w];
            if (isCell(m, n) && !MazeIsWall(m, n) && !visited[n.row][n.col]) {
                pred[n.row][n.col] = curr;
                StackPush(s, n);
            }
        }
    }
    freeBoolMatrix(visited);
    freeCellMatrix(pred);
    StackFree(s);
    return found;
}

static bool isCell(Maze m, struct cell c) {
    int col = MazeHeight(m);
    int row = MazeWidth(m);
    if (c.row >= 0 && c.row < row && c.col >= 0 && c.col < col) {
        return true;
    }
    return false;
}

static void getPath(struct cell **pred, struct cell src, struct cell dest, Maze m) {
    struct cell curr = dest;
    while (!(curr.row == src.row && curr.col == src.col)) {
        MazeMarkPath(m, curr);
        curr = pred[curr.row][curr.col];
    }
    MazeMarkPath(m, src);
}
