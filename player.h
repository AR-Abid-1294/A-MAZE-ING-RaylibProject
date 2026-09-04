#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

typedef struct Player
{
    int x;
    int y;
    Texture2D player_texture;

    bool flip;

    Texture2D player_sprite_idle[12];
    Texture2D player_sprite_attacking[12];
    Texture2D player_sprite_dying[12];
    int sprite_index;
} Player;


#endif