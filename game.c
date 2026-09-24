#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"

// set up initial game state, load assets
void initGameState(GameState *gs)
{

    InitWindow(SCREENWIDTH, SCREENHEIGHT, "A MAZE ING");
    InitAudioDevice();
    SetTargetFPS(60);

    srand(time(NULL));

    generateMaze = generateMaze_aldous_broder;

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

    // Load Buttons
    gs->music_on_btn = LoadTexture("Assets/Buttons/music_on.png");
    gs->music_hovered_btn = LoadTexture("Assets/Buttons/music_hovered.png");
    gs->music_off_btn = LoadTexture("Assets/Buttons/music_off.png");
    gs->info_btn = LoadTexture("Assets/Buttons/info.png");
    gs->info_hovered_btn = LoadTexture("Assets/Buttons/info_hovered.png");
    gs->settings_btn = LoadTexture("Assets/Buttons/settings.png");
    gs->settings_hovered_btn = LoadTexture("Assets/Buttons/settings_hovered.png");
    gs->menu_btn = LoadTexture("Assets/Buttons/menu.png");
    gs->menu_hovered_btn = LoadTexture("Assets/Buttons/menu_hovered.png");

    // Load Mode Selection Buttons
    gs->best_of_us_btn = LoadTexture("Assets/Mode Buttons/the_best_of_us.png");
    gs->multiverse_btn = LoadTexture("Assets/Mode Buttons/multiverse_of_madmaze.png");
    gs->dark_night_btn = LoadTexture("Assets/Mode Buttons/dark_night.png");
    gs->infinity_war_btn = LoadTexture("Assets/Mode Buttons/infinity_war.png");
    gs->time_runs_out_btn = LoadTexture("Assets/Mode Buttons/time_runs_out.png");
    gs->gravity_grave_btn = LoadTexture("Assets/Mode Buttons/gravity_grave.png");
    gs->endgame_btn = LoadTexture("Assets/Mode Buttons/endgame.png");

    // Name Input
    gs->name[0] = '\0';
    gs->letter_count = 0;

    // Load Leaderboard Data

    // Best Times for THE BEST OF US
    gs->best_times_file = fopen("scores/Best_Times.txt", "r");
    for (int i = 0; i < 10; i++)
        fscanf(gs->best_times_file, "%f %[^\n]", &gs->best_times[i].time, gs->best_times[i].player_name);
    fclose(gs->best_times_file);

    // High Scores for THE MULTIVERSE OF MADMAZE
    gs->high_scores_file = fopen("scores/High_Scores.txt", "r");
    for (int i = 0; i < 10; i++)
        fscanf(gs->high_scores_file, "%d %[^\n]", &gs->high_scores[i].score, gs->high_scores[i].player_name);
    fclose(gs->high_scores_file);

    // Dark Times for the DARK NIGHT
    gs->dark_times_file = fopen("scores/Dark_Nights.txt","r");
    for (int i = 0; i < 10; i++)
        fscanf(gs->dark_times_file, "%f %[^\n]", &gs->dark_times[i].time, gs->dark_times[i].player_name);
    fclose(gs->dark_times_file);

    PlayMusicStream(gs->bg_music);
}

