#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "raylib.h"

#define SCREENWIDTH 800
#define SCREENHEIGHT 600

#define MAZEWIDTH 51
#define MAZEHEIGHT 35
#define CELLSIZE 15
int maze[MAZEHEIGHT][MAZEWIDTH];

#define MAZE_MARGIN_X 15
#define MAZE_MARGIN_Y 15

//for time sector
int framescount = 0;
int net_time = 100; //seconds

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

void drawMaze(Vector2 pos, float block_side_len)
{
    for (int y = 0; y < MAZEHEIGHT; y++)
    {
        float startx = pos.x;
        for (int x = 0; x < MAZEWIDTH; x++)
        {
            if (maze[y][x] == 1)
            {
                Rectangle block = {pos.x, pos.y, block_side_len, block_side_len};
                DrawRectangleRec(block, DARKGREEN);
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

int willGoRight(Vector2 ballPos)
{
    float cellPosX = ballPos.x + CELLSIZE;
    float cellPosY = ballPos.y;
    int cellIndex1 = (cellPosY - MAZE_MARGIN_Y) / CELLSIZE;
    int cellIndex2 = (cellPosX - MAZE_MARGIN_X) / CELLSIZE;

    if (maze[cellIndex1][cellIndex2] == 0)
        return 1;
    else
        return 0;
}

int willGoLeft(Vector2 ballPos)
{
    float cellPosX = ballPos.x - CELLSIZE;
    float cellPosY = ballPos.y;
    int cellIndex1 = (cellPosY - MAZE_MARGIN_Y) / CELLSIZE;
    int cellIndex2 = (cellPosX - MAZE_MARGIN_X) / CELLSIZE;

    if (maze[cellIndex1][cellIndex2] == 0)
        return 1;
    else
        return 0;
}

int willGoUp(Vector2 ballPos)
{
    float cellPosX = ballPos.x;
    float cellPosY = ballPos.y - CELLSIZE;
    int cellIndex1 = (cellPosY - MAZE_MARGIN_Y) / CELLSIZE;
    int cellIndex2 = (cellPosX - MAZE_MARGIN_X) / CELLSIZE;

    if (maze[cellIndex1][cellIndex2] == 0)
        return 1;
    else
        return 0;
}

int willGoDown(Vector2 ballPos)
{
    float cellPosX = ballPos.x;
    float cellPosY = ballPos.y + CELLSIZE;
    int cellIndex1 = (cellPosY - MAZE_MARGIN_Y) / CELLSIZE;
    int cellIndex2 = (cellPosX - MAZE_MARGIN_X) / CELLSIZE;

    if (maze[cellIndex1][cellIndex2] == 0)
        return 1;
    else
        return 0;
}

int isPostionFree(Vector2 pos)
{
    int cellIndex1 = (pos.y - MAZE_MARGIN_Y - CELLSIZE / 2) / CELLSIZE;
    int cellIndex2 = (pos.x - MAZE_MARGIN_X - CELLSIZE / 2) / CELLSIZE;

    int cellIndex3 = (pos.y - MAZE_MARGIN_Y + CELLSIZE / 2) / CELLSIZE;
    int cellIndex4 = (pos.x - MAZE_MARGIN_X + CELLSIZE / 2) / CELLSIZE;

    if (maze[cellIndex1][cellIndex2] == 0 &&
        maze[cellIndex3][cellIndex4] == 0 &&
        maze[cellIndex1][cellIndex4] == 0 &&
        maze[cellIndex3][cellIndex2] == 0)
        return 1;
    else
        return 0;
}

// int canGoTo(Vector2 pos)
// {
//     float directions[9][2] = {
//         {0, 0},
//         {0, 1},
//         {0, -1},
//         {1, 0},
//         {1, 1},
//         {1, -1},
//         {-1, 0},
//         {-1, 1},
//         {-1, -1},
//     };

//     float cellPosX = MAZE_MARGIN_X + ((pos.x - MAZE_MARGIN_X) / CELLSIZE) * CELLSIZE;
//     float cellPosY = MAZE_MARGIN_Y + ((pos.y - MAZE_MARGIN_Y) / CELLSIZE) * CELLSIZE;

//     int isAllowed = 1;
//     for (int i = 0; i < 9; i++)
//     {

//         Vector2 targetCellPos = {cellPosX + directions[i][0] * CELLSIZE, cellPosY + directions[i][1] * CELLSIZE};
//     }
// }

int main()
{
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Demo Game");
    SetTargetFPS(60);

    // calculate inital position of the ball
    float init_pos_x = MAZE_MARGIN_X + CELLSIZE * (3.0 / 2);
    float init_pos_y = MAZE_MARGIN_Y + CELLSIZE * (3.0 / 2);

    Vector2 ballPos0 = {init_pos_x, init_pos_y};
    Vector2 ballPos = ballPos0;
    float ballRadius = CELLSIZE / 2;

    srand(time(NULL));
    initializeMaze();
    generateMaze(1, 1);

    // Game Loop
    while (!WindowShouldClose())
    {
        // Logic Part

        // movement logic with willGoRight, willGoLeft etc
        // if (IsKeyDown(KEY_RIGHT) && willGoRight(ballPos))
        //     ballPos.x += 2;
        // if (IsKeyDown(KEY_LEFT) && willGoLeft(ballPos))
        //     ballPos.x -= 2;
        // if (IsKeyDown(KEY_UP) && willGoUp(ballPos))
        //     ballPos.y -= 2;
        // if (IsKeyDown(KEY_DOWN) && willGoDown(ballPos))
        //     ballPos.y += 2;

        // movement logic with isPositionFree
        Vector2 ballPosNew = ballPos;
        if (IsKeyDown(KEY_RIGHT))
            ballPosNew.x += 2;
        if (IsKeyDown(KEY_LEFT))
            ballPosNew.x -= 2;
        if (IsKeyDown(KEY_UP))
            ballPosNew.y -= 2;
        if (IsKeyDown(KEY_DOWN))
            ballPosNew.y += 2;

        if (isPostionFree(ballPosNew))
            ballPos = ballPosNew;

        // Generate New Maze
        if (IsKeyPressed(KEY_SPACE))
        {
            initializeMaze();
            generateMaze(1, 1);
            ballPos = ballPos0;
        }
        //framescount increasing to determine time
        framescount++;

        // Drawing Part
        BeginDrawing();
        ClearBackground(RAYWHITE);

        drawMaze((Vector2){MAZE_MARGIN_X, MAZE_MARGIN_Y}, CELLSIZE);

        DrawCircleV(ballPos, ballRadius, RED);
        DrawCircleLinesV(ballPos, ballRadius, BLACK);

        //Time sector
        DrawText(TextFormat("Time : %2d:%3.1f    Remaining : %2d:%3.1f", framescount/3600,(framescount%3600)/60.0, (net_time*60- framescount)/3600,((net_time*60- framescount)%3600)/60.0), 5, 5, 15, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}