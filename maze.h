#ifndef MAZE_H
#define MAZE_H

#include "raylib.h"
#include "raymath.h"

#define LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))

#define SCREENWIDTH 800
#define SCREENHEIGHT 600

#define MAZEWIDTH 51
#define MAZEHEIGHT 35
#define CELLSIZE 15
extern int maze[MAZEHEIGHT][MAZEWIDTH];

#define MAZE_MARGIN_X 15
#define MAZE_MARGIN_Y 15

#define SPEED_MAX 120.0f

// for time sector
extern int frames_count;
extern int net_time;

void initializeMaze();

// Check if a cell is inside the maze
int isCellValid(int x, int y);

void shuffleDirections(int directions[4][2]);

void generateMaze(int x, int y);

void drawMaze(Vector2 pos, float block_side_len, Texture2D block);

int isPostionFree(Vector2 pos);

#endif