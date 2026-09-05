#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "raylib.h"
#include "raymath.h"
#include "game.h"

// set up initial game state, load assets
void initGameState(GameState *gs)
{
    gs->page = MENU;
    gs->shouldQuit = false;

    // Load Textures
    gs->maze.cell_texture = LoadTexture("Assets/Textures/plaster1.png");
    gs->player.player_texture = LoadTexture("Assets/Textures/stone1.png");

    // Load Sprites
    for (int i = 0; i <= 11; i++)
    {
        const char *path1 = TextFormat("Assets/Sprites/Sprites3/Idle/Wraith_03_Idle Blinking_%d.png", i);
        gs->player.player_sprite_idle[i] = LoadTexture(path1);

        const char *path2 = TextFormat("Assets/Sprites/Sprites3/Attacking/Wraith_03_Attack_%d.png", i);
        gs->player.player_sprite_attacking[i] = LoadTexture(path2);

        const char *path3 = TextFormat("Assets/Sprites/Sprites3/Dying/Wraith_01_Dying_%d.png", i);
        gs->player.player_sprite_dying[i] = LoadTexture(path3);
    }

    // Load Fonts
    gs->font1 = LoadFontEx("Assets/Fonts/Font3.otf", 100, NULL, 0);
    gs->btn_font = LoadFontEx("Assets/Fonts/Font4.ttf", 100, NULL, 0);
    gs->title_font = LoadFontEx("Assets/Fonts/Game Of Squids.ttf", 100, NULL, 0);
    gs->msg_font = LoadFontEx("Assets/Fonts/The Amazing Spider-Man.ttf", 100, NULL, 0);

    // Load Sound Effects
    gs->hover_sound = LoadSound("Assets/Sound Effects/pop_1.wav");
    gs->click_sound = LoadSound("Assets/Sound Effects/click_double_on.wav");
    gs->movement_sound = LoadSound("Assets/Sound Effects/water_drop_synthetic.wav");
    gs->movement_blocked_sound = LoadSound("Assets/Sound Effects/cardboard_hit.wav");
    gs->game_finish_sound = LoadSound("Assets/Sound Effects/xylophone_positive_long.wav");

    // Load Music
    gs->bg_music = LoadMusicStream("Assets/Music/Mingle Game Song.mp3");
    gs->bg_music.looping = true;

    // Load Images
    gs->abid_pic = LoadTexture("Assets/Images/abid.png");
    gs->afif_pic = LoadTexture("Assets/Images/afif.png");
}

// unload textures
void unloadGameState(GameState *gs)
{
    UnloadTexture(gs->maze.cell_texture);
    UnloadTexture(gs->player.player_texture);

    // for(int i=0; i<=11; i++){
    //     UnloadTexture(gs->player.player_sprite_idle[i]);
    // }

    UnloadSound(gs->hover_sound);
    UnloadSound(gs->click_sound);
    UnloadSound(gs->movement_sound);
    UnloadSound(gs->movement_blocked_sound);
    UnloadSound(gs->game_finish_sound);

    UnloadMusicStream(gs->bg_music);

    UnloadFont(gs->btn_font);
    UnloadFont(gs->title_font);
    UnloadFont(gs->msg_font);

    destroyMaze(&gs->maze);
}

// draw and update different pages

