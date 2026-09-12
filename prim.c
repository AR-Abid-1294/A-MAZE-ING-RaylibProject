#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "prim.h"

void chooseRandFrontier(Maze *maze)
{
    int r = rand() % maze->frontier_count;
    Cell *target_cell = maze->frontiers[r].univisited_cell;
    if (target_cell->cellState == VISITED)
    {
        maze->frontier_count--;
        removeFrontier(maze, r);
    }
    else
    {
        target_cell->cellState = VISITED;
        breakWall(maze, maze->frontiers[r].visisted_cell, maze->frontiers[r].univisited_cell);
        maze->frontier_count--;
        removeFrontier(maze, r);
        addFrontier(maze, target_cell);
    }
}

void generateMaze_prim(Maze *maze)
{
    while (maze->frontier_count)
    {
        chooseRandFrontier(maze);
    }
}
