#include "maze.h"
#include "ui.h"

int main()
{
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Demo Game");
    SetTargetFPS(60);

    // Load Sprites and Textures
    Texture2D wallTexture = LoadTexture("Assets/brick2.png");

    // calculate inital position of the ball
    float init_pos_x = MAZE_MARGIN_X + CELLSIZE * (3.0 / 2);
    float init_pos_y = MAZE_MARGIN_Y + CELLSIZE * (3.0 / 2);

    Vector2 ball_pos0 = {init_pos_x, init_pos_y};
    Vector2 ball_pos = ball_pos0;
    float ball_radius = CELLSIZE / 2;
    float sprite_side = CELLSIZE;
    Vector2 ballSpeed = Vector2Zero();

    // page
    int page = 0;

    srand(time(NULL));
    initializeMaze();
    generateMaze(1, 1);

    // Game Loop
    while (!WindowShouldClose())
    {

        // --------------- MENU PAGE ---------------
        if (page == 0)
        {
            BeginDrawing();
            ClearBackground(GetColor(0xf0f2f5ff));

            // PLAY BUTTON
            Button play_btn = {(Rectangle){SCREENWIDTH * (2.0 / 5), SCREENHEIGHT / 5, SCREENWIDTH / 5, 35},
                               BLUE,
                               0, WHITE, "PLAY", RAYWHITE, 25};
            drawButton(play_btn);
            if (hovered(play_btn))
            {
                play_btn.buttonColor = GetColor(0x7a35ffff);
                drawButtonShadow(play_btn);
            }
            if (clicked(play_btn))
                page = 1;

            // CREDIT BUTTON
            Button credit_btn = {(Rectangle){SCREENWIDTH * (2.0 / 5), SCREENHEIGHT / 5 + 50, SCREENWIDTH / 5, 35},
                                 BLUE,
                                 0, WHITE, "CREDIT", RAYWHITE, 25};
            drawButton(credit_btn);
            if (hovered(credit_btn))
            {
                credit_btn.buttonColor = GetColor(0x7a35ffff);
                drawButtonShadow(credit_btn);
            }
            if (clicked(credit_btn))
                page = 2;

            // QUIT BUTTON
            Button quit_btn = {(Rectangle){SCREENWIDTH * (2.0 / 5), SCREENHEIGHT / 5 + 50 * 2, SCREENWIDTH / 5, 35},
                               BLUE,
                               0, WHITE, "QUIT", RAYWHITE, 25};
            drawButton(quit_btn);
            if (hovered(quit_btn))
            {
                quit_btn.buttonColor = GetColor(0x7a35ffff);
                drawButtonShadow(quit_btn);
            }
            if (clicked(quit_btn))
                break;

            if (hovered(play_btn) || hovered(credit_btn) || hovered(quit_btn))
                SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            else
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);

            EndDrawing();
        }

        // --------------- CREDIT PAGE ---------------
        if (page == 2)
        {
            BeginDrawing();
            ClearBackground(GetColor(0xffefb3ff));
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);

            // Afif Part
            char afif_credit[1000] = "S.M. Afif Iqbal\n2505004";
            Card afif_card = {(Rectangle){SCREENWIDTH * (1.0 / 10), SCREENHEIGHT / 5, SCREENWIDTH * (3.0 / 10), 100},
                              GetColor(0x013e37ff),
                              0, WHITE, "S.M. Afif Iqbal\n2505004", RAYWHITE, 25};
            drawCard(afif_card);
            drawCardShadow(afif_card);

            // Abid Part
            char abid_credit[1000] = "Md Abidur Rahman\n2505019";
            Card abid_card = {(Rectangle){SCREENWIDTH * (6.0 / 10), SCREENHEIGHT / 5, SCREENWIDTH * (3.0 / 10), 100},
                              GetColor(0x013e37ff),
                              0, WHITE, "Md Abidur Rahman\n2505019", RAYWHITE, 25};
            drawCard(abid_card);
            drawCardShadow(abid_card);

            // MENU BUTTON
            Button menu_btn = {(Rectangle){10, SCREENHEIGHT - 30 - 10, 70, 30}, DARKGRAY,
                               0, WHITE,
                               "MENU", RAYWHITE, 20};
            drawButton(menu_btn);
            if (hovered(menu_btn))
            {
                menu_btn.buttonColor = GRAY;
                drawButtonShadow(menu_btn);
                SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            }
            else
            {
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            }
            if (clicked(menu_btn))
                page = 0;

            EndDrawing();
        }

        // --------------- GAME PAGE ---------------
        if (page == 1)
        {
            // Logic Part

            // Delta Time
            float dt = GetFrameTime();

            // movement logic with isPositionFree
            Vector2 ball_posNew = ball_pos;
            if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
                ballSpeed.x = SPEED_MAX;
            else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
                ballSpeed.x = -SPEED_MAX;
            else if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
                ballSpeed.y = -SPEED_MAX;
            else if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
                ballSpeed.y = SPEED_MAX;
            else
                ballSpeed = Vector2Zero();

            ball_posNew = Vector2Add(ball_posNew, Vector2Scale(ballSpeed, dt));

            if (isPostionFree(ball_posNew))
                ball_pos = ball_posNew;

            // Generate New Maze
            if (IsKeyPressed(KEY_SPACE))
            {
                initializeMaze();
                generateMaze(1, 1);
                ball_pos = ball_pos0;
            }

            // frames_count increasing to determine time
            frames_count++;

            // Drawing Part
            BeginDrawing();
            ClearBackground(RAYWHITE);

            drawMaze((Vector2){MAZE_MARGIN_X, MAZE_MARGIN_Y}, CELLSIZE, wallTexture);

            DrawCircleV(ball_pos, ball_radius, RED);
            DrawCircleLinesV(ball_pos, ball_radius, BLACK);

            // Time sector
            DrawText(TextFormat("Time : %2d:%3.1f    Remaining : %2d:%3.1f",
                                frames_count / 3600, (frames_count % 3600) / 60.0,
                                (net_time * 60 - frames_count) / 3600,
                                ((net_time * 60 - frames_count) % 3600) / 60.0),
                     5, 5, 15, BLACK);

            Button menu_btn = {(Rectangle){10, SCREENHEIGHT - 30 - 10, 70, 30}, DARKGRAY,
                               0, WHITE,
                               "MENU", RAYWHITE, 20};
            drawButton(menu_btn);
            if (hovered(menu_btn))
            {
                menu_btn.buttonColor = GRAY;
                drawButtonShadow(menu_btn);
                SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            }
            else
            {
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            }

            if (clicked(menu_btn))
                page = 0;

            EndDrawing();
        }
    }

    UnloadTexture(wallTexture);
    CloseWindow();

    return 0;
}