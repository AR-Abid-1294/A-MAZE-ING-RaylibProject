#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "raylib.h"
#include "raymath.h"
#include "player.h"

#define LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))

#define SCREENWIDTH 1400
#define SCREENHEIGHT 800

#define MAZEWIDTH 35
#define MAZEHEIGHT 25
#define CELLSIZE 25
#define WALL_THICK 3
#define MAX_LEVEL 50

#define MAZE_MARGIN_X (SCREENWIDTH - MAZEWIDTH * CELLSIZE) / 2
#define MAZE_MARGIN_Y (SCREENHEIGHT - MAZEHEIGHT * CELLSIZE) / 2 + CELLSIZE

#define SPEED_MAX 120.0f

extern int directions[4][2];

#define MIN(a, b) (a < b ? a : b)

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
    CROSSED,
    // during auto solving
    UNCHECKED,
    CHECKED
} CellState;

typedef enum Difficulty
{
    EASY,
    MEDIUM,
    HARD
} Difficulty;

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

typedef struct Frontier
{
    Cell *visisted_cell;
    Cell *univisited_cell;
} Frontier;

typedef struct Maze
{
    int height;
    int width;
    int cell_size;
    float wall_thickness;

    Cell **cells;
    int visited_count;

    Cell *current_cell; // for Recursive Backtracker

    // for Randomized Prim's
    Frontier *frontiers;
    int frontier_count;

    Texture2D cell_texture;
    Texture2D crossed_cell_texture;

    // Maze width, height and cell size
    // for different levels of MULTIVERSE mode
    int levels[50][3];

    Difficulty difficulty;
} Maze;

void shuffleDirections();

void initializeMaze(Maze *maze, int level);

bool isCellValid(Maze maze, int x, int y);

bool isWall(Maze maze, Cell cell1, Cell cell2);

void breakWall(Maze *maze, Cell *cell1, Cell *cell2);

void addFrontier(Maze *maze, Cell *cell);

void removeFrontier(Maze *maze, int frontier_index);

// Different Maze Generation Algorithms

void generateMaze_backtracker(Maze *maze);

void chooseRandFrontier(Maze *maze);

void generateMaze_prim(Maze *maze);

void generateMaze_aldous_broder(Maze *maze);

void (*generateMaze)(Maze *maze);

void drawMaze(Maze *maze, Vector2 pos, Player *player);

void destroyMaze(Maze *maze);

// Maze Solving Algorithms

void markAll(Maze *maze, CellState state);

void findPath(Maze *maze, Cell *cell);

void solveMaze(Maze *maze);

#endif