#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "raylib.h"

#define SCREENWIDTH 800
#define SCREENHEIGHT 600

#define MAZEWIDTH 51
#define MAZEHEIGHT 37
int maze[MAZEHEIGHT][MAZEWIDTH];

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

// void printMaze()
// {
//     for (int y = 0; y < MAZEHEIGHT; y++)
//     {
//         for (int x = 0; x < MAZEWIDTH; x++)
//         {
//             if (maze[y][x] == 1)
//                 printf("# ");
//             else if (maze[y][x] == 0)
//                 printf("  ");
//         }
//         printf("\n");
//     }
// }

void generateMaze(int x, int y)
{
    maze[y][x] = 0;

    int directions[4][2] = {{0, 2}, {0, -2}, {2, 0}, {-2, 0}};
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
                if (false)
                {
                    /* code */
                }
                
                Rectangle block = {pos.x, pos.y, block_side_len, block_side_len};
                DrawRectangleRec(block, DARKGREEN);
            }
            else if(y == MAZEHEIGHT - 2 && x == MAZEWIDTH - 2){
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

int main()
{
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Demo Game");
    SetTargetFPS(60);

    Vector2 ballPos0 = {37.5, 37.5};
    Vector2 ballPos = ballPos0;
    int ballRadius = 6;

    srand(time(NULL));
    initializeMaze();
    generateMaze(1, 1);

    // Game Loop
    while (!WindowShouldClose())
    {
        // Logic Part
        if (IsKeyDown(KEY_RIGHT) && ballPos.x < SCREENWIDTH - ballRadius)
            ballPos.x += 2;
        if (IsKeyDown(KEY_LEFT) && ballPos.x > ballRadius)
            ballPos.x -= 2;
        if (IsKeyDown(KEY_UP) && ballPos.y > ballRadius)
            ballPos.y -= 2;
        if (IsKeyDown(KEY_DOWN) && ballPos.y < SCREENHEIGHT - ballRadius)
            ballPos.y += 2;

        // Generate New Maze
        if (IsKeyPressed(KEY_SPACE))
        {
            initializeMaze();
            generateMaze(1, 1);
            ballPos = ballPos0;
        }

        // Drawing Part
        BeginDrawing();
        ClearBackground(RAYWHITE);

        drawMaze((Vector2){15, 15}, 15);

        DrawCircleV(ballPos, ballRadius, RED);
        DrawCircleLinesV(ballPos, ballRadius, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}