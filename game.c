#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"

// set up initial game state, load assets
void initGameState(GameState *gs)
{

    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Demo Game");
    InitAudioDevice();
    SetTargetFPS(60);

    srand(time(NULL));

    gs->page = MENU;
    gs->shouldQuit = false;

    // Load Textures
    gs->maze.cell_texture = LoadTexture("Assets/Textures/plaster1.png");
    gs->maze.crossed_cell_texture = LoadTexture("Assets/Textures/crossed_cells.png");
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
    gs->font1 = LoadFontEx("Assets/Fonts/font1.otf", 100, NULL, 0);
    gs->font2 = LoadFontEx("Assets/Fonts/font2.ttf", 100, NULL, 0);
    gs->font3 = LoadFontEx("Assets/Fonts/font3.otf", 100, NULL, 0);
    gs->font4 = LoadFontEx("Assets/Fonts/font4.ttf", 100, NULL, 0);
    gs->btn_font = LoadFontEx("Assets/Fonts/btn_font.ttf", 100, NULL, 0);
    gs->title_font = LoadFontEx("Assets/Fonts/title_font.ttf", 100, NULL, 0);
    gs->msg_font = LoadFontEx("Assets/Fonts/msg_font.ttf", 100, NULL, 0);

    // Load Sound Effects
    gs->click_sound1 = LoadSound("Assets/Sound Effects/click_double_on.wav");
    gs->movement_sound = LoadSound("Assets/Sound Effects/water_drop_synthetic.wav");
    gs->movement_blocked_sound = LoadSound("Assets/Sound Effects/cardboard_hit.wav");
    gs->game_finish_sound = LoadSound("Assets/Sound Effects/xylophone_positive_long.wav");

    // Load Music
    gs->bg_music = LoadMusicStream("Assets/Music/Mingle Game Song.mp3");
    gs->bg_music.looping = true;
    gs->music_on = true;

    // Optimize Volume
    SetMusicVolume(gs->bg_music, 0.3f);
    SetSoundVolume(gs->movement_sound, 2);
    SetSoundVolume(gs->game_finish_sound, 2);
    SetSoundVolume(gs->movement_blocked_sound, 1.5);

    // Load Images
    gs->abid_pic = LoadTexture("Assets/Images/abid.png");
    gs->afif_pic = LoadTexture("Assets/Images/afif.png");

    // Name Input
    gs->name[0] = '\0';
    gs->letter_count = 0;

    // Load Best Times (THE BEST OF US)

    PlayMusicStream(gs->bg_music);
}

void unloadGameState(GameState *gs)
{
    // Unload Textures
    UnloadTexture(gs->maze.cell_texture);
    UnloadTexture(gs->maze.crossed_cell_texture);
    UnloadTexture(gs->player.player_texture);

    // Unload Fonts
    UnloadFont(gs->font1);
    UnloadFont(gs->font2);
    UnloadFont(gs->btn_font);
    UnloadFont(gs->title_font);
    UnloadFont(gs->msg_font);

    // Unload Sound Effects
    UnloadSound(gs->click_sound1);
    UnloadSound(gs->movement_sound);
    UnloadSound(gs->movement_blocked_sound);
    UnloadSound(gs->game_finish_sound);

    // Unload Music
    UnloadMusicStream(gs->bg_music);

    // Unload Images
    UnloadTexture(gs->abid_pic);
    UnloadTexture(gs->afif_pic);

    destroyMaze(&gs->maze);

    CloseAudioDevice();
    CloseWindow();
}

// draw and update different pages