void unloadGameState(GameState *gs)
{
    // Unload Textures
    UnloadTexture(gs->maze.cell_texture);
    UnloadTexture(gs->maze.crossed_cell_texture);
    UnloadTexture(gs->player.player_texture);

    // Unload Sprites
    for (int i = 0; i <= 11; i++)
    {
        UnloadTexture(gs->player.player_sprite_idle[i]);
        UnloadTexture(gs->player.player_sprite_attacking[i]);
        UnloadTexture(gs->player.player_sprite_dying[i]);
    }

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

    // Unload Buttons
    UnloadTexture(gs->music_on_btn);
    UnloadTexture(gs->music_hovered_btn);
    UnloadTexture(gs->music_off_btn);
    UnloadTexture(gs->settings_btn);
    UnloadTexture(gs->settings_hovered_btn);
    UnloadTexture(gs->info_btn);
    UnloadTexture(gs->info_hovered_btn);
    UnloadTexture(gs->menu_btn);
    UnloadTexture(gs->menu_hovered_btn);

    // Unload Mode Selction Buttons
    UnloadTexture(gs->best_of_us_btn);
    UnloadTexture(gs->multiverse_btn);
    UnloadTexture(gs->dark_night_btn);
    UnloadTexture(gs->infinity_war_btn);
    UnloadTexture(gs->time_runs_out_btn);
    UnloadTexture(gs->gravity_grave_btn);
    UnloadTexture(gs->endgame_btn);

    // Store Best Times of THE BEST OF US in external file
    gs->best_times_file = fopen("scores/Best_Times.txt", "w");
    for (int i = 0; i < 10; i++)
        fprintf(gs->best_times_file, "%f %s\n", gs->best_times[i].time, gs->best_times[i].player_name);
    fclose(gs->best_times_file);

    // Store High Scores of THE MULTIVERSE OF MADMAZE file
    gs->high_scores_file = fopen("scores/High_Scores.txt", "w");
    for (int i = 0; i < 10; i++)
        fprintf(gs->high_scores_file, "%d %s\n", gs->high_scores[i].score, gs->high_scores[i].player_name);
    fclose(gs->high_scores_file);

    // Store Dark Times for THE DARK NIGHT
    gs->dark_times_file = fopen("scores/Dark_Nights.txt", "w");
    for (int i = 0; i < 10; i++)
        fprintf(gs->dark_times_file, "%f %s\n", gs->dark_times[i].time, gs->dark_times[i].player_name);
    fclose(gs->dark_times_file);

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
    const char *title = "A MAZE ING";
    Vector2 title_pos = {(SCREENWIDTH - MeasureText(title, 100)) / 2, 15};
    drawText(gs->title_font, title, title_pos, 100, 1, WHITE, 80);

    // PLAY BUTTON
    Button play_btn = {(Rectangle){SCREENWIDTH * (2.0 / 5), 250, SCREENWIDTH / 5, 35},
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
    Button credit_btn = {(Rectangle){SCREENWIDTH * (2.0 / 5), 250 + 50, SCREENWIDTH / 5, 35},
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

    // LEADERBOARD BUTTON
    const char *leaderboard_btn_text = "LEADERBOARD   ";

    Button leaderboard_btn = {(Rectangle){SCREENWIDTH * (2.0 / 5), 250 + 50 * 2, SCREENWIDTH / 5, 35},
                              GetColor(0x00f0ffff),
                              .stroke = 0, WHITE, leaderboard_btn_text, gs->btn_font, BLACK, 25, 1, 80};
    drawButton(leaderboard_btn);
    if (hovered(leaderboard_btn))
    {
        leaderboard_btn.buttonColor = BLUE;
        leaderboard_btn.textColor = WHITE;
        drawButton(leaderboard_btn);
    }
    if (clicked(leaderboard_btn))
    {
        PlaySound(gs->click_sound1);
        if (gs->mode == BEST_OF_US)
            gs->page = BEST_TIMES;
        else if (gs->mode == MULTIVERSE)
            gs->page = HIGH_SCORES;
    }

    // QUIT BUTTON
    Button quit_btn = {(Rectangle){SCREENWIDTH * (2.0 / 5), 250 + 50 * 3, SCREENWIDTH / 5, 35},
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

    // Mode Selection Buttons

    // THE BEST OF US
    Rectangle best_of_us_mode_btn = {50, 600, 220, 140};

    DrawTexturePro(gs->best_of_us_btn, (Rectangle){0, 0, gs->best_of_us_btn.width, gs->best_of_us_btn.height}, best_of_us_mode_btn, Vector2Zero(), 0, WHITE);

    if (clickedRec(best_of_us_mode_btn))
    {
        srand(52);
        PlaySound(gs->click_sound1);
        gs->mode = BEST_OF_US;
    }

    // THE MULTIVERSE OF MADMAZE
    Rectangle multiverse_mode_btn = {50 + 220 + 50, 600, 220, 140};

    DrawTexturePro(gs->multiverse_btn, (Rectangle){0, 0, gs->multiverse_btn.width, gs->multiverse_btn.height}, multiverse_mode_btn, Vector2Zero(), 0, WHITE);

    if (clickedRec(multiverse_mode_btn))
    {
        PlaySound(gs->click_sound1);
        gs->mode = MULTIVERSE;
        gs->level = 1;
    }

    // TIME RUNS OUT
    Rectangle time_runs_out_mode_btn = {50 + 220 * 2 + 50 * 2, 600, 220, 140};

    DrawTexturePro(gs->time_runs_out_btn, (Rectangle){0, 0, gs->time_runs_out_btn.width, gs->time_runs_out_btn.height}, time_runs_out_mode_btn, Vector2Zero(), 0, WHITE);

    if (clickedRec(time_runs_out_mode_btn))
    {
        PlaySound(gs->click_sound1);
        gs->mode = TIME_RUNS_OUT;
    }

    // THE DARK NIGHT
    Rectangle dark_night_mode_btn = {50 + 220 * 3 + 50 * 3, 600, 220, 140};

    DrawTexturePro(gs->dark_night_btn, (Rectangle){0, 0, gs->dark_night_btn.width, gs->dark_night_btn.height}, dark_night_mode_btn, Vector2Zero(), 0, WHITE);

    if (clickedRec(dark_night_mode_btn))
    {
        PlaySound(gs->click_sound1);
        gs->mode = DARK_NIGHT;
    }

    // INFINITY WAR
    Rectangle infinity_war_mode_btn = {50 + 220 * 4 + 50 * 4, 600, 220, 140};

    DrawTexturePro(gs->infinity_war_btn, (Rectangle){0, 0, gs->infinity_war_btn.width, gs->infinity_war_btn.height}, infinity_war_mode_btn, Vector2Zero(), 0, WHITE);

    if (clickedRec(infinity_war_mode_btn))
    {
        PlaySound(gs->click_sound1);
        gs->mode = INFINITY_WAR;
    }

    // Selected Mode Pointer
    int i;
    if (gs->mode == BEST_OF_US)
        i = 0;
    else if (gs->mode == MULTIVERSE)
        i = 1;
    else if (gs->mode == TIME_RUNS_OUT)
        i = 2;
    else if (gs->mode == DARK_NIGHT)
        i = 3;
    else if (gs->mode == INFINITY_WAR)
        i = 4;

    Vector2 v1 = {50 + 110 + (50 + 220) * i, 600 + 150};
    Vector2 v2 = {v1.x - 10, v1.y + 15};
    Vector2 v3 = {v1.x + 10, v1.y + 15};

    DrawTriangle(v1, v2, v3, WHITE);

    // Sprite Animation
    Texture2D menu_sprite1 = gs->player.player_sprite_attacking[gs->player.sprite_index];
    DrawTexturePro(menu_sprite1, (Rectangle){0, 0, menu_sprite1.width, menu_sprite1.height},
                   (Rectangle){80, 200, 300, 300}, Vector2Zero(), 0, WHITE);

    Texture2D menu_sprite2 = gs->player.player_sprite_dying[gs->player.sprite_index];
    DrawTexturePro(menu_sprite2, (Rectangle){0, 0, -menu_sprite2.width, menu_sprite2.height},
                   (Rectangle){1000, 200, 300, 300}, Vector2Zero(), 0, WHITE);

    // MUSIC BUTTON
    Rectangle music_btn_rec = {SCREENWIDTH - 40 * 3, 20, 20, 20};

    Texture2D music_btn = hoveredRec(music_btn_rec) ? gs->music_hovered_btn : (gs->music_on ? gs->music_on_btn : gs->music_off_btn);

    DrawTexturePro(music_btn, (Rectangle){0, 0, gs->music_on_btn.width, gs->music_on_btn.height}, music_btn_rec, Vector2Zero(), 0, WHITE);

    if (clickedRec(music_btn_rec))
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

    // INFO BUTTON
    Rectangle info_btn_rec = {SCREENWIDTH - 40 * 2, 20, 20, 20};

    Texture2D info_btn = hoveredRec(info_btn_rec) ? gs->info_hovered_btn : gs->info_btn;

    DrawTexturePro(info_btn, (Rectangle){0, 0, gs->info_btn.width, gs->info_btn.height}, info_btn_rec, Vector2Zero(), 0, WHITE);

    if (clickedRec(info_btn_rec))
    {
        PlaySound(gs->click_sound1);
        gs->page = INFO;
    }

    // SETTINGS BUTTON
    Rectangle settings_btn_rec = {SCREENWIDTH - 40, 20, 20, 20};

    Texture2D settings_btn = hoveredRec(settings_btn_rec) ? gs->settings_hovered_btn : gs->settings_btn;

    DrawTexturePro(settings_btn, (Rectangle){0, 0, gs->settings_btn.width, gs->settings_btn.height}, settings_btn_rec, Vector2Zero(), 0, WHITE);

    if (clickedRec(settings_btn_rec))
    {
        PlaySound(gs->click_sound1);
        gs->page = SETTINGS;
    }

    // Change Mouse Cursor
    if (hovered(play_btn) || hovered(credit_btn) || hovered(leaderboard_btn) || hovered(quit_btn) || hoveredRec(best_of_us_mode_btn) || hoveredRec(multiverse_mode_btn) || hoveredRec(dark_night_mode_btn) || hoveredRec(time_runs_out_mode_btn) || hoveredRec(infinity_war_mode_btn) || hoveredRec(music_btn_rec) || hoveredRec(info_btn_rec) || hoveredRec(settings_btn_rec))
    {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
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
                                      (letter >= 'a' && letter <= 'z')) ||
            letter == ' ' || letter == '.')
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
}

void drawNameInput(GameState *gs)
{
    BeginDrawing();
    ClearBackground(GetColor(0xfff4d6ff));

    const char *instruct = "ENTER YOUR NAME";
    DrawTextEx(gs->font1, instruct, (Vector2){(SCREENWIDTH - MeasureText(instruct, 30)) / 2.0, SCREENHEIGHT / 2.0 - 150}, 30, 1, BLACK);

    Card input_card = {(Rectangle){SCREENWIDTH * (1.0 / 5), SCREENHEIGHT * (1.0 / 2) - 100, SCREENWIDTH * (3.0 / 5), 100},
                       GetColor(0x263baaff),
                       0, WHITE, gs->name, gs->font1, GetColor(0xfff4d6ff), 80, 1, 10, 80, 5, 5};
    drawCard(input_card);

    // MENU BUTTON
    Rectangle menu_btn_rec = {20, 20, 20, 20};
    Texture menu_btn = hoveredRec(menu_btn_rec) ? gs->menu_hovered_btn : gs->menu_btn;
    DrawTexturePro(menu_btn, (Rectangle){0, 0, menu_btn.width, menu_btn.height}, menu_btn_rec, Vector2Zero(), 0, WHITE);

    if (clickedRec(menu_btn_rec))
    {
        PlaySound(gs->click_sound1);
        gs->page = MENU;
    }

    // ENTER button
    Button enter_btn = {(Rectangle){(SCREENWIDTH - 100) / 2, SCREENHEIGHT / 2.0 + 20, 100, 40}, GetColor(0x2e2e2eff), 0, RAYWHITE, "ENTER", gs->btn_font, WHITE, 20, 1, 0};

    if (gs->letter_count)
    {
        drawButton(enter_btn);

        if (hovered(enter_btn))
        {
            enter_btn.buttonColor = BLACK;
            enter_btn.textColor = WHITE;
            drawButton(enter_btn);
        }

        if (clicked(enter_btn) || IsKeyPressed(KEY_ENTER))
        {
            PlaySound(gs->click_sound1);

            if (gs->mode == BEST_OF_US || gs->mode == DARK_NIGHT)
            {
                gs->page = PLAYING;
                gs->start_time = GetTime();
                initGameplay(gs);
            }
            else if (gs->mode == MULTIVERSE)
            {
                gs->page = LEVELS;
                gs->last_score = 0;
            }
        }
    }

    if (hoveredRec(menu_btn_rec) || hovered(enter_btn))
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    else
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);

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
    Rectangle menu_btn_rec = {20, 20, 20, 20};
    Texture menu_btn = hoveredRec(menu_btn_rec) ? gs->menu_hovered_btn : gs->menu_btn;
    DrawTexturePro(menu_btn, (Rectangle){0, 0, menu_btn.width, menu_btn.height}, menu_btn_rec, Vector2Zero(), 0, WHITE);

    if (clickedRec(menu_btn_rec) || IsKeyPressed(KEY_BACKSPACE))
    {
        PlaySound(gs->click_sound1);
        gs->page = MENU;
    }

    // Change Mouse Cursor
    if (hoveredRec(menu_btn_rec))
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    else
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);

    EndDrawing();
}

