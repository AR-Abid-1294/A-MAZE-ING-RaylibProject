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
    gs->maze.cell_texture = LoadTexture("Assets/Textures/plaster1.png");
    gs->player.player_texture = LoadTexture("Assets/Textures/stone1.png");

    // Load Fonts
    gs->font1 = LoadFont("Assets/Fonts/Font3.otf");
    gs->font2 = LoadFont("Assets/Fonts/Font2.TTF");

    // Load Sound Effects
    gs->hover_sound = LoadSound("Assets/Sound Effects/pop_1.wav");
    gs->click_sound = LoadSound("Assets/Sound Effects/click_double_on.wav");
    gs->movement_sound = LoadSound("Assets/Sound Effects/water_drop_synthetic.wav");
    gs->movement_blocked_sound = LoadSound("Assets/Sound Effects/cardboard_hit.wav");

    // calculate inital position of the ball
    float init_pos_x = MAZE_MARGIN_X + CELLSIZE * (3.0 / 2);
    float init_pos_y = MAZE_MARGIN_Y + CELLSIZE * (3.0 / 2);

    gs->player.x = 0;
    gs->player.y = 0;

    srand(time(NULL));
    initializeMaze(&gs->maze, MAZEHEIGHT, MAZEWIDTH);
    generateMaze(&gs->maze, &gs->maze.cells[0][0]);
}

// unload textures
void unloadGameState(GameState *gs)
{
    UnloadTexture(gs->maze.cell_texture);
    UnloadTexture(gs->player.player_texture);
    destroyMaze(&gs->maze);
}

// draw and update different pages

void updateMenu(GameState *gs)
{
    BeginDrawing();
    ClearBackground(GetColor(0x0b132b));

    // PLAY BUTTON
    Button play_btn = {(Rectangle){SCREENWIDTH * (2.0 / 5), SCREENHEIGHT / 5, SCREENWIDTH / 5, 35},
                       DARKBLUE,
                       0, WHITE, "PLAY", RAYWHITE, 25};
    drawButton(play_btn, gs->font1);
    if (hovered(play_btn))
    {
        play_btn.buttonColor = BLUE;
        drawButton(play_btn, gs->font1);
    }
    if (clicked(play_btn))
    {
        PlaySound(gs->click_sound);
        gs->page = PLAYING;
    }

    // CREDIT BUTTON
    Button credit_btn = {(Rectangle){SCREENWIDTH * (2.0 / 5), SCREENHEIGHT / 5 + 50, SCREENWIDTH / 5, 35},
                         DARKBLUE,
                         0, WHITE, "CREDIT", RAYWHITE, 25};
    drawButton(credit_btn, gs->font1);
    if (hovered(credit_btn))
    {
        credit_btn.buttonColor = BLUE;
        drawButton(credit_btn, gs->font1);
    }
    if (clicked(credit_btn))
    {
        PlaySound(gs->click_sound);
        gs->page = CREDIT;
    }

    // QUIT BUTTON
    Button quit_btn = {(Rectangle){SCREENWIDTH * (2.0 / 5), SCREENHEIGHT / 5 + 50 * 2, SCREENWIDTH / 5, 35},
                       DARKBLUE,
                       0, WHITE, "QUIT", RAYWHITE, 25};
    drawButton(quit_btn, gs->font1);
    if (hovered(quit_btn))
    {
        quit_btn.buttonColor = BLUE;
        drawButton(quit_btn, gs->font1);
    }
    if (clicked(quit_btn))
    {
        PlaySound(gs->click_sound);
        gs->shouldQuit = true;
    }

    // change mouse cursor
    if (hovered(play_btn) || hovered(credit_btn) || hovered(quit_btn))
    {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        // PlaySound(gs->hover_sound);
    }
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
    drawButton(menu_btn, gs->font1);
    if (hovered(menu_btn))
    {
        menu_btn.buttonColor = GRAY;
        // drawButtonShadow(menu_btn, gs->font1);
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    }
    else
    {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
    if (clicked(menu_btn))
    {
        PlaySound(gs->click_sound);
        gs->page = MENU;
    }

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

void updateGameplay(GameState *gs)
{

    // Logic Part

    // Delta Time
    float dt = GetFrameTime();

    // movement
    int x = gs->player.x;
    int y = gs->player.y;
    Cell cell_old = gs->maze.cells[y][x];

    bool movement_attempt;

    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
    {
        y--;
        movement_attempt = true;
    }
    else if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
    {
        y++;
        movement_attempt = true;
    }
    else if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))
    {
        x++;
        movement_attempt = true;
    }
    else if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))
    {
        x--;
        movement_attempt = true;
    }

    if (movement_attempt)
    {
        if (isCellValid(x, y, gs->maze))
        {
            Cell cell_new = gs->maze.cells[y][x];
            if (isCellAllowed(cell_old, cell_new))
            {
                gs->player.x = x;
                gs->player.y = y;
                PlaySound(gs->movement_sound);
            }
            else
            {
                PlaySound(gs->movement_blocked_sound);
            }
        }
        else
        {
            PlaySound(gs->movement_blocked_sound);
        }
    }

    // Generate New Maze
    if (IsKeyPressed(KEY_SPACE))
    {
        destroyMaze(&gs->maze);
        initializeMaze(&gs->maze, MAZEHEIGHT, MAZEWIDTH);
        generateMaze(&gs->maze, &gs->maze.cells[0][0]);
        gs->player.x = 0;
        gs->player.y = 0;
    }

    // frames_count increasing to determine time
    frames_count++;
}

void drawGame(GameState *gs)
{
    BeginDrawing();
    ClearBackground(GetColor(0x0b132b));

    drawMaze(&gs->maze, (Vector2){MAZE_MARGIN_X, MAZE_MARGIN_Y}, CELLSIZE, gs->player);

    // Time sector
    DrawText(TextFormat("Time : %2d:%3.1f    Remaining : %2d:%3.1f",
                        frames_count / 3600, (frames_count % 3600) / 60.0,
                        (net_time * 60 - frames_count) / 3600,
                        ((net_time * 60 - frames_count) % 3600) / 60.0),
             5, 5, 15, BLACK);

    Button menu_btn = {(Rectangle){10, SCREENHEIGHT - 30 - 10, 70, 30}, DARKGRAY,
                       0, WHITE,
                       "MENU", RAYWHITE, 20};
    drawButton(menu_btn, gs->font1);
    if (hovered(menu_btn))
    {
        menu_btn.buttonColor = GRAY;
        // drawButtonShadow(menu_btn, gs->font1);
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    }
    else
    {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    if (clicked(menu_btn))
    {
        PlaySound(gs->click_sound);
        gs->page = 0;
    }

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
        updateGameplay(gs);
        drawGame(gs);
        break;

    case CREDIT:
        updateCredit(gs);
        break;

    default:
        break;
    }
}