void updateMenu(GameState *gs)
{
    BeginDrawing();
    ClearBackground(GetColor(0x2e2e2eff));
    
    // TITLE
    const char *title = "SQUID MAZE";
    Vector2 title_pos = {(SCREENWIDTH - MeasureText(title, 100)) / 2, 15};
    drawText(gs->title_font, title, title_pos, 100, 1, WHITE, 80);
    
    // PLAY BUTTON
    Button play_btn = {(Rectangle){SCREENWIDTH * (2.0 / 5), 300, SCREENWIDTH / 5, 35},
    GetColor(0x00f0ffff),
    0, WHITE, "PLAY", gs->btn_font, BLACK, 25, 1, 80};
    drawButton(play_btn);
    if (hovered(play_btn))
    {
        play_btn.buttonColor = BLUE;
        play_btn.textColor = WHITE;
        drawButton(play_btn);
    }
    if (clicked(play_btn))
    {
        PlaySound(gs->click_sound);
        gs->page = PLAYING;
        initGameplay(gs);
        gs->start_time = GetTime();
    }
    
    // CREDIT BUTTON
    Button credit_btn = {(Rectangle){SCREENWIDTH * (2.0 / 5), 300 + 50, SCREENWIDTH / 5, 35},
    GetColor(0x00f0ffff),
    0, WHITE, "CREDIT", gs->btn_font, BLACK, 25, 1, 80};
    drawButton(credit_btn);
    if (hovered(credit_btn))
    {
        credit_btn.buttonColor = BLUE;
        credit_btn.textColor = WHITE;
        drawButton(credit_btn);
    }
    if (clicked(credit_btn))
    {
        PlaySound(gs->click_sound);
        gs->page = CREDIT;
    }
    
    // BEST TIMES BUTTON
    Button best_times_btn = {(Rectangle){SCREENWIDTH * (2.0 / 5), 300 + 50 * 2, SCREENWIDTH / 5, 35},
    GetColor(0x00f0ffff),
    .stroke = 0, WHITE, "BEST TIMES", gs->btn_font, BLACK, 25, 1, 80};
    drawButton(best_times_btn);
    if (hovered(best_times_btn))
    {
        best_times_btn.buttonColor = BLUE;
        best_times_btn.textColor = WHITE;
        drawButton(best_times_btn);
    }
    if (clicked(best_times_btn))
    {
        PlaySound(gs->click_sound);
        gs->page = BEST_TIMES;
    }
    
    // QUIT BUTTON
    Button quit_btn = {(Rectangle){SCREENWIDTH * (2.0 / 5), 300 + 50 * 3, SCREENWIDTH / 5, 35},
    GetColor(0xff6b5bff),
    0, WHITE, "QUIT", gs->btn_font, BLACK, 25, 1, 80};
    drawButton(quit_btn);
    if (hovered(quit_btn))
    {
        quit_btn.buttonColor = GetColor(0xff0055ff);
        quit_btn.textColor = WHITE;
        drawButton(quit_btn);
    }
    if (clicked(quit_btn))
    {
        PlaySound(gs->click_sound);
        gs->shouldQuit = true;
    }
    
    DrawCircleGradient((Vector2){SCREENWIDTH / 2, SCREENHEIGHT / 2}, 100, GetColor(0xffffffaa), BLACK);

    // Sprite Animation
    Texture2D menu_sprite1 = gs->player.player_sprite_attacking[gs->player.sprite_index];
    DrawTexturePro(menu_sprite1, (Rectangle){0, 0, menu_sprite1.width, menu_sprite1.height},
    (Rectangle){80, 250, 300, 300}, Vector2Zero(), 0, WHITE);
    
    Texture2D menu_sprite2 = gs->player.player_sprite_dying[gs->player.sprite_index];
    DrawTexturePro(menu_sprite2, (Rectangle){0, 0, -menu_sprite2.width, menu_sprite2.height},
    (Rectangle){1000, 250, 300, 300}, Vector2Zero(), 0, WHITE);
    
    // change mouse cursor
    if (hovered(play_btn) || hovered(credit_btn) || hovered(best_times_btn) || hovered(quit_btn))
    {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        // PlaySound(gs->hover_sound);
    }
    else
    SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    
    EndDrawing();
}

void updateNameInput(GameState *gs)
{
    char name[20] = "";
    int letter_count = 0;

    int letter = GetCharPressed();
    while (letter)
    {
        if (letter_count < 19 && ((letter >= 'A' && letter <= 'Z') ||
                                  (letter >= 'a' && letter <= 'z')))
        {
            name[letter_count] = letter;
            name[letter_count + 1] = '\0';
            letter_count++;
        }

        if (IsKeyPressed(KEY_BACKSPACE) && letter_count)
        {
            letter_count--;
            name[letter_count] = '\0';
        }

        letter = GetCharPressed();
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        gs->page = PLAYING;
        PlaySound(gs->click_sound);
    }
}

