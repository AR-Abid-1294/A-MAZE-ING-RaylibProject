#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "maze.h"
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
    INFO,
    SETTINGS,
    HIGH_SCORES,
    BEST_TIMES
} PageState;

typedef enum GameMode
{
    BEST_OF_US,
    MULTIVERSE,
    DARK_NIGHT,
    TIME_RUNS_OUT,
    INFINITY_WAR,
    GRAVITY_GRAVE,
    ENDGAME
} GameMode;

typedef enum Info
{
    HOWTOPLAY,
    BACKTRACKER,
    PRIM,
    ALDOUSBRODER,
    BESTOFUS,
    MULTIVERSEOFMADMAZE,
    DARKNIGHT,
    TIMERUNSOUT,
    INFINITYWAR
} Info;

typedef enum Algorithm
{
    BACKTRACKER_ALGO,
    PRIM_ALGO,
    ALDOUS_BRODER_ALGO
} Algorithm;

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
    double ball_radius;
    double sprite_side;
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
    Sound click_sound;
    Sound movement_sound;
    Sound movement_blocked_sound;
    Sound game_finish_sound;

    // music
    Music bg_music;
    bool music_on;

    // images
    Texture2D abid_pic;
    Texture2D afif_pic;

    // buttons

    Texture2D music_on_btn;
    Texture2D music_hovered_btn;
    Texture2D music_off_btn;

    Texture2D info_btn;
    Texture2D info_hovered_btn;

    Texture2D settings_btn;
    Texture2D settings_hovered_btn;

    Texture2D menu_btn;
    Texture2D menu_hovered_btn;

    Texture2D nuke_btn;
    Texture2D nuke_hovered_btn;

    Texture2D square_btn;
    Texture2D square_not_btn;

    // mode selection buttons
    Texture2D best_of_us_btn;
    Texture2D multiverse_btn;
    Texture2D dark_night_btn;
    Texture2D infinity_war_btn;
    Texture2D time_runs_out_btn;
    Texture2D gravity_grave_btn;
    Texture2D endgame_btn;

    // info selection
    Info info;
    // settings selection
    Algorithm algorithm;

    // name_input
    char name[20];
    int letter_count;

    // best times for THE BEST OF US mode
    Time best_times_easy[11];
    Time best_times_medium[11];
    Time best_times_hard[11];

    // best times for THE DARK NIGHT
    Time dark_times_easy[11];
    Time dark_times_medium[11];
    Time dark_times_hard[11];

    bool square_on;

    // high scores for THE MULTIVERSE OF MADMAZE
    Score high_scores[11];

    // high scores for TIME RUNS OUT
    Score out_scores_easy[11];
    Score out_scores_medium[11];
    Score out_scores_hard[11];

    // genral pointers
    double current_time;
    double last_time;
    Time *times;

    int last_score;
    Score *scores;

    // mode
    GameMode mode;

    // level for MULTIVERSE OF MADMAZE
    int level;

    // round for INFINTIY WAR
    int round;
    double time_limit;
} GameState;

// set up initial game state, load assets
void initGameState(GameState *gs);

// unload textures
void unloadGameState(GameState *gs);

// update game logic
void updateGame(GameState *gs);
void updateSettings(GameState *gs);
void drawMenu(GameState *gs);
void updateNameInput(GameState *gs);
void drawNameInput(GameState *gs);
void drawCredit(GameState *gs);

void initGameplay(GameState *gs);
void updateGameplay(GameState *gs);
void drawGame(GameState *gs);

void addTime(GameState *gs);
void addScore(GameState *gs);
void drawTime(GameState *gs);
void drawScore(GameState *gs);

void drawDark(GameState *gs);

#endif