void drawMenu(GameState *gs)
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
        PlaySound(gs->click_sound1);
        gs->page = NAME_INPUT;
        gs->name[0] = '\0';
        gs->letter_count = 0;
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
        PlaySound(gs->click_sound1);
        gs->page = CREDIT;
    }

    // BEST TIMES/HIGH SCORES BUTTON
    const char *best_times_btn_text;
    if (gs->mode == BEST)
        best_times_btn_text = "BEST TIMES";
    else if (gs->mode == MULTIVERSE || gs->mode == DARK_NIGHT)
        best_times_btn_text = "HIGH SCORES";

    Button best_times_btn = {(Rectangle){SCREENWIDTH * (2.0 / 5), 300 + 50 * 2, SCREENWIDTH / 5, 35},
                             GetColor(0x00f0ffff),
                             .stroke = 0, WHITE, best_times_btn_text, gs->btn_font, BLACK, 25, 1, 80};
    drawButton(best_times_btn);
    if (hovered(best_times_btn))
    {
        best_times_btn.buttonColor = BLUE;
        best_times_btn.textColor = WHITE;
        drawButton(best_times_btn);
    }
    if (clicked(best_times_btn))
    {
        PlaySound(gs->click_sound1);
        if (gs->mode == BEST)
            gs->page = BEST_TIMES;
        else if (gs->mode == MULTIVERSE)
            gs->page = HIGH_SCORES;
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
        PlaySound(gs->click_sound1);
        gs->shouldQuit = true;
    }

    // Mode Selection Options

    // The Best Of Us
    Button best_mode_btn = {(Rectangle){20, 550, 300, 50}, WHITE, 0, BLACK, "THE BEST OF US", gs->font2, BLACK, 20, 1, 0};
    drawButton(best_mode_btn);

    if (hovered(best_mode_btn) || gs->mode == BEST)
    {
        best_mode_btn.buttonColor = DARKBLUE;
        best_mode_btn.textColor = WHITE;
        drawButton(best_mode_btn);
    }
    if (clicked(best_mode_btn))
    {
        PlaySound(gs->click_sound1);
        gs->mode = BEST;
    }

    // The Multiverse of Madmaze
    Button multiverse_mode_btn = {(Rectangle){350, 550, 500, 50}, WHITE, 0, BLACK, "THE MULTIVERSE OF MADMAZE", gs->font2, BLACK, 20, 1, 0};
    drawButton(multiverse_mode_btn);

    if (hovered(multiverse_mode_btn) || gs->mode == MULTIVERSE)
    {
        multiverse_mode_btn.buttonColor = DARKBLUE;
        multiverse_mode_btn.textColor = WHITE;
        drawButton(multiverse_mode_btn);
    }
    if (clicked(multiverse_mode_btn))
    {
        PlaySound(gs->click_sound1);
        gs->mode = MULTIVERSE;
        gs->level = 1;
    }

    // The Dark Knight
    Button dark_night_mode_btn = {(Rectangle){870, 550, 400, 50}, WHITE, 0, BLACK, "THE DARK NIGHT", gs->font2, BLACK, 20, 1, 0};
    drawButton(dark_night_mode_btn);

    if (hovered(dark_night_mode_btn) || gs->mode == DARK_NIGHT)
    {
        dark_night_mode_btn.buttonColor = DARKBLUE;
        dark_night_mode_btn.textColor = WHITE;
        drawButton(dark_night_mode_btn);
    }
    if (clicked(dark_night_mode_btn))
    {
        PlaySound(gs->click_sound1);
        gs->mode = DARK_NIGHT;
    }

    // Sprite Animation
    Texture2D menu_sprite1 = gs->player.player_sprite_attacking[gs->player.sprite_index];
    DrawTexturePro(menu_sprite1, (Rectangle){0, 0, menu_sprite1.width, menu_sprite1.height},
                   (Rectangle){80, 250, 300, 300}, Vector2Zero(), 0, WHITE);

    Texture2D menu_sprite2 = gs->player.player_sprite_dying[gs->player.sprite_index];
    DrawTexturePro(menu_sprite2, (Rectangle){0, 0, -menu_sprite2.width, menu_sprite2.height},
                   (Rectangle){1000, 250, 300, 300}, Vector2Zero(), 0, WHITE);

    // Mute Music Button
    Button mute_music_btn = {(Rectangle){1150, 10, 200, 40}, DARKBLUE,
                             0, WHITE,
                             "MUTE MUSIC", gs->btn_font, RAYWHITE, 20, 1, 0};
    drawButton(mute_music_btn);
    if (hovered(mute_music_btn))
    {
        mute_music_btn.buttonColor = BLUE;
        mute_music_btn.shadow_opacity = 80;
        drawButton(mute_music_btn);
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    }
    else
    {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
    if (clicked(mute_music_btn))
    {
        PlaySound(gs->click_sound1);
        if (gs->music_on)
        {
            SetMusicVolume(gs->bg_music, 0);
            gs->music_on = false;
        }
        else
        {
            SetMusicVolume(gs->bg_music, 0.3f);
            gs->music_on = true;
        }
    }

    // change mouse cursor
    if (hovered(play_btn) || hovered(credit_btn) || hovered(best_times_btn) || hovered(quit_btn) || hovered(best_mode_btn) || hovered(multiverse_mode_btn) || hovered(mute_music_btn))
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
    int letter = GetCharPressed();
    while (letter)
    {
        if (gs->letter_count < 19 && ((letter >= 'A' && letter <= 'Z') ||
                                      (letter >= 'a' && letter <= 'z')))
        {
            gs->name[gs->letter_count] = (char)letter;
            gs->name[gs->letter_count + 1] = '\0';
            gs->letter_count++;
        }

        letter = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) && gs->letter_count)
    {
        gs->letter_count--;
        gs->name[gs->letter_count] = '\0';
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        PlaySound(gs->click_sound1);

        if (gs->mode == BEST)
        {
            gs->page = PLAYING;
            gs->start_time = GetTime();
            initGameplay(gs);
        }
        else if (gs->mode == MULTIVERSE)
        {
            gs->page = LEVELS;
        }
    }
}

