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

    PlayMusicStream(gs.bg_music);
    SetMusicVolume(gs.bg_music, 0.3f);
    SetSoundVolume(gs.movement_sound, 2);
    SetSoundVolume(gs.game_finish_sound, 2);
    SetSoundVolume(gs.movement_blocked_sound, 1.5);

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