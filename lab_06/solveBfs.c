// BFS maze solver

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cell.h"
#include "matrix.h"
#include "Maze.h"
#include "Queue.h"

static bool isCell (Maze m, struct cell c);
static void getPath(struct cell **pred, struct cell src, struct cell dest, Maze m);

bool solve(Maze m) {
    int row = MazeHeight(m);
    int col = MazeWidth(m);
    bool **visited = createBoolMatrix(row, col);
    struct cell **pred = createCellMatrix(row, col);
    Queue q = QueueNew();
    struct cell src = MazeGetStart(m);
    QueueEnqueue(q, src);
    bool found = false;
    visited[src.row][src.col] = true;
    while (!found && !QueueIsEmpty(q)) {
        struct cell curr = QueueDequeue(q);
        
        bool dest = MazeVisit(m, curr);
        if (dest == true) {
            getPath(pred, src, curr, m);
            found = true;
            break;
        }
        struct cell neighbors[4] = {
            {curr.row, curr.col + 1},
            {curr.row, curr.col - 1},
            {curr.row + 1, curr.col},
            {curr.row - 1, curr.col}
        };
        for (int w = 0; w < 4; w++) {
            struct cell n = neighbors[w];
            if (isCell(m, n) && !MazeIsWall(m, n) && !visited[n.row][n.col]) {
                visited[n.row][n.col] = true;
                pred[n.row][n.col] = curr;
                QueueEnqueue(q, n);
            }
        }
    }
    freeBoolMatrix(visited);
    freeCellMatrix(pred);
    QueueFree(q);
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