void drawNameInput(GameState *gs)
{
    BeginDrawing();
    ClearBackground(GetColor(0xf15153ff));

    const char *instruct = "ENTER YOUR NAME";
    DrawTextEx(gs->font1, instruct, (Vector2){(SCREENWIDTH - MeasureText(instruct, 30)) / 2.0, SCREENHEIGHT / 2.0 - 150}, 30, 1, WHITE);

    Card input_card = {(Rectangle){SCREENWIDTH * (1.0 / 5), SCREENHEIGHT * (1.0 / 2) - 100, SCREENWIDTH * (3.0 / 5), 100},
                       GetColor(0x321847ff),
                       0, WHITE, gs->name, gs->font1, RAYWHITE, 80, 1, 10, 80, 5, 5};
    drawCard(input_card);

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
    if (clicked(menu_btn))
    {
        PlaySound(gs->click_sound1);
        gs->page = MENU;
    }

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
    Card abid_card = {(Rectangle){SCREENWIDTH * (6.0 / 10), SCREENHEIGHT * (6.5 / 10), SCREENWIDTH * (3.0 / 10), 100}, GetColor(0x013e37ff), 0, WHITE, abid_credit, gs->font1, RAYWHITE, 30, 1, 20, 80, 10, 10};
    drawCard(abid_card);

    // Afif Part
    Rectangle afif_pic_rec = (Rectangle){SCREENWIDTH * (1.0 / 10), SCREENHEIGHT * (1.5 / 10), SCREENWIDTH * (3.0 / 10), SCREENHEIGHT / 2.0};
    drawTextureShadowed(gs->afif_pic, afif_pic_rec);

    const char *afif_credit = "S.M. Afif Iqbal\n2505004\n";
    Card afif_card = {(Rectangle){SCREENWIDTH * (1.0 / 10), SCREENHEIGHT * (6.5 / 10), SCREENWIDTH * (3.0 / 10), 100}, GetColor(0x013e37ff), 0, WHITE, afif_credit, gs->font1, RAYWHITE, 30, 1, 20, 80, 10, 10};
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
        PlaySound(gs->click_sound1);
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
        PlaySound(gs->click_sound1);
        gs->page = MENU;
    }

    EndDrawing();
}

void drawHighScores(GameState *gs)
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
        const char *best_time_text = TextFormat("%.2lf", best_times_[i]);
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
        PlaySound(gs->click_sound1);
        gs->page = MENU;
    }

    EndDrawing();
}