void drawNameInput(GameState *gs)
{
    BeginDrawing();
    ClearBackground(GetColor(0xffefb3ff));

    Card input_card = {(Rectangle){SCREENWIDTH * (1.0 / 5), SCREENHEIGHT * (1.0 / 5), SCREENWIDTH * (3.0 / 5), 100},
                       GetColor(0x013e37ff),
                       0, WHITE, "", gs->font1, RAYWHITE, 25};

    EndDrawing();
}

void drawCredit(GameState *gs)
{
    BeginDrawing();
    ClearBackground(GetColor(0xffefb3ff));
    SetMouseCursor(MOUSE_CURSOR_DEFAULT);

    // Abid Part
    Rectangle abid_pic_rec = (Rectangle){SCREENWIDTH * (6.0 / 10), SCREENHEIGHT * (1.5 / 10), SCREENWIDTH * (3.0 / 10), SCREENHEIGHT / 2.0};
    drawTextureShadowed(gs->abid_pic, abid_pic_rec);

    const char *abid_credit = "Md Abidur Rahman\n2505019\n";
    Card abid_card = {(Rectangle){SCREENWIDTH * (6.0 / 10), SCREENHEIGHT * (6.5 / 10), SCREENWIDTH * (3.0 / 10), 100}, GetColor(0x013e37ff), 0, WHITE, abid_credit, gs->font1, RAYWHITE, 30, 1, 0, 80, 10, 10};
    drawCard(abid_card);

    // Afif Part
    Rectangle afif_pic_rec = (Rectangle){SCREENWIDTH * (1.0 / 10), SCREENHEIGHT * (1.5 / 10), SCREENWIDTH * (3.0 / 10), SCREENHEIGHT / 2.0};
    drawTextureShadowed(gs->afif_pic, afif_pic_rec);

    const char *afif_credit = "S.M. Afif Iqbal\n2505004\n";
    Card afif_card = {(Rectangle){SCREENWIDTH * (1.0 / 10), SCREENHEIGHT * (6.5 / 10), SCREENWIDTH * (3.0 / 10), 100}, GetColor(0x013e37ff), 0, WHITE, afif_credit, gs->font1, RAYWHITE, 30, 1, 0, 80, 10, 10};
    drawCard(afif_card);

    // MENU BUTTON
    Button menu_btn = {(Rectangle){10, 10, 100, 40}, DARKBLUE,
                       0, WHITE,
                       "MENU", gs->btn_font, RAYWHITE, 20, 1, 0};
    drawButton(menu_btn);
    if (hovered(menu_btn))
    {
        menu_btn.buttonColor = BLUE;
        menu_btn.shadow_opacity = 80;
        drawButton(menu_btn);
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    }
    else
    {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
    if (clicked(menu_btn) || IsKeyPressed(KEY_BACKSPACE))
    {
        PlaySound(gs->click_sound);
        gs->page = MENU;
    }

    EndDrawing();
}

void drawBestTimes(GameState *gs)
{
    char player_names_[20][10] = {"Abid",
                                  "Afif",
                                  "Rumman",
                                  "Tahsin",
                                  "Akif",
                                  "Ahnaf",
                                  "Raisa",
                                  "Ananto",
                                  "Jibon",
                                  "Mahin"};
    float best_times_[10] = {23.12,
                             12.67,
                             21.98,
                             67.89,
                             12.43,
                             76.54,
                             12.09,
                             32.30,
                             11.21,
                             10.01};

    BeginDrawing();
    ClearBackground(GetColor(0xdff7ffff));

    for (int i = 0; i < 10; i++)
    {
        // Player Name
        Rectangle player_name_rec = {200, (SCREENHEIGHT - 500) / 2 + 60 * i, 450, 45};
        Card player_name_card = {player_name_rec, GetColor(0xffe2b8ff), 0, WHITE, TextFormat("\n%s", player_names_[i]), gs->btn_font, GetColor(0x053d3aff), 25, 1, -15, 80, -5, 5};
        drawCard(player_name_card);

        // Best Time
        Rectangle best_times_rec = {700, (SCREENHEIGHT - 500) / 2 + 60 * i, 450, 45};
        const char *best_time_text = formatTime(best_times_[i]);
        Card best_times_card = {best_times_rec, GetColor(0x053d3aff), 0, WHITE, TextFormat("\n%s", best_time_text), gs->btn_font, GetColor(0xffe2b8ff), 25, 1, -17, 80, 5, 5};
        drawCard(best_times_card);
    }

    // MENU BUTTON
    Button menu_btn = {(Rectangle){10, 10, 100, 40}, DARKBLUE,
                       0, WHITE,
                       "MENU", gs->btn_font, RAYWHITE, 20, 1, 0};
    drawButton(menu_btn);
    if (hovered(menu_btn))
    {
        menu_btn.buttonColor = BLUE;
        menu_btn.shadow_opacity = 80;
        drawButton(menu_btn);
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    }
    else
    {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    if (clicked(menu_btn) || IsKeyPressed(KEY_BACKSPACE))
    {
        PlaySound(gs->click_sound);
        gs->page = MENU;
    }

    EndDrawing();
}

bool isCellAllowed(Cell cell1, Cell cell2)
{
    if (cell1.x == cell2.x)
    {
        if (cell1.y - cell2.y == 1)
        {
            return !(cell1.up_wall && cell2.down_wall);
        }
        else if (cell2.y - cell1.y == 1)
        {
            return !(cell2.up_wall && cell1.down_wall);
        }
    }
    else if (cell1.y == cell2.y)
    {
        if (cell1.x - cell2.x == 1)
        {
            return !(cell1.left_wall && cell2.right_wall);
        }
        else if (cell2.x - cell1.x == 1)
        {
            return !(cell2.left_wall && cell1.right_wall);
        }
    }
    return true;
}

void initGameplay(GameState *gs)
{
    // calculate inital position of the ball
    float init_pos_x = MAZE_MARGIN_X + CELLSIZE * (3.0 / 2);
    float init_pos_y = MAZE_MARGIN_Y + CELLSIZE * (3.0 / 2);

    gs->player.x = 0;
    gs->player.y = 0;

    srand(time(NULL));
    initializeMaze(&gs->maze, MAZEHEIGHT, MAZEWIDTH);
    generateMaze2(&gs->maze);
}

void updateGameplay(GameState *gs)
{

    // Logic Part

    // Delta Time
    float dt = GetFrameTime();

    // movement
    int x = gs->player.x;
    int y = gs->player.y;
    Cell cell_old = gs->maze.cells[y][x];

    bool movement_attempt = false;

    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
    {
        y--;
        movement_attempt = true;
    }
    else if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
    {
        y++;
        movement_attempt = true;
    }
    else if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))
    {
        x++;
        movement_attempt = true;
        gs->player.flip = false;
    }
    else if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))
    {
        x--;
        movement_attempt = true;
        gs->player.flip = true;
    }

    if (movement_attempt)
    {
        if (isCellValid(x, y, gs->maze))
        {
            Cell cell_new = gs->maze.cells[y][x];
            if (isCellAllowed(cell_old, cell_new))
            {
                gs->player.x = x;
                gs->player.y = y;
                PlaySound(gs->movement_sound);
            }
            else
            {
                PlaySound(gs->movement_blocked_sound);
            }
        }
        else
        {
            PlaySound(gs->movement_blocked_sound);
        }
    }

    // Generate New Maze
    if (IsKeyPressed(KEY_SPACE))
    {
        gs->start_time = GetTime();

        PlaySound(gs->click_sound);

        destroyMaze(&gs->maze);
        initializeMaze(&gs->maze, MAZEHEIGHT, MAZEWIDTH);
        generateMaze2(&gs->maze);

        gs->player.x = 0;
        gs->player.y = 0;
    }

    // Game Finished
    if (gs->player.x == MAZEWIDTH - 1 && gs->player.y == MAZEHEIGHT - 1)
    {
        gs->last_time = GetTime() - gs->start_time;
        PlaySound(gs->game_finish_sound);
        gs->page = GAME_FINISH;
    }
}

