#ifndef MAZE_H
#define MAZE_H

#include "raylib.h"
#include "raymath.h"
#include "player.h"

#define LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))

#define SCREENWIDTH 1400
#define SCREENHEIGHT 800

#define MAZEWIDTH 41
#define MAZEHEIGHT 25
#define CELLSIZE 25
#define WALL_THICK 3

#define MAZE_MARGIN_X (SCREENWIDTH - MAZEWIDTH * CELLSIZE) / 2
#define MAZE_MARGIN_Y (SCREENHEIGHT - MAZEHEIGHT * CELLSIZE) / 2

#define SPEED_MAX 120.0f

// for time sector
extern int frames_count;
extern int net_time;

typedef enum Direction
{
    UP,
    DOWN,
    RIGHT,
    LEFT
} Direction;

typedef enum CellState
{
    // during maze generation
    UNVISITED,
    VISITED,
    // during maze solving
    UNCROSSED,
    CROSSED
} CellState;

typedef struct Cell
{
    CellState cellState;
    int x;
    int y;

    bool up_wall;
    bool down_wall;
    bool right_wall;
    bool left_wall;
} Cell;

typedef struct Maze
{
    int height;
    int width;

    Cell **cells;

    Texture2D cell_texture;
} Maze;

// Check if a cell is inside the maze
void shuffleDirections(int directions[4][2]);

int isPostionFree(Vector2 pos);

void initializeMaze(Maze *maze, int height, int width);

bool isCellValid(int x, int y, Maze maze);

void breakWall(Maze *maze, Cell *cell1, Cell *cell2);

void generateMaze(Maze *maze, Cell *cell);

void drawMaze(Maze *maze, Vector2 pos, float tile_side_len, Player player);

void destroyMaze(Maze *maze);

#endif