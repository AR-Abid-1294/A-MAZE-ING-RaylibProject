#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "raylib.h"
#include "raymath.h"
#include "game.h"

// set up initial game state, load assets
void initGameState(GameState *gs)
{
    gs->page = MENU;
    gs->shouldQuit = false;

    // Load Sprites and Textures
    gs->wall_texture = LoadTexture("Assets/brick2.png");
    gs->maze.cell_texture = LoadTexture("Assets/plaster1.png");
    gs->player.player_texture = LoadTexture("Assets/stone1.png");

    // calculate inital position of the ball
    float init_pos_x = MAZE_MARGIN_X + CELLSIZE * (3.0 / 2);
    float init_pos_y = MAZE_MARGIN_Y + CELLSIZE * (3.0 / 2);

    gs->ball_pos0 = (Vector2){init_pos_x, init_pos_y};
    gs->ball_pos = gs->ball_pos0;
    gs->ball_radius = CELLSIZE / 2;
    gs->sprite_side = CELLSIZE;
    gs->ball_speed = Vector2Zero();

    gs->player.x = 0;
    gs->player.y = 0;

    srand(time(NULL));
    initializeMaze();
    generateMaze(1, 1);

    initializeMaze2(&gs->maze, MAZEHEIGHT, MAZEWIDTH);
    generateMaze2(&gs->maze, &gs->maze.cells[0][0]);
}

// unload textures
void unloadGameState(GameState *gs)
{
    UnloadTexture(gs->wall_texture);
    UnloadTexture(gs->maze.cell_texture);
    UnloadTexture(gs->player.player_texture);
    destroyMaze2(&gs->maze);
}

// update game logic
void updateGameplay(GameState *gs)
{

    // Logic Part

    // Delta Time
    float dt = GetFrameTime();

    // movement logic with isPositionFree
    Vector2 ball_posNew = gs->ball_pos;
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
        gs->ball_speed.x = SPEED_MAX;
    else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
        gs->ball_speed.x = -SPEED_MAX;
    else if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
        gs->ball_speed.y = -SPEED_MAX;
    else if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
        gs->ball_speed.y = SPEED_MAX;
    else
        gs->ball_speed = Vector2Zero();

    ball_posNew = Vector2Add(ball_posNew, Vector2Scale(gs->ball_speed, dt));

    if (isPostionFree(ball_posNew))
        gs->ball_pos = ball_posNew;

    // Generate New Maze
    if (IsKeyPressed(KEY_SPACE))
    {
        initializeMaze();
        generateMaze(1, 1);
        gs->ball_pos = gs->ball_pos0;
    }

    // frames_count increasing to determine time
    frames_count++;
}

// draw main game
void drawGame(GameState *gs)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    drawMaze((Vector2){MAZE_MARGIN_X, MAZE_MARGIN_Y}, CELLSIZE, gs->wall_texture);

    DrawCircleV(gs->ball_pos, gs->ball_radius, RED);
    DrawCircleLinesV(gs->ball_pos, gs->ball_radius, BLACK);

    // Time sector
    DrawText(TextFormat("Time : %2d:%3.1f    Remaining : %2d:%3.1f",
                        frames_count / 3600, (frames_count % 3600) / 60.0,
                        (net_time * 60 - frames_count) / 3600,
                        ((net_time * 60 - frames_count) % 3600) / 60.0),
             5, 5, 15, BLACK);

    Button menu_btn = {(Rectangle){10, SCREENHEIGHT - 30 - 10, 70, 30}, DARKGRAY,
                       0, WHITE,
                       "MENU", RAYWHITE, 20};
    drawButton(menu_btn);
    if (hovered(menu_btn))
    {
        menu_btn.buttonColor = GRAY;
        drawButtonShadow(menu_btn);
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    }
    else
    {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    if (clicked(menu_btn))
        gs->page = 0;

    EndDrawing();
}

// draw and update different pages

void updateMenu(GameState *gs)
{
    BeginDrawing();
    ClearBackground(GetColor(0xf0f2f5ff));

    // PLAY BUTTON
    Button play_btn = {(Rectangle){SCREENWIDTH * (2.0 / 5), SCREENHEIGHT / 5, SCREENWIDTH / 5, 35},
                       BLUE,
                       0, WHITE, "PLAY", RAYWHITE, 25};
    drawButton(play_btn);
    if (hovered(play_btn))
    {
        play_btn.buttonColor = GetColor(0x7a35ffff);
        drawButtonShadow(play_btn);
    }
    if (clicked(play_btn))
        gs->page = PLAYING;

    // CREDIT BUTTON
    Button credit_btn = {(Rectangle){SCREENWIDTH * (2.0 / 5), SCREENHEIGHT / 5 + 50, SCREENWIDTH / 5, 35},
                         BLUE,
                         0, WHITE, "CREDIT", RAYWHITE, 25};
    drawButton(credit_btn);
    if (hovered(credit_btn))
    {
        credit_btn.buttonColor = GetColor(0x7a35ffff);
        drawButtonShadow(credit_btn);
    }
    if (clicked(credit_btn))
        gs->page = CREDIT;

    // QUIT BUTTON
    Button quit_btn = {(Rectangle){SCREENWIDTH * (2.0 / 5), SCREENHEIGHT / 5 + 50 * 2, SCREENWIDTH / 5, 35},
                       BLUE,
                       0, WHITE, "QUIT", RAYWHITE, 25};
    drawButton(quit_btn);
    if (hovered(quit_btn))
    {
        quit_btn.buttonColor = GetColor(0x7a35ffff);
        drawButtonShadow(quit_btn);
    }
    if (clicked(quit_btn))
        gs->shouldQuit = true;

    // change mouse cursor
    if (hovered(play_btn) || hovered(credit_btn) || hovered(quit_btn))
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    else
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);

    EndDrawing();
}