void drawInfo(GameState *gs)
{
    BeginDrawing();
    ClearBackground(GetColor(0x2e2e2eff));

    // MENU BUTTON
    Rectangle menu_btn_rec = {20, 20, 20, 20};
    Texture menu_btn = hoveredRec(menu_btn_rec) ? gs->menu_hovered_btn : gs->menu_btn;
    DrawTexturePro(menu_btn, (Rectangle){0, 0, menu_btn.width, menu_btn.height}, menu_btn_rec, Vector2Zero(), 0, WHITE);

    if (clickedRec(menu_btn_rec))
    {
        PlaySound(gs->click_sound1);
        gs->page = MENU;
    }

    EndDrawing();
}

void drawSettings(GameState *gs)
{
    BeginDrawing();
    ClearBackground(GetColor(0x2e2e2eff));

    // MENU BUTTON
    Rectangle menu_btn_rec = {20, 20, 20, 20};
    Texture menu_btn = hoveredRec(menu_btn_rec) ? gs->menu_hovered_btn : gs->menu_btn;
    DrawTexturePro(menu_btn, (Rectangle){0, 0, menu_btn.width, menu_btn.height}, menu_btn_rec, Vector2Zero(), 0, WHITE);

    if (clickedRec(menu_btn_rec))
    {
        PlaySound(gs->click_sound1);
        gs->page = MENU;
    }

    EndDrawing();
}

