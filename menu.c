#include <stdio.h>
#include "raylib.h"

int main()
{
    InitWindow(800, 600, "menu");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        Rectangle play_button = {300, 200, 200, 50};

        Vector2 mouse = GetMousePosition();

        int hovered = CheckCollisionPointRec(mouse, play_button);
        if (hovered)
            DrawRectangleRec(play_button, GREEN);
        else
            DrawRectangleRec(play_button, DARKGREEN);
        DrawRectangleLinesEx(play_button, 5, WHITE);

        int clicked = hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
        if (clicked)
            DrawText("Hello, Abid!", play_button.x, play_button.y + play_button.height * 2, 20, WHITE);

        EndDrawing();
    }
    CloseWindow();
}