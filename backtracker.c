#include "backtracker.h"

void generateMaze_backtracker(Maze *maze)
{
    maze->current_cell->cellState = VISITED;

    shuffleDirections();

    for (int i = 0; i < 4; i++)
    {
        int nx = maze->current_cell->x + directions[i][0];
        int ny = maze->current_cell->y + directions[i][1];

        if (isCellValid(nx, ny, *maze))
        {
            Cell *neighbor_cell = &maze->cells[ny][nx];

            if (neighbor_cell->cellState == UNVISITED)
            {
                Cell *old_current_cell = maze->current_cell;
                maze->current_cell = neighbor_cell;
                breakWall(maze, old_current_cell, maze->current_cell);

                generateMaze_backtracker(maze);
                maze->current_cell = old_current_cell;
            }
        }
    }
}