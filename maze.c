#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "maze.h"
#include "player.h"

int maze[MAZEHEIGHT][MAZEWIDTH];

// for time sector
int frames_count = 0;
int net_time = 100; // seconds

void initializeMaze()
{
    for (int y = 0; y < MAZEHEIGHT; y++)
    {
        for (int x = 0; x < MAZEWIDTH; x++)
        {
            maze[y][x] = 1; // start with everything solid
        }
    }
}

// Check if a cell is inside the maze
int isCellValid(int x, int y)
{
    return ((x > 0 && x < MAZEWIDTH - 1) && (y > 0 && y < MAZEHEIGHT - 1));
}

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

void generateMaze(int x, int y)
{
    maze[y][x] = 0;

    int directions[4][2] = {{0, 2}, {0, -2}, {2, 0}, {-2, 0}}; // (y,x) for maze (array)
    shuffleDirections(directions);

    for (int i = 0; i < 4; i++)
    {
        int delx = directions[i][0];
        int dely = directions[i][1];
        int x_ = x + delx;
        int y_ = y + dely;

        if (isCellValid(x_, y_) && maze[y_][x_] == 1)
        {
            maze[y + dely / 2][x + delx / 2] = 0;
            generateMaze(x_, y_);
        }
    }
}

void drawMaze(Vector2 pos, float block_side_len, Texture2D block)
{
    for (int y = 0; y < MAZEHEIGHT; y++)
    {
        float startx = pos.x;
        for (int x = 0; x < MAZEWIDTH; x++)
        {
            if (maze[y][x] == 1)
            {
                // Rectangle block = {pos.x, pos.y, block_side_len, block_side_len};
                // DrawRectangleRec(block, DARKGREEN);
                DrawTexturePro(block,
                               (Rectangle){0, 0, block.width, block.height},
                               (Rectangle){pos.x, pos.y, block_side_len, block_side_len},
                               Vector2Zero(), 0, WHITE);
            }
            else if (y == MAZEHEIGHT - 2 && x == MAZEWIDTH - 2)
            {
                Rectangle block = {pos.x, pos.y, block_side_len, block_side_len};
                DrawRectangleRec(block, DARKBLUE);
                DrawRectangleLinesEx(block, 5, ORANGE);
            }
            pos.x += block_side_len;
        }
        pos.x = startx;
        pos.y += block_side_len;
    }
}

int isPostionFree(Vector2 pos)
{
    float margin = (CELLSIZE / 2) * 0.9f;

    int cellIndex1 = (pos.y - MAZE_MARGIN_Y - margin) / CELLSIZE;
    int cellIndex2 = (pos.x - MAZE_MARGIN_X - margin) / CELLSIZE;

    int cellIndex3 = (pos.y - MAZE_MARGIN_Y + margin) / CELLSIZE;
    int cellIndex4 = (pos.x - MAZE_MARGIN_X + margin) / CELLSIZE;

    if (maze[cellIndex1][cellIndex2] == 0 &&
        maze[cellIndex3][cellIndex4] == 0 &&
        maze[cellIndex1][cellIndex4] == 0 &&
        maze[cellIndex3][cellIndex2] == 0)
        return 1;
    else
        return 0;
}

///////////////
///////////////
// new (2) approach

void initializeMaze2(Maze *maze, int height, int width)
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

bool isCellValid2(int x, int y, Maze maze)
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

void generateMaze2(Maze *maze, Cell *cell)
{
    cell->cellState = VISITED;

    int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}}; // (y,x) for maze (array)
    shuffleDirections(directions);

    for (int i = 0; i < 4; i++)
    {
        int nx = cell->x + directions[i][0];
        int ny = cell->y + directions[i][1];
        Cell *neighbor_cell;
        if (isCellValid2(nx, ny, *maze))
        {
            neighbor_cell = &maze->cells[ny][nx];
            if (neighbor_cell->cellState == UNVISITED)
            {
                breakWall(maze, cell, neighbor_cell);
                generateMaze2(maze, neighbor_cell);
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

void drawMaze2(Maze *maze, Vector2 pos, float tile_side_len, Player player)
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

void destroyMaze2(Maze *maze)
{
    for (int i = 0; i < maze->height; i++)
    {
        free(maze->cells[i]);
    }
    free(maze->cells);
}