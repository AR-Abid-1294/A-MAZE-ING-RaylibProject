#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "raylib.h"
#include "raymath.h"

#define LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))

#define SCREENWIDTH 800
#define SCREENHEIGHT 600

#define MAZEWIDTH 51
#define MAZEHEIGHT 35
#define CELLSIZE 15
int maze[MAZEHEIGHT][MAZEWIDTH];

#define MAZE_MARGIN_X 15
#define MAZE_MARGIN_Y 15

#define SPEED_MAX 120.0f

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