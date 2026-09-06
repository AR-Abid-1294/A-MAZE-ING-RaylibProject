#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "maze.h"
#include "player.h"

int maze[MAZEHEIGHT][MAZEWIDTH];
int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

// for time sector
int frames_count = 0;
int net_time = 100; // seconds

void shuffleDirections()
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

    // initialize frontiers
    int max_frontier = (maze->height) * (maze->width) * 4;
    maze->frontiers = malloc(max_frontier * sizeof(Frontier));

    maze->cells[0][0].cellState = VISITED;
    maze->frontiers[0] = (Frontier){&maze->cells[0][0], &maze->cells[0][1]};
    maze->frontiers[1] = (Frontier){&maze->cells[0][0], &maze->cells[1][0]};
    maze->frontier_count = 2;
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

    shuffleDirections();

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

void addFrontier(Maze *maze, Cell *cell)
{
    for (int i = 0; i < 4; i++)
    {
        int x = cell->x + directions[i][0];
        int y = cell->y + directions[i][1];
        if (isCellValid(x, y, *maze))
        {
            Cell *neighbor_cell = &maze->cells[y][x];
            if (neighbor_cell->cellState == UNVISITED)
            {
                maze->frontiers[maze->frontier_count] = (Frontier){cell, neighbor_cell};
                maze->frontier_count++;
            }
        }
    }
}

void removeFrontier(Maze *maze, int frontier_index)
{
    for (int i = frontier_index; i < maze->frontier_count; i++)
    {
        maze->frontiers[i] = maze->frontiers[i + 1];
    }
}

void chooseRandFrontier(Maze *maze)
{
    int r = rand() % maze->frontier_count;
    Cell *target_cell = maze->frontiers[r].univisited_cell;
    if (target_cell->cellState == VISITED)
    {
        maze->frontier_count--;
        removeFrontier(maze, r);
    }
    else
    {
        target_cell->cellState = VISITED;
        breakWall(maze, maze->frontiers[r].visisted_cell, maze->frontiers[r].univisited_cell);
        maze->frontier_count--;
        removeFrontier(maze, r);
        addFrontier(maze, target_cell);
    }
}

void generateMaze2(Maze *maze)
{
    while (maze->frontier_count)
    {
        chooseRandFrontier(maze);
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

void drawMaze(Maze *maze, Vector2 pos, float tile_side_len, Player *player)
{
    Texture2D tile = maze->cell_texture;
    // Texture2D sprite = player->player_sprite_idle[player->sprite_index];
    for (int y = 0; y < maze->height; y++)
    {
        float startx = pos.x;
        for (int x = 0; x < maze->width; x++)
        {
            if (x == player->x && y == player->y)
            {
                tile = player->player_texture;
            }
            else
            {
                tile = maze->cell_texture;
            }

            Rectangle cell_rec = (Rectangle){pos.x, pos.y, tile_side_len, tile_side_len};

            DrawTexturePro(tile,
                           (Rectangle){0, 0, tile.width, tile.height},
                           cell_rec, Vector2Zero(), 0, WHITE);

            drawBorder(cell_rec, UP, maze->cells[y][x].up_wall ? WALL_THICK : 0, WHITE);
            drawBorder(cell_rec, DOWN, maze->cells[y][x].down_wall ? WALL_THICK : 0, WHITE);
            drawBorder(cell_rec, RIGHT, maze->cells[y][x].right_wall ? WALL_THICK : 0, WHITE);
            drawBorder(cell_rec, LEFT, maze->cells[y][x].left_wall ? WALL_THICK : 0, WHITE);

            // if (x == player->x && y == player->y)
            // {
            //     DrawTexturePro(sprite,
            //                    (Rectangle){0, 0, player->flip ? -sprite.width : sprite.width,
            //                                sprite.height},
            //                    cell_rec, Vector2Zero(), 0, WHITE);
            // }

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
    free(maze->frontiers);
}