void drawLevels(GameState *gs)
{
    BeginDrawing();
    ClearBackground(GetColor(0xdff7ffff));

    const char *title = "THE MULTIVERSE OF MADMAZE";
    DrawTextEx(gs->title_font, title, (Vector2){(SCREENWIDTH - MeasureText(title, 50)) / 2, 20}, 50, 1, BLACK);

    Vector2 pos = {65, 100};
    for (int i = 1; i <= 5; i++)
    {
        for (int j = 1; j <= 10; j++)
        {
            int level_no = (i - 1) * 10 + j;
            Button level_btn = {(Rectangle){pos.x, pos.y, 100, 100}, GetColor(0x0b132bff), 0, WHITE, TextFormat("LVL %d", level_no), gs->font4, GetColor(0x39ff88ff), 20, 1, 0};
            drawButton(level_btn);
            pos.x += 130;
            if (hovered(level_btn))
            {
                level_btn.buttonColor = GetColor(0xff0055ff);
                level_btn.textColor = WHITE;
                level_btn.shadow_opacity = 80;
                drawButton(level_btn);
            }

            if (clicked(level_btn))
            {
                PlaySound(gs->click_sound1);
                gs->level = level_no;
                gs->page = PLAYING;
                initGameplay(gs);
            }
        }
        pos.x = 65;
        pos.y += 130;
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
        PlaySound(gs->click_sound1);
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
    gs->player.x = 0;
    gs->player.y = 0;

    if (gs->mode == BEST)
        gs->level = 0;

    initializeMaze(&gs->maze, gs->level);
    generateMaze_prim(&gs->maze);
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
                gs->maze.cells[y][x].cellState = CROSSED;
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
    if (IsKeyPressed(KEY_SPACE) && gs->mode == BEST)
    {
        gs->start_time = GetTime();

        PlaySound(gs->click_sound1);

        destroyMaze(&gs->maze);
        initGameplay(gs);
    }

    // Game Finished
    if (gs->player.x == gs->maze.width - 1 && gs->player.y == gs->maze.height - 1)
    {
        gs->last_time = GetTime() - gs->start_time;
        PlaySound(gs->game_finish_sound);
        if (gs->mode == BEST)
        {
            gs->page = GAME_FINISH;
        }
        else if (gs->mode == MULTIVERSE)
        {
            destroyMaze(&gs->maze);
            if (gs->level < 50)
            {
                gs->level++;
                initGameplay(gs);
            }
            else
            {
                gs->page = MULTIVERSE_CONQUERED;
            }
        }
    }
}

void drawGame(GameState *gs)
{
    BeginDrawing();
    ClearBackground(GetColor(0x0d0d0dff));

    Vector2 maze_starting_pos = {(SCREENWIDTH - gs->maze.width * gs->maze.cell_size) / 2,
                                 (SCREENHEIGHT - gs->maze.height * gs->maze.cell_size) / 2 + gs->maze.cell_size};
    drawMaze(&gs->maze, maze_starting_pos, &gs->player);

    // TITLE
    const char *title;
    if (gs->mode == BEST)
        title = "THE BEST OF US";
    else if (gs->mode == MULTIVERSE)
        title = "THE MULTIVERSE OF MADMAZE";

    DrawTextEx(gs->title_font, title, (Vector2){(SCREENWIDTH - MeasureText(title, 50)) / 2, 20}, 50, 1, WHITE);

    // Control Instructions
    const char *control_inst = "W/A/S/D or Arrow Keys for Movement | Space for New Maze | F for Auto Solve";
    DrawTextEx(gs->font1, control_inst, (Vector2){(SCREENWIDTH - MeasureText(control_inst, 20)) / 2, 70}, 20, 1, GRAY);

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

    if (clicked(menu_btn))
    {
        PlaySound(gs->click_sound1);
        gs->page = MENU;
    }

    if (IsKeyPressed(KEY_BACKSPACE))
    {
        if (gs->mode == BEST)
            gs->page = MENU;
        else if (gs->mode == MULTIVERSE)
            gs->page = LEVELS;
    }

    // BRAND NEW MAZE
    double current_time = GetTime() - gs->start_time;
    // const char *new_maze_msg = "BRAND NEW MAZE";
    // Card new_maze_card = {(Rectangle){(SCREENWIDTH - 500) / 2, (SCREENHEIGHT - 100) / 2, 500, 100},
    //                       DARKBLUE, 0, WHITE, new_maze_msg, gs->msg_font, WHITE, 50, 1, 20, 80, 10, 10};
    // if (current_time <= 1)
    // {
    //     drawCard(new_maze_card);
    // }

    if (gs->mode == BEST)
    {
        // Time sector
        const char *time_text = formatTime(current_time);
        DrawTextEx(gs->btn_font, time_text, (Vector2){1250, 15}, 20, 1, WHITE);
    }
    else if (gs->mode == MULTIVERSE)
    {
        // Level
        DrawTextEx(gs->btn_font, TextFormat("LEVEL: %d", gs->level), (Vector2){1250, 15}, 20, 1, WHITE);
    }

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
        PlaySound(gs->click_sound1);
        gs->page = MENU;
    }

    // Time Card
    const char *time_card_text = TextFormat("%s\n%s", gs->name, formatTime(gs->last_time));
    Card time_card = {(Rectangle){SCREENWIDTH * (2.0 / 5), SCREENHEIGHT / 2 - 100, SCREENWIDTH * (1.0 / 5), 100}, GetColor(0x2f4858ff), 0, BLACK, time_card_text, gs->font1, WHITE, 40, 1, 10, 80, 10, 10};

    drawCard(time_card);

    Button quit_btn = {(Rectangle){SCREENWIDTH * (2.0 / 5), SCREENHEIGHT / 2 + 30, 140, 50}, GetColor(0xff6b5bff), 0, BLACK, "QUIT GAME", gs->btn_font, WHITE, 15, 1, 0};

    drawButton(quit_btn);

    if (hovered(quit_btn))
    {
        quit_btn.buttonColor = GetColor(0xff0055ff);
        quit_btn.shadow_opacity = 80;
        drawButton(quit_btn);
    }

    if (clicked(quit_btn))
    {
        gs->shouldQuit = true;
    }

    Button replay_btn = {(Rectangle){SCREENWIDTH * (2.0 / 5) + 160, SCREENHEIGHT / 2 + 30, 120, 50}, DARKGREEN, 0, BLACK, "REPLAY", gs->btn_font, WHITE, 15, 1, 0};

    if (hovered(replay_btn))
    {
        replay_btn.buttonColor = GREEN;
        replay_btn.shadow_opacity = 80;
        drawButton(replay_btn);
    }

    if (clicked(replay_btn))
    {

        PlaySound(gs->click_sound1);
        gs->page = PLAYING;
        initGameplay(gs);
        gs->start_time = GetTime();
    }

    drawButton(replay_btn);

    EndDrawing();
}

