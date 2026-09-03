#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

typedef struct Player
{
    int x;
    int y;
    Texture2D player_texture;
} Player;

#endif