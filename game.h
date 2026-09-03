#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "maze.h"
#include "ui.h"
#include "player.h"

typedef enum PageState
{
    MENU = 0,
    PLAYING = 1,
    CREDIT = 19,
    SETTINgs = 20,
    HIGH_SCORES = 21
} PageState;

typedef struct GameState
{
    PageState page;
    bool shouldQuit;

    Maze maze;

    // player
    Player player;

    // ball
    Vector2 ball_pos0;
    Vector2 ball_pos;
    float ball_radius;
    float sprite_side;
    Vector2 ball_speed;

    // assets
    Texture2D wall_texture;
    Texture2D player_sprite;

    // fonts
    Font font1;
    Font font2;

    // sound effects
    Sound hover_sound;
    Sound click_sound;
    Sound movement_sound;
    Sound movement_blocked_sound;
} GameState;

// set up initial game state, load assets
void initGameState(GameState *gs);

// unload textures
void unloadGameState(GameState *gs);

// update game logic
void updateGame(GameState *gs);
void updateGameplay(GameState *gs);
void drawGame(GameState *gs);
void updateMenu(GameState *gs);
void updateCredit(GameState *gs);

void updateGameplay(GameState *gs);
void drawGame(GameState *gs);

#endif