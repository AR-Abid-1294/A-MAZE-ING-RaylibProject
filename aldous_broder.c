#include "aldous_broder.h"

void generateMaze_aldous_broder(Maze *maze)
{
    while (maze->visited_count < maze->height * maze->width)
    {
        shuffleDirections();

        Cell *neighbour_cell;

        for (int i = 0; i < 4; i++)
        {
            int nx = maze->current_cell->x + directions[i][0];
            int ny = maze->current_cell->y + directions[i][1];

            if (isCellValid(nx, ny, *maze))
            {
                neighbour_cell = &maze->cells[ny][nx];
                break;
            }
        }

        if (neighbour_cell->cellState == UNVISITED)
        {
            neighbour_cell->cellState = VISITED;
            maze->visited_count++;
            breakWall(maze, maze->current_cell, neighbour_cell);
        }

        maze->current_cell = neighbour_cell;
    }
}