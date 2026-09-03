#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "maze.h"
#include "player.h"

int maze[MAZEHEIGHT][MAZEWIDTH];

// for time sector
int frames_count = 0;
int net_time = 100; // seconds

void shuffleDirections(int directions[4][2])
{
    for (int i = 0; i < 4; i++)
    {
        int r = rand() % 4;
        int temp1 = directions[i][0];
        int temp2 = directions[i][1];
        directions[i][0] = directions[r][0];
        directions[i][1] = directions[r][1];
        directions[r][0] = temp1;
        directions[r][1] = temp2;
    }
}

void initializeMaze(Maze *maze, int height, int width)
{
    maze->height = height;
    maze->width = width;

    // initialize cells
    maze->cells = malloc(maze->height * sizeof(Cell *));
    for (int i = 0; i < maze->height; i++)
    {
        maze->cells[i] = malloc(maze->width * sizeof(Cell));
        for (int j = 0; j < maze->width; j++)
        {
            maze->cells[i][j].cellState = UNVISITED;
            maze->cells[i][j].x = j;
            maze->cells[i][j].y = i;
            maze->cells[i][j].up_wall = true;
            maze->cells[i][j].down_wall = true;
            maze->cells[i][j].right_wall = true;
            maze->cells[i][j].left_wall = true;
        }
    }
}

bool isCellValid(int x, int y, Maze maze)
{
    return ((x >= 0 && x <= maze.width - 1) && (y >= 0 && y <= maze.height - 1));
}

void breakWall(Maze *maze, Cell *cell1, Cell *cell2)
{
    if (cell1->x == cell2->x)
    {
        if (cell1->y - cell2->y == 1)
        {
            cell1->up_wall = false;
            cell2->down_wall = false;
        }
        else if (cell2->y - cell1->y == 1)
        {
            cell2->up_wall = false;
            cell1->down_wall = false;
        }
    }
    else if (cell1->y == cell2->y)
    {
        if (cell1->x - cell2->x == 1)
        {
            cell1->left_wall = false;
            cell2->right_wall = false;
        }
        else if (cell2->x - cell1->x == 1)
        {
            cell2->left_wall = false;
            cell1->right_wall = false;
        }
    }
}

void generateMaze(Maze *maze, Cell *cell)
{
    cell->cellState = VISITED;

    int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}}; // (y,x) for maze (array)
    shuffleDirections(directions);

    for (int i = 0; i < 4; i++)
    {
        int nx = cell->x + directions[i][0];
        int ny = cell->y + directions[i][1];
        Cell *neighbor_cell;
        if (isCellValid(nx, ny, *maze))
        {
            neighbor_cell = &maze->cells[ny][nx];
            if (neighbor_cell->cellState == UNVISITED)
            {
                breakWall(maze, cell, neighbor_cell);
                generateMaze(maze, neighbor_cell);
            }
        }
    }
}

void drawBorder(Rectangle rec, Direction dir, float thick, Color color)
{
    Vector2 start, end;
    switch (dir)
    {
    case UP:
        start = (Vector2){rec.x, rec.y};
        end = (Vector2){rec.x + rec.width, rec.y};
        break;

    case DOWN:
        start = (Vector2){rec.x, rec.y + rec.height};
        end = (Vector2){rec.x + rec.width, rec.y + rec.height};
        break;

    case RIGHT:
        start = (Vector2){rec.x + rec.width, rec.y};
        end = (Vector2){rec.x + rec.width, rec.y + rec.height};
        break;

    case LEFT:
        start = (Vector2){rec.x, rec.y};
        end = (Vector2){rec.x, rec.y + rec.height};
        break;

    default:
        break;
    }
    DrawLineEx(start, end, thick, color);
}

void drawMaze(Maze *maze, Vector2 pos, float tile_side_len, Player player)
{
    Texture2D tile;
    for (int y = 0; y < maze->height; y++)
    {
        float startx = pos.x;
        for (int x = 0; x < maze->width; x++)
        {
            if (x == player.x && y == player.y)
            {
                tile = player.player_texture;
            }
            else
            {
                tile = maze->cell_texture;
            }

            Rectangle tile_rec = (Rectangle){pos.x, pos.y, tile_side_len, tile_side_len};
            DrawTexturePro(tile,
                           (Rectangle){0, 0, tile.width, tile.height},
                           tile_rec, Vector2Zero(), 0, WHITE);

            drawBorder(tile_rec, UP, maze->cells[y][x].up_wall ? 2 : 0, WHITE);
            drawBorder(tile_rec, DOWN, maze->cells[y][x].down_wall ? 2 : 0, WHITE);
            drawBorder(tile_rec, RIGHT, maze->cells[y][x].right_wall ? 2 : 0, WHITE);
            drawBorder(tile_rec, LEFT, maze->cells[y][x].left_wall ? 2 : 0, WHITE);

            pos.x += tile_side_len;
        }
        pos.x = startx;
        pos.y += tile_side_len;
    }
}

void destroyMaze(Maze *maze)
{
    for (int i = 0; i < maze->height; i++)
    {
        free(maze->cells[i]);
    }
    free(maze->cells);
}