void drawMultiConq(GameState *gs)
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
        PlaySound(gs->click_sound1);
        gs->page = MENU;
    }

    // Congrats Card
    const char *congo_text = "       Jhapana!!\n  Tu si great ho..\nTohfa qabul karo.";
    Card congo_card = {(Rectangle){SCREENWIDTH * (2.0 / 5), SCREENHEIGHT / 2 - 120, SCREENWIDTH * (1.0 / 5), 120}, GetColor(0x2f4858ff), 0, BLACK, congo_text, gs->font1, WHITE, 30, 1, 10, 80, 10, 10};

    drawCard(congo_card);

    Button quit_btn = {(Rectangle){SCREENWIDTH * (2.0 / 5), SCREENHEIGHT / 2 + 30, 140, 50}, GetColor(0xff6b5bff), 0, BLACK, "QUIT GAME", gs->btn_font, WHITE, 15, 1, 0};

    drawButton(quit_btn);

    if (hovered(quit_btn))
    {
        quit_btn.buttonColor = GetColor(0xff0055ff);
        quit_btn.shadow_opacity = 80;
        drawButton(quit_btn);
    }

    if (clicked(quit_btn))
    {
        gs->shouldQuit = true;
    }

    Button replay_btn = {(Rectangle){SCREENWIDTH * (2.0 / 5) + 160, SCREENHEIGHT / 2 + 30, 120, 50}, DARKGREEN, 0, BLACK, "REPLAY", gs->btn_font, WHITE, 15, 1, 0};

    if (hovered(replay_btn))
    {
        replay_btn.buttonColor = GREEN;
        replay_btn.shadow_opacity = 80;
        drawButton(replay_btn);
    }

    if (clicked(replay_btn))
    {

        PlaySound(gs->click_sound1);
        gs->page = PLAYING;
        initGameplay(gs);
        gs->start_time = GetTime();
    }

    drawButton(replay_btn);

    EndDrawing();
}

void updateGame(GameState *gs)
{

    UpdateMusicStream(gs->bg_music);
    gs->player.sprite_index = (int)(GetTime() / 0.1) % 12;

    switch (gs->page)
    {
    case MENU:
        drawMenu(gs);
        break;

    case NAME_INPUT:
        updateNameInput(gs);
        drawNameInput(gs);
        break;

    case LEVELS:
        drawLevels(gs);
        break;

    case PLAYING:
        updateGameplay(gs);
        drawGame(gs);
        break;

    case GAME_FINISH:
        drawScore(gs);
        break;

    case MULTIVERSE_CONQUERED:
        drawMultiConq(gs);
        break;

    case CREDIT:
        drawCredit(gs);
        break;

    case BEST_TIMES:
        drawBestTimes(gs);
        break;

    case HIGH_SCORES:
        drawHighScores(gs);
        break;

    default:
        break;
    }
}