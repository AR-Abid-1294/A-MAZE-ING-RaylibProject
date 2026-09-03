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

    GameState gs = {0};

    initGameState(&gs);

    // Game Loop
    while (!WindowShouldClose() && !gs.shouldQuit)
    {
        updateGame(&gs);
    }

    unloadGameState(&gs);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}