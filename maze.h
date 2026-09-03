#ifndef MAZE_H
#define MAZE_H

#include "raylib.h"
#include "raymath.h"
#include "player.h"

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

void initializeMaze();

// Check if a cell is inside the maze
int isCellValid(int x, int y);

void shuffleDirections(int directions[4][2]);

void generateMaze(int x, int y);

void drawMaze(Vector2 pos, float block_side_len, Texture2D block);

int isPostionFree(Vector2 pos);

// new (2) approach
void initializeMaze2(Maze *maze, int height, int width);

bool isCellValid2(int x, int y, Maze maze);

void breakWall(Maze *maze, Cell *cell1, Cell *cell2);

void generateMaze2(Maze *maze, Cell *cell);

void drawMaze2(Maze *maze, Vector2 pos, float tile_side_len, Player player);

void destroyMaze2(Maze *maze);

#endif