void drawGame(GameState *gs)
{
    BeginDrawing();
    ClearBackground(GetColor(0x0d0d0dff));

    drawMaze(&gs->maze, (Vector2){MAZE_MARGIN_X, MAZE_MARGIN_Y}, CELLSIZE, &gs->player);

    // Title
    const char *title = "CHAMBER OF SECRETS";
    DrawTextEx(gs->title_font, title, (Vector2){(SCREENWIDTH - MeasureText(title, 40)) / 2, 20}, 40, 1, WHITE);

    // MENU BUTTON
    Button menu_btn = {(Rectangle){10, 10, 100, 40}, DARKBLUE,
                       0, WHITE,
                       "MENU", gs->btn_font, RAYWHITE, 20, 1, 0};
    drawButton(menu_btn);
    if (hovered(menu_btn))
    {
        menu_btn.buttonColor = BLUE;
        menu_btn.shadow_opacity = 80;
        drawButton(menu_btn);
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    }
    else
    {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    if (clicked(menu_btn) || IsKeyPressed(KEY_BACKSPACE))
    {
        PlaySound(gs->click_sound);
        gs->page = MENU;
    }

    // BRAND NEW MAZE
    double current_time = GetTime() - gs->start_time;
    const char *new_maze_msg = "BRAND NEW MAZE";
    if (current_time <= 0.5 || (current_time >= 1 && current_time <= 1.5))
    {
        DrawTextEx(gs->msg_font, new_maze_msg, (Vector2){(SCREENWIDTH - MeasureText(new_maze_msg, 50)) / 2, SCREENHEIGHT - 65}, 50, 1, WHITE);
    }

    // Time sector
    const char *time_text = formatTime(current_time);
    DrawTextEx(gs->btn_font, time_text, (Vector2){1300, 15}, 20, 1, WHITE);

    EndDrawing();
}

void drawScore(GameState *gs)
{
    BeginDrawing();
    ClearBackground(GetColor(0xddfbefff));

    // MENU BUTTON
    Button menu_btn = {(Rectangle){10, 10, 100, 40}, DARKBLUE,
                       0, WHITE,
                       "MENU", gs->btn_font, RAYWHITE, 20, 1, 0};
    drawButton(menu_btn);
    if (hovered(menu_btn))
    {
        menu_btn.buttonColor = BLUE;
        menu_btn.shadow_opacity = 80;
        drawButton(menu_btn);
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    }
    else
    {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    if (clicked(menu_btn) || IsKeyPressed(KEY_BACKSPACE))
    {
        PlaySound(gs->click_sound);
        gs->page = MENU;
    }

    Card time_card = {(Rectangle){SCREENWIDTH * (2.0 / 5), SCREENHEIGHT / 2 - 50, SCREENHEIGHT * (1.0 / 5), 100}, GetColor(0x2f4858ff), 0, BLACK, formatTime(gs->last_time), gs->font1, WHITE, 40, 1, 10, 80, 10, 10};

    drawCard(time_card);

    EndDrawing();
}

void updateGame(GameState *gs)
{
    switch (gs->page)
    {
    case MENU:
        updateMenu(gs);
        break;

    case NAME_INPUT:
        updateNameInput(gs);
        drawNameInput(gs);
        break;

    case PLAYING:
        updateGameplay(gs);
        drawGame(gs);
        break;

    case GAME_FINISH:
        drawScore(gs);
        break;

    case CREDIT:
        drawCredit(gs);
        break;

    case BEST_TIMES:
        drawBestTimes(gs);
        break;

    default:
        break;
    }
}