void updateCredit(GameState *gs)
{
    BeginDrawing();
    ClearBackground(GetColor(0xffefb3ff));
    SetMouseCursor(MOUSE_CURSOR_DEFAULT);

    // Afif Part
    char afif_credit[1000] = "S.M. Afif Iqbal\n2505004";
    Card afif_card = {(Rectangle){SCREENWIDTH * (1.0 / 10), SCREENHEIGHT / 5, SCREENWIDTH * (3.0 / 10), 100},
                      GetColor(0x013e37ff),
                      0, WHITE, "S.M. Afif Iqbal\n2505004", RAYWHITE, 25};
    drawCard(afif_card);
    drawCardShadow(afif_card);

    // Abid Part
    char abid_credit[1000] = "Md Abidur Rahman\n2505019";
    Card abid_card = {(Rectangle){SCREENWIDTH * (6.0 / 10), SCREENHEIGHT / 5, SCREENWIDTH * (3.0 / 10), 100},
                      GetColor(0x013e37ff),
                      0, WHITE, "Md Abidur Rahman\n2505019", RAYWHITE, 25};
    drawCard(abid_card);
    drawCardShadow(abid_card);

    // MENU BUTTON
    Button menu_btn = {(Rectangle){10, SCREENHEIGHT - 30 - 10, 70, 30}, DARKGRAY,
                       0, WHITE,
                       "MENU", RAYWHITE, 20};
    drawButton(menu_btn);
    if (hovered(menu_btn))
    {
        menu_btn.buttonColor = GRAY;
        drawButtonShadow(menu_btn);
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    }
    else
    {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
    if (clicked(menu_btn))
        gs->page = MENU;

    EndDrawing();
}

bool isCellAllowed(Cell cell1, Cell cell2)
{
    if (cell1.x == cell2.x)
    {
        if (cell1.y - cell2.y == 1)
        {
            return !(cell1.up_wall && cell2.down_wall);
        }
        else if (cell2.y - cell1.y == 1)
        {
            return !(cell2.up_wall && cell1.down_wall);
        }
    }
    else if (cell1.y == cell2.y)
    {
        if (cell1.x - cell2.x == 1)
        {
            return !(cell1.left_wall && cell2.right_wall);
        }
        else if (cell2.x - cell1.x == 1)
        {
            return !(cell2.left_wall && cell1.right_wall);
        }
    }
    return true;
}

void updateGameplay2(GameState *gs)
{

    // Logic Part

    // Delta Time
    float dt = GetFrameTime();

    // movement
    int x = gs->player.x;
    int y = gs->player.y;
    Cell cell_old = gs->maze.cells[y][x];

    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
    {
        y--;
    }
    else if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
    {
        y++;
    }
    else if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))
    {
        x++;
    }
    else if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))
    {
        x--;
    }

    if (isCellValid2(x, y, gs->maze))
    {
        Cell cell_new = gs->maze.cells[y][x];
        if (isCellAllowed(cell_old, cell_new))
        {
            gs->player.x = x;
            gs->player.y = y;
        }
    }

    // Generate New Maze
    if (IsKeyPressed(KEY_SPACE))
    {
        destroyMaze2(&gs->maze);
        initializeMaze2(&gs->maze, MAZEHEIGHT, MAZEWIDTH);
        generateMaze2(&gs->maze, &gs->maze.cells[0][0]);
        gs->player.x = 0;
        gs->player.y = 0;
    }

    // frames_count increasing to determine time
    frames_count++;
}

void drawGame2(GameState *gs)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    drawMaze2(&gs->maze, (Vector2){MAZE_MARGIN_X, MAZE_MARGIN_Y}, CELLSIZE, gs->player);

    // Time sector
    DrawText(TextFormat("Time : %2d:%3.1f    Remaining : %2d:%3.1f",
                        frames_count / 3600, (frames_count % 3600) / 60.0,
                        (net_time * 60 - frames_count) / 3600,
                        ((net_time * 60 - frames_count) % 3600) / 60.0),
             5, 5, 15, BLACK);

    Button menu_btn = {(Rectangle){10, SCREENHEIGHT - 30 - 10, 70, 30}, DARKGRAY,
                       0, WHITE,
                       "MENU", RAYWHITE, 20};
    drawButton(menu_btn);
    if (hovered(menu_btn))
    {
        menu_btn.buttonColor = GRAY;
        drawButtonShadow(menu_btn);
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    }
    else
    {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    if (clicked(menu_btn))
        gs->page = 0;

    EndDrawing();
}

void updateGame(GameState *gs)
{
    switch (gs->page)
    {
    case MENU:
        updateMenu(gs);
        break;

    case PLAYING:
        updateGameplay2(gs);
        drawGame2(gs);
        break;

    case CREDIT:
        updateCredit(gs);
        break;

    default:
        break;
    }
}