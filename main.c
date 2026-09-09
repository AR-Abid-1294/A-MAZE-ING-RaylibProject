#include <stdlib.h>
#include <time.h>

#include "maze.h"
#include "ui.h"
#include "game.h"

int main()
{
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Demo Game");
    InitAudioDevice();
    SetTargetFPS(60);

    srand(time(NULL));

    GameState gs = {0};

    initGameState(&gs);


    // Game Loop
    while (!WindowShouldClose() && !gs.shouldQuit)
    {
        updateGame(&gs);
        UpdateMusicStream(gs.bg_music);
        gs.player.sprite_index = (int)(GetTime() / 0.1) % 12;
    }

    unloadGameState(&gs);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}