#include <stdlib.h>
#include <time.h>

#include "ui.h"
#include "game.h"

int main()
{
    GameState gs = {0};
    initGameState(&gs);

    // Game Loop
    while (!WindowShouldClose() && !gs.shouldQuit)
        updateGame(&gs);

    unloadGameState(&gs);

    return 0;
}