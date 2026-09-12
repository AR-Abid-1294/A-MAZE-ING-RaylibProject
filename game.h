#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "prim.h"
#include "ui.h"
#include "scores.h"

typedef enum PageState
{
    MENU,
    NAME_INPUT,
    PLAYING,
    LEVELS,
    GAME_FINISH,
    GAME_OVER,
    MULTIVERSE_CONQUERED,
    CREDIT,
    SETTINGS,
    HIGH_SCORES,
    BEST_TIMES
} PageState;

typedef enum GameMode
{
    BEST,
    MULTIVERSE,
    DARK_NIGHT,
    INFINITY_WAR
} GameMode;

typedef struct GameState
{
    PageState page;
    bool shouldQuit;
    double start_time;

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
    Font font3;
    Font font4;
    Font font5;
    Font font6;
    Font font7;
    Font title_font;
    Font btn_font;
    Font msg_font;

    // sound effects
    Sound click_sound1;
    Sound movement_sound;
    Sound movement_blocked_sound;
    Sound game_finish_sound;

    // music
    Music bg_music;
    bool music_on;

    // images
    Texture2D abid_pic;
    Texture2D afif_pic;

    // best times for THE BEST OF US mode
    float last_time;
    Score best_times[10];
    FILE *best_times_file;

    // high scores for THE MULTIVERSE OF MADMAZE
    Score high_scores[10];
    FILE *high_scores_file;

    // mode
    GameMode mode;

    // level
    int level;
} GameState;

// set up initial game state, load assets
void initGameState(GameState *gs);

// unload textures
void unloadGameState(GameState *gs);

// update game logic
void updateGame(GameState *gs);
void drawMenu(GameState *gs);
void updateNameInput(GameState *gs);
void drawNameInput(GameState *gs);
void drawCredit(GameState *gs);

void initGameplay(GameState *gs);
void updateGameplay(GameState *gs);
void drawGame(GameState *gs);

void drawScore(GameState *gs);

#endif