void drawBestTimes(GameState *gs)
{

    BeginDrawing();
    ClearBackground(GetColor(0xdff7ffff));

    if(gs->mode == BEST_OF_US)
    for (int i = 0; i < 10; i++)
    {
        // Player Name
        Rectangle player_name_rec = {200, (SCREENHEIGHT - 500) / 2 + 60 * i, 450, 45};
        Card player_name_card = {player_name_rec, GetColor(0xffe2b8ff), 0, WHITE, TextFormat("\n%s", gs->best_times[i].player_name), gs->btn_font, GetColor(0x053d3aff), 25, 1, -15, 80, -5, 5};
        drawCard(player_name_card);

        // Best Time
        Rectangle best_times_rec = {700, (SCREENHEIGHT - 500) / 2 + 60 * i, 450, 45};
        const char *best_time_text = formatTime(gs->best_times[i].time);
        Card best_times_card = {best_times_rec, GetColor(0x053d3aff), 0, WHITE, TextFormat("\n%s", best_time_text), gs->btn_font, GetColor(0xffe2b8ff), 25, 1, -17, 80, 5, 5};
        drawCard(best_times_card);
    }

    else if(gs->mode == DARK_NIGHT) // not done
    for (int i = 0; i < 10; i++)
    {
        // Player Name
        Rectangle player_name_rec = {200, (SCREENHEIGHT - 500) / 2 + 60 * i, 450, 45};
        Card player_name_card = {player_name_rec, GetColor(0xffe2b8ff), 0, WHITE, TextFormat("\n%s", gs->best_times[i].player_name), gs->btn_font, GetColor(0x053d3aff), 25, 1, -15, 80, -5, 5};
        drawCard(player_name_card);

        // Best Time
        Rectangle best_times_rec = {700, (SCREENHEIGHT - 500) / 2 + 60 * i, 450, 45};
        const char *best_time_text = formatTime(gs->best_times[i].time);
        Card best_times_card = {best_times_rec, GetColor(0x053d3aff), 0, WHITE, TextFormat("\n%s", best_time_text), gs->btn_font, GetColor(0xffe2b8ff), 25, 1, -17, 80, 5, 5};
        drawCard(best_times_card);
    }


    // MENU BUTTON
    // MENU BUTTON
    Rectangle menu_btn_rec = {20, 20, 20, 20};
    Texture menu_btn = hoveredRec(menu_btn_rec) ? gs->menu_hovered_btn : gs->menu_btn;
    DrawTexturePro(menu_btn, (Rectangle){0, 0, menu_btn.width, menu_btn.height}, menu_btn_rec, Vector2Zero(), 0, WHITE);

    if (clickedRec(menu_btn_rec) || IsKeyPressed(KEY_BACKSPACE))
    {
        PlaySound(gs->click_sound1);
        gs->page = MENU;
    }

    // NUKE BUTTON
    Button nuke_btn = {(Rectangle){SCREENWIDTH - 10 - 100, 10, 100, 40}, DARKBLUE,
                       0, WHITE,
                       "NUKE", gs->btn_font, RAYWHITE, 20, 1, 0};
    drawButton(nuke_btn);
    if (hovered(nuke_btn))
    {
        nuke_btn.buttonColor = BLUE;
        nuke_btn.shadow_opacity = 80;
        drawButton(nuke_btn);
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    }
    else
    {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    if (clicked(nuke_btn) || IsKeyPressed(KEY_BACKSPACE))
    {
        PlaySound(gs->click_sound1);
        nukeBestTimes(gs->best_times);
    }

    EndDrawing();
}

void drawHighScores(GameState *gs)
{
    BeginDrawing();
    ClearBackground(GetColor(0xdff7ffff));

    for (int i = 0; i < 10; i++)
    {
        // Player Name
        Rectangle player_name_rec = {200, (SCREENHEIGHT - 500) / 2 + 60 * i, 450, 45};
        Card player_name_card = {player_name_rec, GetColor(0xffe2b8ff), 0, WHITE, TextFormat("\n%s", gs->high_scores[i].player_name), gs->btn_font, GetColor(0x053d3aff), 25, 1, -15, 80, -5, 5};
        drawCard(player_name_card);

        // Best Time
        Rectangle best_times_rec = {700, (SCREENHEIGHT - 500) / 2 + 60 * i, 450, 45};
        const char *best_time_text = TextFormat("%03d", gs->high_scores[i].score);
        Card best_times_card = {best_times_rec, GetColor(0x053d3aff), 0, WHITE, TextFormat("\n%s", best_time_text), gs->btn_font, GetColor(0xffe2b8ff), 25, 1, -17, 80, 5, 5};
        drawCard(best_times_card);
    }

    // MENU BUTTON
    Rectangle menu_btn_rec = {20, 20, 20, 20};
    Texture menu_btn = hoveredRec(menu_btn_rec) ? gs->menu_hovered_btn : gs->menu_btn;
    DrawTexturePro(menu_btn, (Rectangle){0, 0, menu_btn.width, menu_btn.height}, menu_btn_rec, Vector2Zero(), 0, WHITE);

    if (clickedRec(menu_btn_rec) || IsKeyPressed(KEY_BACKSPACE))
    {
        PlaySound(gs->click_sound1);
        gs->page = MENU;
    }

    // NUKE BUTTON
    Button nuke_btn = {(Rectangle){SCREENWIDTH - 10 - 100, 10, 100, 40}, DARKBLUE,
                       0, WHITE,
                       "NUKE", gs->btn_font, RAYWHITE, 20, 1, 0};
    drawButton(nuke_btn);
    if (hovered(nuke_btn))
    {
        nuke_btn.buttonColor = BLUE;
        nuke_btn.shadow_opacity = 80;
        drawButton(nuke_btn);
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    }
    else
    {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    if (clicked(nuke_btn) || IsKeyPressed(KEY_BACKSPACE))
    {
        PlaySound(gs->click_sound1);
        nukeHighScores(gs->high_scores);
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
    Rectangle menu_btn_rec = {20, 20, 20, 20};
    Texture menu_btn = hoveredRec(menu_btn_rec) ? gs->menu_hovered_btn : gs->menu_btn;
    DrawTexturePro(menu_btn, (Rectangle){0, 0, menu_btn.width, menu_btn.height}, menu_btn_rec, Vector2Zero(), 0, WHITE);

    if (clickedRec(menu_btn_rec) || IsKeyPressed(KEY_BACKSPACE))
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

    if (gs->mode == BEST_OF_US || gs->mode == DARK_NIGHT)
        gs->level = 0;
    else if (gs->mode == MULTIVERSE)
        srand(4 + 19);

    initializeMaze(&gs->maze, gs->level);
    generateMaze(&gs->maze);
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
    if (IsKeyPressed(KEY_SPACE) && gs->mode == BEST_OF_US)
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
        if (gs->mode == BEST_OF_US )
        {
            addTime(gs);
            gs->page = GAME_FINISH;
        }
        else if (gs->mode == MULTIVERSE)
        {
            gs->last_score += gs->maze.height * gs->maze.width * 5;
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
        else if (gs->mode == DARK_NIGHT )
        {
            addDarkTime(gs);
            gs->page = GAME_FINISH;
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
    if (gs->mode == DARK_NIGHT)
        drawDark(gs);

    // TITLE
    const char *title;
    if (gs->mode == BEST_OF_US)
    {
        title = "THE BEST OF US";
        const char *control_inst = "W/A/S/D or Arrow Keys for Movement | Space for New Maze | F for Auto Solve";
        DrawTextEx(gs->font1, control_inst, (Vector2){(SCREENWIDTH - MeasureText(control_inst, 20)) / 2, 70}, 20, 1, GRAY);
    }
    else if (gs->mode == MULTIVERSE)
    {
        title = "THE MULTIVERSE OF MADMAZE";
        const char *control_inst = "W/A/S/D or Arrow Keys for Movement | F for Auto Solve";
        DrawTextEx(gs->font1, control_inst, (Vector2){(SCREENWIDTH - MeasureText(control_inst, 20)) / 2, 70}, 20, 1, GRAY);
    }
    else if (gs->mode == DARK_NIGHT)
    {
        title = "DARK NIGHT";
        const char *control_inst = "W/A/S/D or Arrow Keys for Movement | Space for New Maze | F for Auto Solve";
        DrawTextEx(gs->font1, control_inst, (Vector2){(SCREENWIDTH - MeasureText(control_inst, 20)) / 2, 70}, 20, 1, GRAY);
    }
    DrawTextEx(gs->title_font, title, (Vector2){(SCREENWIDTH - MeasureText(title, 50)) / 2, 20}, 50, 1, WHITE);

    // MENU BUTTON
    Rectangle menu_btn_rec = {20, 20, 20, 20};
    Texture menu_btn = hoveredRec(menu_btn_rec) ? gs->menu_hovered_btn : gs->menu_btn;
    DrawTexturePro(menu_btn, (Rectangle){0, 0, menu_btn.width, menu_btn.height}, menu_btn_rec, Vector2Zero(), 0, WHITE);

    if (clickedRec(menu_btn_rec))
    {
        PlaySound(gs->click_sound1);
        gs->page = MENU;
    }

    // Change Mouse Cursor
    if (hoveredRec(menu_btn_rec))
    {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    }
    else
    {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    if (IsKeyPressed(KEY_BACKSPACE))
    {
        if (gs->mode == BEST_OF_US)
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

    if (gs->mode == BEST_OF_US || gs->mode == DARK_NIGHT)
    {
        // Time sector
        const char *time_text = formatTime(current_time);
        DrawTextEx(gs->btn_font, time_text, (Vector2){1250, 15}, 20, 1, WHITE);
    }
    else if (gs->mode == MULTIVERSE)
    {
        // Level
        DrawTextEx(gs->btn_font, TextFormat("LEVEL: %d", gs->level), (Vector2){1200, 15}, 20, 1, WHITE);

        // Score
        DrawTextEx(gs->btn_font, TextFormat("SCORE: %5d", gs->last_score), (Vector2){1175, 45}, 20, 1, WHITE);

        // FINISH BUTTON
        Button finish_btn = {(Rectangle){SCREENWIDTH - 20 - 100, SCREENHEIGHT - 20 - 40, 100, 40}, DARKBLUE,
                             0, WHITE,
                             "FINISH", gs->btn_font, RAYWHITE, 20, 1, 0};
        drawButton(finish_btn);
        if (hovered(finish_btn))
        {
            finish_btn.buttonColor = BLUE;
            finish_btn.shadow_opacity = 80;
            drawButton(finish_btn);
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        }
        else
        {
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }

        if (clicked(finish_btn))
        {
            PlaySound(gs->click_sound1);
            addScore(gs);
            gs->page = GAME_FINISH;
        }
    }

    EndDrawing();
}

void drawDark(GameState *gs)
{
    Vector2 pos = {(SCREENWIDTH - gs->maze.width * gs->maze.cell_size) / 2,
                   (SCREENHEIGHT - gs->maze.height * gs->maze.cell_size) / 2 + gs->maze.cell_size};
    for (int y = 0; y < gs->maze.height; y++)
    {
        float startx = pos.x;
        int range = 5;
        for (int x = 0; x < gs->maze.width; x++)
        {
            int distance2 = (x - gs->player.x) * (x - gs->player.x) + (y - gs->player.y) * (y - gs->player.y);
            //if (!(x == gs->maze.width - 1 && y == gs->maze.height - 1) && (distance2 > range * range))
            if(!(x == gs->maze.width - 1 && y == gs->maze.height - 1) && (((x-gs->player.x)<-range || (x-gs->player.x)>range) || ((y-gs->player.y)<-range || (y-gs->player.y)>range)))
            {
                DrawRectangle(pos.x, pos.y, gs->maze.cell_size, gs->maze.cell_size, BLACK);
            }

            pos.x += gs->maze.cell_size;
        }
        pos.x = startx;
        pos.y += gs->maze.cell_size;
    }
}

void drawTime(GameState *gs)
{
    BeginDrawing();
    ClearBackground(GetColor(0xddfbefff));

    // MENU BUTTON
    Rectangle menu_btn_rec = {20, 20, 20, 20};
    Texture menu_btn = hoveredRec(menu_btn_rec) ? gs->menu_hovered_btn : gs->menu_btn;
    DrawTexturePro(menu_btn, (Rectangle){0, 0, menu_btn.width, menu_btn.height}, menu_btn_rec, Vector2Zero(), 0, WHITE);

    if (clickedRec(menu_btn_rec) || IsKeyPressed(KEY_BACKSPACE))
    {
        PlaySound(gs->click_sound1);
        gs->page = MENU;
    }

    // Time Card
    const char *time_card_text = TextFormat("%3s\n%s", gs->name, formatTime(gs->last_time));
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

void drawScore(GameState *gs)
{
    BeginDrawing();
    ClearBackground(GetColor(0xddfbefff));

    // MENU BUTTON
    Rectangle menu_btn_rec = {20, 20, 20, 20};
    Texture menu_btn = hoveredRec(menu_btn_rec) ? gs->menu_hovered_btn : gs->menu_btn;
    DrawTexturePro(menu_btn, (Rectangle){0, 0, menu_btn.width, menu_btn.height}, menu_btn_rec, Vector2Zero(), 0, WHITE);

    if (clickedRec(menu_btn_rec) || IsKeyPressed(KEY_BACKSPACE))
    {
        PlaySound(gs->click_sound1);
        gs->page = MENU;
    }

    // Score Card
    const char *score_card_text = TextFormat("%2s\n%d", gs->name, gs->last_score);
    Card score_card = {(Rectangle){SCREENWIDTH * (2.0 / 5), SCREENHEIGHT / 2 - 100, SCREENWIDTH * (1.0 / 5), 100}, GetColor(0x2f4858ff), 0, BLACK, score_card_text, gs->font1, WHITE, 40, 1, 10, 80, 10, 10};

    drawCard(score_card);

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
        gs->last_score = 0;
        gs->page = LEVELS;
        initGameplay(gs);
        gs->start_time = GetTime();
    }

    drawButton(replay_btn);

    EndDrawing();
}

void addTime(GameState *gs)
{
    strcpy(gs->best_times[10].player_name, gs->name);
    gs->best_times[10].time = gs->last_time;
    sortBestTimes(gs->best_times);
}

void addDarkTime(GameState *gs)
{
    strcpy(gs->dark_times[10].player_name, gs->name);
    gs->dark_times[10].time = gs->last_time;
    sortBestTimes(gs->dark_times);
}


void addScore(GameState *gs)
{
    strcpy(gs->high_scores[10].player_name, gs->name);
    gs->high_scores[10].score = gs->last_score;
    sortHighScores(gs->high_scores);
}

void drawMultiConq(GameState *gs)
{
    BeginDrawing();
    ClearBackground(GetColor(0xddfbefff));

    // MENU BUTTON
    Rectangle menu_btn_rec = {20, 20, 20, 20};
    Texture menu_btn = hoveredRec(menu_btn_rec) ? gs->menu_hovered_btn : gs->menu_btn;
    DrawTexturePro(menu_btn, (Rectangle){0, 0, menu_btn.width, menu_btn.height}, menu_btn_rec, Vector2Zero(), 0, WHITE);

    if (clickedRec(menu_btn_rec) || IsKeyPressed(KEY_BACKSPACE))
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
        if (gs->mode == BEST_OF_US)
            drawTime(gs);
        else if (gs->mode == MULTIVERSE)
            drawScore(gs);
        break;

    case MULTIVERSE_CONQUERED:
        drawMultiConq(gs);
        break;

    case CREDIT:
        drawCredit(gs);
        break;

    case INFO:
        drawInfo(gs);
        break;

    case SETTINGS:
        drawSettings(gs);
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