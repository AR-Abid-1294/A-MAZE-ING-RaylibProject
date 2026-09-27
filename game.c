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
    gs->times = gs->best_times_medium;
    gs->scores = gs->high_scores;
    gs->info = HOWTOPLAY;
    gs->algorithm = ALDOUS_BRODER_ALGO;
    gs->maze.difficulty = MEDIUM;
    gs->dev = true;

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
    gs->click_sound = LoadSound("Assets/Sound Effects/click_double_on.wav");
    gs->movement_sound = LoadSound("Assets/Sound Effects/water_drop_synthetic.wav");
    gs->movement_blocked_sound = LoadSound("Assets/Sound Effects/cardboard_hit.wav");
    gs->game_finish_sound = LoadSound("Assets/Sound Effects/xylophone_positive_long.wav");

    // Load Music
    gs->bg_music = LoadMusicStream("Assets/Music/Sakura-Girl-Motivation-chosic.com_.mp3");
    gs->bg_music.looping = true;
    gs->music_on = true;

    // Optimize Volume
    SetMusicVolume(gs->bg_music, 0.3f);
    SetSoundVolume(gs->movement_sound, 2);
    SetSoundVolume(gs->game_finish_sound, 2);
    SetSoundVolume(gs->movement_blocked_sound, 1.5);

    // Load Images
    gs->title_pic = LoadTexture("Assets/Images/Amazeing1.png");
    gs->abid_pic = LoadTexture("Assets/Images/abid.png");
    gs->afif_pic = LoadTexture("Assets/Images/afif.png");

    gs->how_to_play_info = LoadTexture("Assets/Images/how_to_play.png");
    gs->backtracker_info = LoadTexture("Assets/Images/backtracker.png");
    gs->prim_info = LoadTexture("Assets/Images/prim.png");
    gs->aldous_broder_info = LoadTexture("Assets/Images/aldous_broder.png");
    gs->best_of_us_info = LoadTexture("Assets/Images/best_of_us.png");
    gs->multiverse_info = LoadTexture("Assets/Images/multiverse.png");
    gs->dark_night_info = LoadTexture("Assets/Images/dark_night.png");
    gs->infinity_war_info = LoadTexture("Assets/Images/infinity_war.png");
    gs->time_runs_out_info = LoadTexture("Assets/Images/time_runs_out.png");

    gs->resources_pic = LoadTexture("Assets/Images/resources.png");

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
    gs->menu_from_game_btn = LoadTexture("Assets/Buttons/menu_from_game.png");
    gs->menu_hovered_from_game_btn = LoadTexture("Assets/Buttons/menu_hovered_from_game.png");
    gs->finish_btn = LoadTexture("Assets/Buttons/finish.png");
    gs->finish_hovered_btn = LoadTexture("Assets/Buttons/finish_hovered.png");
    gs->nuke_btn = LoadTexture("Assets/Buttons/nuke.png");
    gs->search_btn = LoadTexture("Assets/Buttons/search.png");
    gs->search_hovered_btn = LoadTexture("Assets/Buttons/search_hovered.png");
    gs->square_btn = LoadTexture("Assets/Buttons/square.png");
    gs->square_not_btn = LoadTexture("Assets/Buttons/square_not.png");
    gs->square_on = false;

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

    // Search Name Input
    gs->search_name[0] = '\0';
    gs->search_letter_count = 0;

    // Load Leaderboard Data

    // Best Times for THE BEST OF US
    loadTimes(gs->best_times_easy, "scores/Best_Times_easy.txt");
    loadTimes(gs->best_times_medium, "scores/Best_Times_medium.txt");
    loadTimes(gs->best_times_hard, "scores/Best_Times_hard.txt");

    // High Scores for THE MULTIVERSE OF MADMAZE
    loadScores(gs->high_scores, "scores/High_Scores.txt");

    // Dark Times for the DARK NIGHT
    loadTimes(gs->dark_times_easy, "scores/Dark_Times_easy.txt");
    loadTimes(gs->dark_times_medium, "scores/Dark_Times_medium.txt");
    loadTimes(gs->dark_times_hard, "scores/Dark_Times_hard.txt");

    // High Scores for TIME RUNS OUT
    loadScores(gs->out_scores_easy, "scores/Out_Scores_easy.txt");
    loadScores(gs->out_scores_medium, "scores/Out_Scores_medium.txt");
    loadScores(gs->out_scores_hard, "scores/Out_Scores_hard.txt");

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
    UnloadSound(gs->click_sound);
    UnloadSound(gs->movement_sound);
    UnloadSound(gs->movement_blocked_sound);
    UnloadSound(gs->game_finish_sound);

    // Unload Music
    UnloadMusicStream(gs->bg_music);

    // Unload Images
    UnloadTexture(gs->title_pic);
    UnloadTexture(gs->abid_pic);
    UnloadTexture(gs->afif_pic);

    UnloadTexture(gs->how_to_play_info);
    UnloadTexture(gs->backtracker_info);
    UnloadTexture(gs->prim_info);
    UnloadTexture(gs->aldous_broder_info);
    UnloadTexture(gs->best_of_us_info);
    UnloadTexture(gs->multiverse_info);
    UnloadTexture(gs->dark_night_info);
    UnloadTexture(gs->infinity_war_info);
    UnloadTexture(gs->time_runs_out_info);
    UnloadTexture(gs->resources_pic);

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
    UnloadTexture(gs->menu_from_game_btn);
    UnloadTexture(gs->menu_hovered_from_game_btn);

    UnloadTexture(gs->finish_btn);
    UnloadTexture(gs->finish_hovered_btn);
    UnloadTexture(gs->nuke_btn);
    UnloadTexture(gs->search_btn);
    UnloadTexture(gs->search_hovered_btn);
    UnloadTexture(gs->square_btn);
    UnloadTexture(gs->square_not_btn);

    // Unload Mode Selction Buttons
    UnloadTexture(gs->best_of_us_btn);
    UnloadTexture(gs->multiverse_btn);
    UnloadTexture(gs->dark_night_btn);
    UnloadTexture(gs->infinity_war_btn);
    UnloadTexture(gs->time_runs_out_btn);
    UnloadTexture(gs->gravity_grave_btn);
    UnloadTexture(gs->endgame_btn);

    // Store Leaderboard Data

    // Best Times for THE BEST OF
    storeTimes(gs->best_times_easy, "scores/Best_Times_easy.txt");
    storeTimes(gs->best_times_medium, "scores/Best_Times_medium.txt");
    storeTimes(gs->best_times_hard, "scores/Best_Times_hard.txt");

    // High Scores for THE MULTIVERSE OF MADMAZE
    storeScores(gs->high_scores, "scores/High_Scores.txt");

    // Dark Times for the DARK NIGHT
    storeTimes(gs->dark_times_easy, "scores/Dark_Times_easy.txt");
    storeTimes(gs->dark_times_medium, "scores/Dark_Times_medium.txt");
    storeTimes(gs->dark_times_hard, "scores/Dark_Times_hard.txt");

    // High Scores for TIME RUNS OUT
    storeScores(gs->out_scores_easy, "scores/Out_Scores_easy.txt");
    storeScores(gs->out_scores_medium, "scores/Out_Scores_medium.txt");
    storeScores(gs->out_scores_hard, "scores/Out_Scores_hard.txt");

    destroyMaze(&gs->maze);

    CloseAudioDevice();
    CloseWindow();
}

void updateSettings(GameState *gs)
{
    if (gs->mode == BEST_OF_US)
    {
        if (gs->maze.difficulty == EASY)
            gs->times = gs->best_times_easy;
        else if (gs->maze.difficulty == MEDIUM)
            gs->times = gs->best_times_medium;
        else if (gs->maze.difficulty == HARD)
            gs->times = gs->best_times_hard;
    }

    else if (gs->mode == MULTIVERSE)
    {
        gs->scores = gs->high_scores;
    }

    else if (gs->mode == TIME_RUNS_OUT)
    {
        if (gs->maze.difficulty == EASY)
            gs->scores = gs->out_scores_easy;
        else if (gs->maze.difficulty == MEDIUM)
            gs->scores = gs->out_scores_medium;
        else if (gs->maze.difficulty == HARD)
            gs->scores = gs->out_scores_hard;
    }

    else if (gs->mode == DARK_NIGHT)
    {
        if (gs->maze.difficulty == EASY)
            gs->times = gs->dark_times_easy;
        else if (gs->maze.difficulty == MEDIUM)
            gs->times = gs->dark_times_medium;
        else if (gs->maze.difficulty == HARD)
            gs->times = gs->dark_times_hard;
    }
}

// draw and update different pages

void drawMenu(GameState *gs)
{
    BeginDrawing();
    ClearBackground(GetColor(0x2e2e2eff));

    Rectangle title_rec = {300, 0, 800, 150};
    DrawTexturePro(gs->title_pic, (Rectangle){0, 0, gs->title_pic.width, gs->title_pic.height}, title_rec, Vector2Zero(), 0, WHITE);

    // PLAY BUTTON
    Button play_btn = {(Rectangle){SCREENWIDTH * (2.0 / 5), 250, SCREENWIDTH / 5, 35},
                       GetColor(0x00f0ffff),
                       0, WHITE, "PLAY", gs->btn_font, BLACK, 25, 1, 80};
    if (hovered(play_btn))
    {
        play_btn.buttonColor = BLUE;
        play_btn.textColor = WHITE;
    }
    drawButton(play_btn);
    if (clicked(play_btn) || IsKeyPressed(KEY_ENTER))
    {
        PlaySound(gs->click_sound);
        gs->page = NAME_INPUT;
        gs->name[0] = '\0';
        gs->letter_count = 0;
    }

    // CREDIT BUTTON
    Button credit_btn = {(Rectangle){SCREENWIDTH * (2.0 / 5), 250 + 50, SCREENWIDTH / 5, 35},
                         GetColor(0x00f0ffff),
                         0, WHITE, "CREDITS", gs->btn_font, BLACK, 25, 1, 80};
    if (hovered(credit_btn))
    {
        credit_btn.buttonColor = BLUE;
        credit_btn.textColor = WHITE;
    }
    drawButton(credit_btn);
    if (clicked(credit_btn))
    {
        PlaySound(gs->click_sound);
        gs->page = CREDIT;
    }

    // LEADERBOARD BUTTON
    const char *leaderboard_btn_text = "LEADERBOARD   ";

    Button leaderboard_btn = {(Rectangle){SCREENWIDTH * (2.0 / 5), 250 + 50 * 2, SCREENWIDTH / 5, 35},
                              GetColor(0x00f0ffff),
                              .stroke = 0, WHITE, leaderboard_btn_text, gs->btn_font, BLACK, 25, 1, 80};
    if (hovered(leaderboard_btn))
    {
        leaderboard_btn.buttonColor = BLUE;
        leaderboard_btn.textColor = WHITE;
    }
    drawButton(leaderboard_btn);
    if (clicked(leaderboard_btn))
    {
        PlaySound(gs->click_sound);
        if (gs->mode == BEST_OF_US || gs->mode == DARK_NIGHT)
            gs->page = BEST_TIMES;
        else if (gs->mode == MULTIVERSE || gs->mode == TIME_RUNS_OUT)
            gs->page = HIGH_SCORES;
    }

    // QUIT BUTTON
    Button quit_btn = {(Rectangle){SCREENWIDTH * (2.0 / 5), 250 + 50 * 3, SCREENWIDTH / 5, 35},
                       GetColor(0xff6b5bff),
                       0, WHITE, "QUIT", gs->btn_font, BLACK, 25, 1, 80};
    if (hovered(quit_btn))
    {
        quit_btn.buttonColor = GetColor(0xff0055ff);
        quit_btn.textColor = WHITE;
    }
    drawButton(quit_btn);
    if (clicked(quit_btn))
    {
        PlaySound(gs->click_sound);
        gs->shouldQuit = true;
    }

    // Mode Selection Buttons

    // THE BEST OF US
    Rectangle best_of_us_mode_btn = {50, 600, 220, 140};

    DrawTexturePro(gs->best_of_us_btn, (Rectangle){0, 0, gs->best_of_us_btn.width, gs->best_of_us_btn.height}, best_of_us_mode_btn, Vector2Zero(), 0, WHITE);

    if (clickedRec(best_of_us_mode_btn))
    {
        srand(52);
        PlaySound(gs->click_sound);
        gs->mode = BEST_OF_US;
        gs->times = gs->best_times_medium;
    }

    // THE MULTIVERSE OF MADMAZE
    Rectangle multiverse_mode_btn = {50 + 220 + 50, 600, 220, 140};

    DrawTexturePro(gs->multiverse_btn, (Rectangle){0, 0, gs->multiverse_btn.width, gs->multiverse_btn.height}, multiverse_mode_btn, Vector2Zero(), 0, WHITE);

    if (clickedRec(multiverse_mode_btn))
    {
        PlaySound(gs->click_sound);
        gs->mode = MULTIVERSE;
        gs->scores = gs->high_scores;
        gs->level = 1;
    }

    // TIME RUNS OUT
    Rectangle time_runs_out_mode_btn = {50 + 220 * 2 + 50 * 2, 600, 220, 140};

    DrawTexturePro(gs->time_runs_out_btn, (Rectangle){0, 0, gs->time_runs_out_btn.width, gs->time_runs_out_btn.height}, time_runs_out_mode_btn, Vector2Zero(), 0, WHITE);

    if (clickedRec(time_runs_out_mode_btn))
    {
        PlaySound(gs->click_sound);
        gs->mode = TIME_RUNS_OUT;
        gs->scores = gs->out_scores_medium;
    }

    // THE DARK NIGHT
    Rectangle dark_night_mode_btn = {50 + 220 * 3 + 50 * 3, 600, 220, 140};

    DrawTexturePro(gs->dark_night_btn, (Rectangle){0, 0, gs->dark_night_btn.width, gs->dark_night_btn.height}, dark_night_mode_btn, Vector2Zero(), 0, WHITE);

    if (clickedRec(dark_night_mode_btn))
    {
        PlaySound(gs->click_sound);
        gs->mode = DARK_NIGHT;
        gs->times = gs->dark_times_medium;
    }

    // INFINITY WAR
    Rectangle infinity_war_mode_btn = {50 + 220 * 4 + 50 * 4, 600, 220, 140};

    DrawTexturePro(gs->infinity_war_btn, (Rectangle){0, 0, gs->infinity_war_btn.width, gs->infinity_war_btn.height}, infinity_war_mode_btn, Vector2Zero(), 0, WHITE);

    if (clickedRec(infinity_war_mode_btn))
    {
        PlaySound(gs->click_sound);
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
        PlaySound(gs->click_sound);
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
        PlaySound(gs->click_sound);
        gs->page = INFO;
    }

    // SETTINGS BUTTON
    Rectangle settings_btn_rec = {SCREENWIDTH - 40, 20, 20, 20};

    Texture2D settings_btn = hoveredRec(settings_btn_rec) ? gs->settings_hovered_btn : gs->settings_btn;

    DrawTexturePro(settings_btn, (Rectangle){0, 0, gs->settings_btn.width, gs->settings_btn.height}, settings_btn_rec, Vector2Zero(), 0, WHITE);

    if (clickedRec(settings_btn_rec))
    {
        PlaySound(gs->click_sound);
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
                                      (letter >= 'a' && letter <= 'z') ||
                                      letter == ' ' || letter == '.'))
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
    ClearBackground(GetColor(0x2e2e2eff));

    const char *instruct = "ENTER YOUR NAME";
    DrawTextEx(gs->font1, instruct, (Vector2){(SCREENWIDTH - MeasureText(instruct, 30)) / 2.0, SCREENHEIGHT / 2.0 - 150}, 30, 1, WHITE);

    Card input_card = {(Rectangle){SCREENWIDTH * (1.0 / 5), SCREENHEIGHT * (1.0 / 2) - 100, SCREENWIDTH * (3.0 / 5), 100},
                       GetColor(0xff6b5bff),
                       0, WHITE, gs->name, gs->font1, GetColor(0x2e2e2eff), 80, 1, 10, 80, 5, 5};
    drawCard(input_card);

    // MENU BUTTON
    Rectangle menu_btn_rec = {20, 20, 20, 20};
    Texture menu_btn = hoveredRec(menu_btn_rec) ? gs->menu_hovered_btn : gs->menu_btn;
    DrawTexturePro(menu_btn, (Rectangle){0, 0, menu_btn.width, menu_btn.height}, menu_btn_rec, Vector2Zero(), 0, WHITE);

    if (clickedRec(menu_btn_rec))
    {
        PlaySound(gs->click_sound);
        gs->page = MENU;
    }

    // ENTER button
    Button enter_btn = {(Rectangle){(SCREENWIDTH - 100) / 2, SCREENHEIGHT / 2.0 + 20, 100, 40}, GetColor(0xe7edebff), 0, RAYWHITE, "ENTER ", gs->btn_font, GetColor(0x69a481ff), 20, 1, 0};

    if (gs->letter_count)
    {
        drawButton(enter_btn);

        if (hovered(enter_btn))
        {
            enter_btn.buttonColor = GetColor(0xb7f7d4ff);
            enter_btn.textColor = BLACK;
            drawButton(enter_btn);
        }

        if (clicked(enter_btn) || IsKeyPressed(KEY_ENTER))
        {
            PlaySound(gs->click_sound);
            gs->last_score = 0;

            if (gs->mode == MULTIVERSE)
                gs->page = LEVELS;

            else
            {
                gs->page = PLAYING;
                initGameplay(gs);

                if (gs->mode == TIME_RUNS_OUT)
                {
                    gs->round = 1;
                    gs->time_limit = 120;
                }
            }
        }
    }

    // Change Mouse Cursor
    if (hoveredRec(menu_btn_rec) || (gs->letter_count && hovered(enter_btn)))
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    else
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);

    EndDrawing();
}

void updateSearchNameInput(GameState *gs)
{
    int letter = GetCharPressed();
    while (letter)
    {
        if (gs->search_letter_count < 19 && ((letter >= 'A' && letter <= 'Z') ||
                                             (letter >= 'a' && letter <= 'z') ||
                                             letter == ' ' || letter == '.'))
        {
            gs->search_name[gs->search_letter_count] = (char)letter;
            gs->search_name[gs->search_letter_count + 1] = '\0';
            gs->search_letter_count++;
        }

        letter = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) && gs->search_letter_count)
    {
        gs->search_letter_count--;
        gs->search_name[gs->search_letter_count] = '\0';
    }
}

void drawSearchNameInput(GameState *gs)
{
    BeginDrawing();
    ClearBackground(GetColor(0x2e2e2eff));

    const char *instruct = "  ENTER THE NAME TO SEARCH";
    DrawTextEx(gs->font1, instruct, (Vector2){(SCREENWIDTH - MeasureText(instruct, 30)) / 2.0, SCREENHEIGHT / 2.0 - 150}, 30, 1, WHITE);

    Card input_card = {(Rectangle){SCREENWIDTH * (1.0 / 5), SCREENHEIGHT * (1.0 / 2) - 100, SCREENWIDTH * (3.0 / 5), 100},
                       GetColor(0xff6b5bff),
                       0, WHITE, gs->search_name, gs->font1, GetColor(0x2e2e2eff), 80, 1, 10, 80, 5, 5};
    drawCard(input_card);

    // MENU BUTTON
    Rectangle menu_btn_rec = {20, 20, 20, 20};
    Texture menu_btn = hoveredRec(menu_btn_rec) ? gs->menu_hovered_btn : gs->menu_btn;
    DrawTexturePro(menu_btn, (Rectangle){0, 0, menu_btn.width, menu_btn.height}, menu_btn_rec, Vector2Zero(), 0, WHITE);

    if (clickedRec(menu_btn_rec))
    {
        PlaySound(gs->click_sound);
        gs->page = MENU;
    }

    // ENTER button
    Button enter_btn = {(Rectangle){(SCREENWIDTH - 100) / 2, SCREENHEIGHT / 2.0 + 20, 100, 40}, GetColor(0xe7edebff), 0, RAYWHITE, "ENTER ", gs->btn_font, GetColor(0x69a481ff), 20, 1, 0};

    if (gs->search_letter_count)
    {
        drawButton(enter_btn);

        if (hovered(enter_btn))
        {
            enter_btn.buttonColor = GetColor(0xb7f7d4ff);
            enter_btn.textColor = BLACK;
            drawButton(enter_btn);
        }

        if (clicked(enter_btn) || IsKeyPressed(KEY_ENTER))
        {
            PlaySound(gs->click_sound);
            gs->page = SEARCH_HIGH_SCORES;
        }
    }

    // Change Mouse Cursor
    if (hoveredRec(menu_btn_rec) || (gs->letter_count && hovered(enter_btn)))
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    else
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);

    EndDrawing();
}

void drawCredit(GameState *gs)
{
    BeginDrawing();
    ClearBackground(GetColor(0x2e2e2eff));

    Rectangle developers_rec = {SCREENWIDTH / 2 - 200, SCREENHEIGHT - 100, 200, 40};
    Button developers_button = {developers_rec,
                                (gs->dev) ? GetColor(0xff0055ff) : GetColor(0xff6b5bff),
                                0, GetColor(0x2e2e2eff), "DEVELOPERS ", gs->btn_font,
                                (gs->dev) ? WHITE : BLACK, 20, 1, (gs->dev) ? 50 : 0};

    if (hovered(developers_button))
    {
        developers_button.buttonColor = GetColor(0xff0055ff);
        developers_button.textColor = WHITE;
    }
    if (clicked(developers_button))
    {
        PlaySound(gs->click_sound);
        gs->dev = true;
    }
    drawButton(developers_button);

    Rectangle resources_rec = {SCREENWIDTH / 2, SCREENHEIGHT - 100, 200, 40};
    Button resources_button = {resources_rec,
                               !(gs->dev) ? GetColor(0xff0055ff) : GetColor(0xff6b5bff),
                               0, GetColor(0x2e2e2eff), "RESOURCES ", gs->btn_font,
                               !(gs->dev) ? WHITE : BLACK, 20, 1, !(gs->dev) ? 50 : 0};

    if (hovered(resources_button))
    {
        resources_button.buttonColor = GetColor(0xff0055ff);
        resources_button.textColor = WHITE;
    }
    if (clicked(resources_button))
    {
        PlaySound(gs->click_sound);
        gs->dev = false;
    }
    drawButton(resources_button);

    if (gs->dev)
    {
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
    }
    else
    {
        drawTextureShadowed(gs->resources_pic, (Rectangle){200, SCREENHEIGHT * (1.5 / 10), 1000, 500});
    }

    // MENU BUTTON
    Rectangle menu_btn_rec = {20, 20, 20, 20};
    Texture menu_btn = hoveredRec(menu_btn_rec) ? gs->menu_hovered_btn : gs->menu_btn;
    DrawTexturePro(menu_btn, (Rectangle){0, 0, menu_btn.width, menu_btn.height}, menu_btn_rec, Vector2Zero(), 0, WHITE);

    if (clickedRec(menu_btn_rec) || IsKeyPressed(KEY_BACKSPACE))
    {
        PlaySound(gs->click_sound);
        gs->page = MENU;
    }

    // Change Mouse Cursor
    if (hoveredRec(menu_btn_rec) || hovered(developers_button) || hovered(resources_button))
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

    if (clickedRec(menu_btn_rec) || IsKeyPressed(KEY_BACKSPACE))
    {
        PlaySound(gs->click_sound);
        gs->page = MENU;
    }

    //  MAKING CARD
    Texture info_pic;
    Rectangle info_card_rec = {SCREENWIDTH / 5 + 150, 50, 900, 700};
    // texts
    char text[800];
    switch (gs->info)
    {
    case HOWTOPLAY:
        info_pic = gs->how_to_play_info;
        break;
    case BACKTRACKER:
        info_pic = gs->backtracker_info;
        break;
    case PRIM:
        info_pic = gs->prim_info;
        break;
    case ALDOUSBRODER:
        info_pic = gs->aldous_broder_info;
        break;
    case BESTOFUS:
        info_pic = gs->best_of_us_info;
        break;
    case MULTIVERSEOFMADMAZE:
        info_pic = gs->multiverse_info;
        break;
    case TIMERUNSOUT:
        info_pic = gs->time_runs_out_info;
        break;
    case DARKNIGHT:
        info_pic = gs->dark_night_info;
        break;
    case INFINITYWAR:
        info_pic = gs->infinity_war_info;
        break;
    }
    drawTextureShadowed(info_pic, info_card_rec);
    DrawTexturePro(info_pic, (Rectangle){0, 2, info_pic.width, info_pic.height}, info_card_rec, Vector2Zero(), 0, WHITE);

    // HOW TO PLAY BUTTON
    Button how_to_play_btn = {(Rectangle){70, 60, 300 - 20, 40},
                              (gs->info == HOWTOPLAY) ? GetColor(0xff0055ff) : GetColor(0xff6b5bff),
                              0, (gs->info == HOWTOPLAY) ? WHITE : GetColor(0xff6b5bff), "HOW TO PLAY    ", gs->btn_font, (gs->info == HOWTOPLAY) ? WHITE : BLACK, 25, 1, 80};
    drawButton(how_to_play_btn);
    Card how_to_play_card = {};
    if (hovered(how_to_play_btn))
    {
        how_to_play_btn.buttonColor = GetColor(0xff0055ff);
        how_to_play_btn.textColor = WHITE;
        drawButton(how_to_play_btn);
    }
    if (clicked(how_to_play_btn))
    {
        PlaySound(gs->click_sound);
        gs->info = HOWTOPLAY;
        // card
    }

    // algorithms
    Button algo_btn = {(Rectangle){50, 140, 300, 40},
                       GetColor(0x2e2e2eff),
                       0, WHITE, "ALGORITHMS:    ", gs->btn_font, WHITE, 25, 1, 0};
    drawButton(algo_btn);

    // BACKTRAKER
    Button backtracker_btn = {(Rectangle){70, 200, 300 - 20, 40},
                              (gs->info == BACKTRACKER) ? DARKBLUE : GetColor(0x00f0ffff),
                              0, WHITE, "BACKTRACKER       ", gs->btn_font, (gs->info == BACKTRACKER) ? WHITE : BLACK, 20, 1, 80};
    drawButton(backtracker_btn);
    if (hovered(backtracker_btn))
    {
        backtracker_btn.buttonColor = DARKBLUE;
        backtracker_btn.textColor = WHITE;
        drawButton(backtracker_btn);
    }
    if (clicked(backtracker_btn))
    {
        PlaySound(gs->click_sound);
        gs->info = BACKTRACKER;
        // card
    }

    // PRIM
    Button prim_btn = {(Rectangle){70, 260, 300 - 20, 40},
                       (gs->info == PRIM) ? DARKBLUE : GetColor(0x00f0ffff),
                       0, WHITE, "PRIM                  ", gs->btn_font, (gs->info == PRIM) ? WHITE : BLACK, 20, 1, 80};
    drawButton(prim_btn);
    if (hovered(prim_btn))
    {
        prim_btn.buttonColor = DARKBLUE;
        prim_btn.textColor = WHITE;
        drawButton(prim_btn);
    }
    if (clicked(prim_btn))
    {
        PlaySound(gs->click_sound);
        gs->info = PRIM;
        // card
    }

    // ALDOUS BRODER
    Button aldous_btn = {(Rectangle){70, 320, 300 - 20, 40},
                         (gs->info == ALDOUSBRODER) ? DARKBLUE : GetColor(0x00f0ffff),
                         0, WHITE, "ALDOUS BRODER       ", gs->btn_font, (gs->info == ALDOUSBRODER) ? WHITE : BLACK, 20, 1, 80};
    drawButton(aldous_btn);
    if (hovered(aldous_btn))
    {
        aldous_btn.buttonColor = DARKBLUE;
        aldous_btn.textColor = WHITE;
        drawButton(aldous_btn);
    }
    if (clicked(aldous_btn))
    {
        PlaySound(gs->click_sound);
        gs->info = ALDOUSBRODER;
        // card
    }

    // modes
    Button modes_btn = {(Rectangle){50, 400, 300, 40},
                        GetColor(0x2e2e2eff),
                        0, WHITE, "MODES:         ", gs->btn_font, WHITE, 25, 1, 0};
    drawButton(modes_btn);

    // THE BEST OF US
    Button best_button = {(Rectangle){70, 460, 300 - 20, 40},
                          (gs->info == BESTOFUS) ? DARKBLUE : GetColor(0x00f0ffff),
                          0, WHITE, "THE BEST OF US         ", gs->btn_font, (gs->info == BESTOFUS) ? WHITE : BLACK, 19, 1, 80};
    drawButton(best_button);
    if (hovered(best_button))
    {
        best_button.buttonColor = DARKBLUE;
        best_button.textColor = WHITE;
        drawButton(best_button);
    }
    if (clicked(best_button))
    {
        PlaySound(gs->click_sound);
        gs->info = BESTOFUS;
        // card
    }

    // THE MULTIVERSE OF MADMAZE
    Button multiverse_button = {(Rectangle){70, 520, 300 - 20, 40},
                                (gs->info == MULTIVERSEOFMADMAZE) ? DARKBLUE : GetColor(0x00f0ffff),
                                0, WHITE, "THE MULTIVERSE OF MADMAZE            ", gs->btn_font, (gs->info == MULTIVERSEOFMADMAZE) ? WHITE : BLACK, 13, 1, 80};
    drawButton(multiverse_button);
    if (hovered(multiverse_button))
    {
        multiverse_button.buttonColor = DARKBLUE;
        multiverse_button.textColor = WHITE;
        drawButton(multiverse_button);
    }
    if (clicked(multiverse_button))
    {
        PlaySound(gs->click_sound);
        gs->info = MULTIVERSEOFMADMAZE;
        // card
    }

    // TIME RUNS OUT
    Button out_button = {(Rectangle){70, 580, 300 - 20, 40},
                         (gs->info == TIMERUNSOUT) ? DARKBLUE : GetColor(0x00f0ffff),
                         0, WHITE, "TIME RUNS OUT          ", gs->btn_font, (gs->info == TIMERUNSOUT) ? WHITE : BLACK, 19, 1, 80};
    drawButton(out_button);
    if (hovered(out_button))
    {
        out_button.buttonColor = DARKBLUE;
        out_button.textColor = WHITE;
        drawButton(out_button);
    }
    if (clicked(out_button))
    {
        PlaySound(gs->click_sound);
        gs->info = TIMERUNSOUT;
        // card
    }

    // THE DARK NIGHT
    Button dark_button = {(Rectangle){70, 640, 300 - 20, 40},
                          (gs->info == DARKNIGHT) ? DARKBLUE : GetColor(0x00f0ffff),
                          0, WHITE, "THE DARK NIGHT      ", gs->btn_font, (gs->info == DARKNIGHT) ? WHITE : BLACK, 20, 1, 80};
    drawButton(dark_button);
    if (hovered(dark_button))
    {
        dark_button.buttonColor = DARKBLUE;
        dark_button.textColor = WHITE;
        drawButton(dark_button);
    }
    if (clicked(dark_button))
    {
        PlaySound(gs->click_sound);
        gs->info = DARKNIGHT;
        // card
    }

    // INFINITY WAR
    Button infinity_button = {(Rectangle){70, 700, 300 - 20, 40},
                              (gs->info == INFINITYWAR) ? DARKBLUE : GetColor(0x00f0ffff),
                              0, WHITE, "INFINITY WAR         ", gs->btn_font, (gs->info == INFINITYWAR) ? WHITE : BLACK, 20, 1, 80};
    drawButton(infinity_button);
    if (hovered(infinity_button))
    {
        infinity_button.buttonColor = DARKBLUE;
        infinity_button.textColor = WHITE;
        drawButton(infinity_button);
    }
    if (clicked(infinity_button))
    {
        PlaySound(gs->click_sound);
        gs->info = INFINITYWAR;
        // card
    }

    // Change Mouse Cursor
    if (hoveredRec(menu_btn_rec) || hovered(how_to_play_btn) || hovered(backtracker_btn) || hovered(prim_btn) || hovered(aldous_btn) || hovered(best_button) || hovered(multiverse_button) || hovered(out_button) || hovered(dark_button) || hovered(infinity_button))
    {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    }
    else
    {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
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

    if (clickedRec(menu_btn_rec) || IsKeyPressed(KEY_BACKSPACE))
    {
        PlaySound(gs->click_sound);
        gs->page = MENU;
    }

    // Algorithms
    Button algos_btn = {(Rectangle){SCREENWIDTH / 5, 90, SCREENWIDTH / 5 + 20, 50},
                        GetColor(0xffe2b8ff),
                        0, WHITE, "Algorithms:        ", gs->btn_font, GetColor(0x053d3aff), 25, 1, 80};
    drawButton(algos_btn);

    // backtracker
    Button backtracker_btn = {(Rectangle){SCREENWIDTH / 5 + 10, 160, SCREENWIDTH / 5 + 10, 40},
                              (gs->algorithm == BACKTRACKER_ALGO) ? SKYBLUE : GetColor(0xff6b5bff),
                              0, WHITE, "Backtracker          ", gs->btn_font, WHITE, 23, 1, 80};
    if (clicked(backtracker_btn))
    {
        PlaySound(gs->click_sound);
        generateMaze = generateMaze_backtracker;
        gs->algorithm = BACKTRACKER_ALGO;
    }
    if (hovered(backtracker_btn))
    {
        backtracker_btn.buttonColor = SKYBLUE;
    }
    drawButton(backtracker_btn);

    // prim
    Button prim_btn = {(Rectangle){SCREENWIDTH / 5 + 10, 220, SCREENWIDTH / 5 + 10, 40},
                       (gs->algorithm == PRIM_ALGO) ? SKYBLUE : GetColor(0xff6b5bff),
                       0, WHITE, "Prim                ", gs->btn_font, WHITE, 23, 1, 80};
    if (clicked(prim_btn))
    {
        PlaySound(gs->click_sound);
        generateMaze = generateMaze_prim;
        gs->algorithm = PRIM_ALGO;
    }
    if (hovered(prim_btn))
    {
        prim_btn.buttonColor = SKYBLUE;
    }
    drawButton(prim_btn);

    // aldous broder
    Button aldous_broder_btn = {(Rectangle){SCREENWIDTH / 5 + 10, 280, SCREENWIDTH / 5 + 10, 40},
                                (gs->algorithm == ALDOUS_BRODER_ALGO) ? SKYBLUE : GetColor(0xff6b5bff),
                                0, WHITE, "Aldous Broder        ", gs->btn_font, WHITE, 23, 1, 80};
    if (clicked(aldous_broder_btn))
    {
        PlaySound(gs->click_sound);
        generateMaze = generateMaze_aldous_broder;
        gs->algorithm = ALDOUS_BRODER_ALGO;
    }
    if (hovered(aldous_broder_btn))
    {
        aldous_broder_btn.buttonColor = SKYBLUE;
    }
    drawButton(aldous_broder_btn);

    // difficulty
    Button diff_btn = {(Rectangle){SCREENWIDTH * 3 / 5, 90, SCREENWIDTH / 5 + 20, 50},
                       GetColor(0xffe2b8ff),
                       0, WHITE, "Difficulty:        ", gs->btn_font, GetColor(0x053d3aff), 25, 1, 80};
    drawButton(diff_btn);

    // easy
    Button easy_btn = {(Rectangle){SCREENWIDTH * 3 / 5 + 10, 160, SCREENWIDTH / 5, 40},
                       (gs->maze.difficulty == EASY) ? SKYBLUE : GetColor(0xff6b5bff),
                       0, WHITE, "Easy        ", gs->btn_font, WHITE, 25, 1, 80};
    if (clicked(easy_btn))
    {
        PlaySound(gs->click_sound);
        gs->maze.difficulty = EASY;
    }
    if (hovered(easy_btn))
    {
        easy_btn.buttonColor = SKYBLUE;
    }
    drawButton(easy_btn);

    // medium
    Button medium_btn = {(Rectangle){SCREENWIDTH * 3 / 5 + 10, 220, SCREENWIDTH / 5, 40},
                         (gs->maze.difficulty == MEDIUM) ? SKYBLUE : GetColor(0xff6b5bff),
                         0, WHITE, "Medium       ", gs->btn_font, WHITE, 25, 1, 80};
    if (clicked(medium_btn))
    {
        PlaySound(gs->click_sound);
        gs->maze.difficulty = MEDIUM;
    }
    if (hovered(medium_btn))
    {
        medium_btn.buttonColor = SKYBLUE;
    }
    drawButton(medium_btn);

    // hard
    Button hard_btn = {(Rectangle){SCREENWIDTH * 3 / 5 + 10, 280, SCREENWIDTH / 5, 40},
                       (gs->maze.difficulty == HARD) ? SKYBLUE : GetColor(0xff6b5bff),
                       0, WHITE, "Hard        ", gs->btn_font, WHITE, 25, 1, 80};
    if (clicked(hard_btn))
    {
        PlaySound(gs->click_sound);
        gs->maze.difficulty = HARD;
    }
    if (hovered(hard_btn))
    {
        hard_btn.buttonColor = SKYBLUE;
    }
    drawButton(hard_btn);

    EndDrawing();
}

void drawBestTimes(GameState *gs)
{
    BeginDrawing();
    ClearBackground(GetColor(0x2e2e2eff));

    // TITLE
    const char *title;
    if (gs->mode == BEST_OF_US)
    {
        if (gs->maze.difficulty == EASY)
            title = "THE BEST OF US (EASY)";
        else if (gs->maze.difficulty == MEDIUM)
            title = "THE BEST OF US (MEDIUM)";
        else if (gs->maze.difficulty == HARD)
            title = "THE BEST OF US (HARD)";
    }
    else if (gs->mode == DARK_NIGHT)
    {
        if (gs->maze.difficulty == EASY)
            title = "THE DARK NIGHT (EASY)";
        else if (gs->maze.difficulty == MEDIUM)
            title = "THE DARK NIGHT (MEDIUM)";
        else if (gs->maze.difficulty == HARD)
            title = "THE DARK NIGHT (HARD)";
    }

    DrawTextEx(gs->title_font, title, (Vector2){(SCREENWIDTH - MeasureText(title, 50)) / 2, 20}, 50, 1, WHITE);

    for (int i = 0; i < 10; i++)
    {
        // Player Name
        Rectangle player_name_rec = {200, (SCREENHEIGHT - 500) / 2 + 60 * i, 450, 45};
        Card player_name_card = {player_name_rec, GetColor(0xffe2b8ff), 0, WHITE, TextFormat("\n%s", gs->times[i].player_name), gs->font1, GetColor(0x00000ff), 25, 1, -15, 80, -5, 5};
        drawCard(player_name_card);

        // Best Time
        Rectangle best_times_rec = {700, (SCREENHEIGHT - 500) / 2 + 60 * i, 450, 45};
        const char *best_time_text = formatTime(gs->times[i].time);
        Card best_times_card = {best_times_rec, GetColor(0x053d3aff), 0, WHITE, TextFormat("\n%s", best_time_text), gs->btn_font, GetColor(0xffe2b8ff), 25, 1, -17, 80, 5, 5};
        drawCard(best_times_card);
    }

    // MENU BUTTON
    Rectangle menu_btn_rec = {20, 20, 20, 20};
    Texture menu_btn = hoveredRec(menu_btn_rec) ? gs->menu_hovered_btn : gs->menu_btn;
    DrawTexturePro(menu_btn, (Rectangle){0, 0, menu_btn.width, menu_btn.height}, menu_btn_rec, Vector2Zero(), 0, WHITE);

    if (clickedRec(menu_btn_rec) || IsKeyPressed(KEY_BACKSPACE))
    {
        PlaySound(gs->click_sound);
        gs->page = MENU;
    }

    // SEARCH BUTTON
    Rectangle search_btn_rec = {SCREENWIDTH - 10 - 70, 40, 30, 30};
    DrawTexturePro(gs->search_btn, (Rectangle){0, 0, gs->search_btn.width, gs->search_btn.height}, search_btn_rec, Vector2Zero(), 0, WHITE);

    if (clickedRec(search_btn_rec))
    {
        PlaySound(gs->click_sound);
        gs->page = SEARCH_NAME_INPUT;
        gs->search_name[0] = '\0';
        gs->search_letter_count = 0;
    }
    if (hoveredRec(search_btn_rec))
    {
        DrawTexturePro(gs->search_hovered_btn, (Rectangle){0, 0, gs->search_hovered_btn.width, gs->search_hovered_btn.height}, search_btn_rec, Vector2Zero(), 0, WHITE);
    }

    // NUKE BUTTON
    Rectangle nuke_btn_rec = {SCREENWIDTH - 100, SCREENHEIGHT - 75, 50, 50};
    DrawTexturePro(gs->nuke_btn, (Rectangle){0, 0, gs->nuke_btn.width, gs->nuke_btn.height}, nuke_btn_rec, Vector2Zero(), 0, WHITE);

    if (clickedRec(nuke_btn_rec))
    {
        PlaySound(gs->click_sound);
        nukeBestTimes(gs->times);
    }

    // Change mouse cursor
    if (hoveredRec(menu_btn_rec) || hoveredRec(nuke_btn_rec) || hoveredRec(search_btn_rec))
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    else
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);

    EndDrawing();
}

void drawHighScores(GameState *gs)
{
    BeginDrawing();
    ClearBackground(GetColor(0x2e2e2eff));

    // TITLE
    const char *title;
    if (gs->mode == MULTIVERSE)
    {
        title = "THE MULTIVERSE OF MADMAZE";
    }
    else if (gs->mode == TIME_RUNS_OUT)
    {
        if (gs->maze.difficulty == EASY)
            title = "TIME RUNS OUT (EASY)";
        else if (gs->maze.difficulty == MEDIUM)
            title = "TIME RUNS OUT (MEDIUM)";
        else if (gs->maze.difficulty == HARD)
            title = "TIME RUNS OUT (HARD)";
    }

    DrawTextEx(gs->title_font, title, (Vector2){(SCREENWIDTH - MeasureText(title, 50)) / 2, 20}, 50, 1, WHITE);

    for (int i = 0; i < 10; i++)
    {
        // Player Name
        Rectangle player_name_rec = {200, (SCREENHEIGHT - 500) / 2 + 60 * i, 450, 45};
        Card player_name_card = {player_name_rec, GetColor(0xffe2b8ff), 0, WHITE, TextFormat("\n%s", gs->scores[i].player_name), gs->font1, GetColor(0x053d3aff), 25, 1, -15, 80, -5, 5};
        drawCard(player_name_card);

        // Best Time
        Rectangle best_times_rec = {700, (SCREENHEIGHT - 500) / 2 + 60 * i, 450, 45};
        const char *best_time_text = TextFormat("%03d", gs->scores[i].score);
        Card best_times_card = {best_times_rec, GetColor(0x053d3aff), 0, WHITE, TextFormat("\n%s", best_time_text), gs->btn_font, GetColor(0xffe2b8ff), 25, 1, -17, 80, 5, 5};
        drawCard(best_times_card);
    }

    // MENU BUTTON
    Rectangle menu_btn_rec = {20, 20, 20, 20};
    Texture menu_btn = hoveredRec(menu_btn_rec) ? gs->menu_hovered_btn : gs->menu_btn;
    DrawTexturePro(menu_btn, (Rectangle){0, 0, menu_btn.width, menu_btn.height}, menu_btn_rec, Vector2Zero(), 0, WHITE);

    if (clickedRec(menu_btn_rec) || IsKeyPressed(KEY_BACKSPACE))
    {
        PlaySound(gs->click_sound);
        gs->page = MENU;
    }

    // SEARCH BUTTON
    Rectangle search_btn_rec = {SCREENWIDTH - 10 - 70, 40, 30, 30};
    DrawTexturePro(gs->search_btn, (Rectangle){0, 0, gs->search_btn.width, gs->search_btn.height}, search_btn_rec, Vector2Zero(), 0, WHITE);

    if (clickedRec(search_btn_rec))
    {
        PlaySound(gs->click_sound);
        gs->page = SEARCH_NAME_INPUT;
        gs->search_name[0] = '\0';
        gs->search_letter_count = 0;
    }
    if (hoveredRec(search_btn_rec))
    {
        DrawTexturePro(gs->search_hovered_btn, (Rectangle){0, 0, gs->search_hovered_btn.width, gs->search_hovered_btn.height}, search_btn_rec, Vector2Zero(), 0, WHITE);
    }

    // NUKE BUTTON
    Rectangle nuke_btn_rec = {SCREENWIDTH - 100, SCREENHEIGHT - 75, 50, 50};
    DrawTexturePro(gs->nuke_btn, (Rectangle){0, 0, gs->nuke_btn.width, gs->nuke_btn.height}, nuke_btn_rec, Vector2Zero(), 0, WHITE);

    if (clickedRec(nuke_btn_rec))
    {
        PlaySound(gs->click_sound);
        nukeHighScores(gs->scores);
    }

    // Change mouse cursor
    if (hoveredRec(menu_btn_rec) || hoveredRec(nuke_btn_rec) || hoveredRec(search_btn_rec))
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    else
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);

    EndDrawing();
}

void drawSearchBestTimes(GameState *gs)
{
    BeginDrawing();
    ClearBackground(GetColor(0x2e2e2eff));

    // TITLE
    const char *title;
    if (gs->mode == BEST_OF_US)
    {
        if (gs->maze.difficulty == EASY)
            title = "THE BEST OF US (EASY)";
        else if (gs->maze.difficulty == MEDIUM)
            title = "THE BEST OF US (MEDIUM)";
        else if (gs->maze.difficulty == HARD)
            title = "THE BEST OF US (HARD)";
    }
    else if (gs->mode == DARK_NIGHT)
    {
        if (gs->maze.difficulty == EASY)
            title = "THE DARK NIGHT (EASY)";
        else if (gs->maze.difficulty == MEDIUM)
            title = "THE DARK NIGHT (MEDIUM)";
        else if (gs->maze.difficulty == HARD)
            title = "THE DARK NIGHT (HARD)";
    }

    DrawTextEx(gs->title_font, title, (Vector2){(SCREENWIDTH - MeasureText(title, 50)) / 2, 20}, 50, 1, WHITE);

    for (int i = 0, j = 0; i < 5;)
    {
        if (j < 100)
        {
            if (strcmp(gs->search_name, gs->times[j].player_name))
                j++;
            else
            {
                // player
                Rectangle player_name_rec = {200, (SCREENHEIGHT - 500) / 2 + 60 * i, 450, 45};
                Card player_name_card = {player_name_rec, GetColor(0xffe2b8ff), 0, WHITE, TextFormat("\n%s", gs->times[j].player_name), gs->font1, GetColor(0x053d3aff), 25, 1, -15, 80, -5, 5};
                drawCard(player_name_card);

                // time -> Best Time
                Rectangle best_times_rec = {700, (SCREENHEIGHT - 500) / 2 + 60 * i, 450, 45};
                const char *best_time_text = TextFormat("%03d", gs->times[j].time);
                Card best_times_card = {best_times_rec, GetColor(0x053d3aff), 0, WHITE, TextFormat("\n%s", best_time_text), gs->btn_font, GetColor(0xffe2b8ff), 25, 1, -17, 80, 5, 5};
                drawCard(best_times_card);

                i++;
                j++;
            }
        }
        else
        {
            // player
            Rectangle player_name_rec = {200, (SCREENHEIGHT - 500) / 2 + 60 * i, 450, 45};
            Card player_name_card = {player_name_rec, GetColor(0xffe2b8ff), 0, WHITE, TextFormat("\n%s", gs->search_name), gs->font1, GetColor(0x053d3aff), 25, 1, -15, 80, -5, 5};
            drawCard(player_name_card);

            // time -> Best Time
            Rectangle best_times_rec = {700, (SCREENHEIGHT - 500) / 2 + 60 * i, 450, 45};
            Card best_times_card = {best_times_rec, GetColor(0x053d3aff), 0, WHITE, TextFormat("\n "), gs->btn_font, GetColor(0xffe2b8ff), 25, 1, -17, 80, 5, 5};
            drawCard(best_times_card);

            i++;
        }
    }

    // MENU BUTTON
    Rectangle menu_btn_rec = {20, 20, 20, 20};
    Texture menu_btn = hoveredRec(menu_btn_rec) ? gs->menu_hovered_btn : gs->menu_btn;
    DrawTexturePro(menu_btn, (Rectangle){0, 0, menu_btn.width, menu_btn.height}, menu_btn_rec, Vector2Zero(), 0, WHITE);

    if (clickedRec(menu_btn_rec) || IsKeyPressed(KEY_BACKSPACE))
    {
        PlaySound(gs->click_sound);
        gs->page = MENU;
    }

    EndDrawing();
}

void drawSearchHighScores(GameState *gs)
{
    BeginDrawing();
    ClearBackground(GetColor(0x2e2e2eff));

    // TITLE
    const char *title;
    if (gs->mode == MULTIVERSE)
    {
        title = "THE MULTIVERSE OF MADMAZE";
    }
    else if (gs->mode == TIME_RUNS_OUT)
    {
        if (gs->maze.difficulty == EASY)
            title = "TIME RUNS OUT (EASY)";
        else if (gs->maze.difficulty == MEDIUM)
            title = "TIME RUNS OUT (MEDIUM)";
        else if (gs->maze.difficulty == HARD)
            title = "TIME RUNS OUT (HARD)";
    }
    DrawTextEx(gs->title_font, title, (Vector2){(SCREENWIDTH - MeasureText(title, 50)) / 2, 20}, 50, 1, WHITE);

    int i = 0, j = 0, flag = 0;
    for (; i < 5;)
    {
        if (j < 100)
        {
            if (strcmp(gs->search_name, gs->scores[j].player_name))
                j++;
            else
            {
                // player
                Rectangle player_name_rec = {200, (SCREENHEIGHT - 500) / 2 + 60 * i, 450, 45};
                Card player_name_card = {player_name_rec, GetColor(0xffe2b8ff), 0, WHITE, TextFormat("\n%s", gs->scores[j].player_name), gs->font1, GetColor(0x053d3aff), 25, 1, -15, 80, -5, 5};
                drawCard(player_name_card);

                // score -> Best Time
                Rectangle best_times_rec = {700, (SCREENHEIGHT - 500) / 2 + 60 * i, 450, 45};
                const char *best_time_text = TextFormat("%03d", gs->scores[j].score);
                Card best_times_card = {best_times_rec, GetColor(0x053d3aff), 0, WHITE, TextFormat("\n%s", best_time_text), gs->btn_font, GetColor(0xffe2b8ff), 25, 1, -17, 80, 5, 5};
                drawCard(best_times_card);

                i++;
                j++;
                flag = 1;
            }
        }
        else
        {
            // // player
            // Rectangle player_name_rec = {200, (SCREENHEIGHT - 500) / 2 + 60 * i, 450, 45};
            // Card player_name_card = {player_name_rec, GetColor(0xffe2b8ff), 0, WHITE, TextFormat("\n%s", gs->search_name), gs->font1, GetColor(0x053d3aff), 25, 1, -15, 80, -5, 5};
            // drawCard(player_name_card);

            // // score -> Best Time
            // Rectangle best_times_rec = {700, (SCREENHEIGHT - 500) / 2 + 60 * i, 450, 45};
            // Card best_times_card = {best_times_rec, GetColor(0x053d3aff), 0, WHITE, TextFormat("\n "), gs->btn_font, GetColor(0xffe2b8ff), 25, 1, -17, 80, 5, 5};
            // drawCard(best_times_card);

            i++;
        }
    }
    if (!flag)
    {
        char *not_found = "tomar dara holo nah";
        DrawTextEx(gs->title_font, not_found, (Vector2){(SCREENWIDTH - MeasureText(not_found, 50)) / 2, 20 + 200}, 50, 1, RED);
    }

    // MENU BUTTON
    Rectangle menu_btn_rec = {20, 20, 20, 20};
    Texture menu_btn = hoveredRec(menu_btn_rec) ? gs->menu_hovered_btn : gs->menu_btn;
    DrawTexturePro(menu_btn, (Rectangle){0, 0, menu_btn.width, menu_btn.height}, menu_btn_rec, Vector2Zero(), 0, WHITE);

    if (clickedRec(menu_btn_rec) || IsKeyPressed(KEY_BACKSPACE))
    {
        PlaySound(gs->click_sound);
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
                PlaySound(gs->click_sound);
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
    gs->player.x = 0;
    gs->player.y = 0;

    gs->start_time = GetTime();

    if (gs->mode == MULTIVERSE)
        srand(4 + 19);
    else
    {
        gs->level = 0;
    }

    destroyMaze(&gs->maze);
    initializeMaze(&gs->maze, gs->level);
    generateMaze(&gs->maze);
}

void updateGameplay(GameState *gs)
{

    // Logic Part

    // Movement
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
        if (isCellValid(gs->maze, x, y))
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
    if (IsKeyPressed(KEY_SPACE) && (gs->mode == DARK_NIGHT || gs->mode == INFINITY_WAR))
    {
        PlaySound(gs->click_sound);
        initGameplay(gs);
    }

    // Game Finished
    if (gs->player.x == gs->maze.width - 1 && gs->player.y == gs->maze.height - 1)
    {
        gs->last_time = gs->current_time;
        PlaySound(gs->game_finish_sound);
        if (gs->mode == BEST_OF_US || gs->mode == DARK_NIGHT)
        {
            addTime(gs);
            gs->page = GAME_FINISH;
        }

        else if (gs->mode == MULTIVERSE)
        {
            gs->last_score += gs->maze.height * gs->maze.width * 5;

            if (gs->level < 50)
            {
                gs->level++;
                initGameplay(gs);
            }
            else
            {
                destroyMaze(&gs->maze);
                gs->page = MULTIVERSE_CONQUERED;
                addScore(gs);
            }
        }

        else if (gs->mode == TIME_RUNS_OUT)
        {
            gs->last_score += gs->round * 50 + (gs->time_limit - gs->current_time) * 5;
            gs->round++;

            if (gs->round <= 5)
                gs->time_limit -= 10;
            else
                gs->time_limit -= 5;

            initGameplay(gs);
        }

        else if (gs->mode == INFINITY_WAR)
        {
            initGameplay(gs);
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
    const char *control_inst;
    if (gs->mode == BEST_OF_US)
    {
        title = "THE BEST OF US";
        control_inst = "W/A/S/D or Arrow Keys for Movement | F for Auto Solve";
    }
    else if (gs->mode == MULTIVERSE)
    {
        title = "THE MULTIVERSE OF MADMAZE";
        control_inst = "W/A/S/D or Arrow Keys for Movement | F for Auto Solve";
    }
    else if (gs->mode == TIME_RUNS_OUT)
    {
        title = "TIME RUNS OUT";
        control_inst = "W/A/S/D or Arrow Keys for Movement | F for Auto Solve";
    }
    else if (gs->mode == DARK_NIGHT)
    {
        title = "DARK NIGHT";
        control_inst = "W/A/S/D or Arrow Keys for Movement | Space for New Maze | F for Auto Solve";
    }
    else if (gs->mode == INFINITY_WAR)
    {
        title = "INFINITY WAR";
        control_inst = "W/A/S/D or Arrow Keys for Movement | Space for New Maze | F for Auto Solve";
    }

    DrawTextEx(gs->title_font, title, (Vector2){(SCREENWIDTH - MeasureText(title, 50)) / 2, 20}, 50, 1, WHITE);

    DrawTextEx(gs->font1, control_inst, (Vector2){(SCREENWIDTH - MeasureText(control_inst, 20)) / 2, 70}, 20, 1, GRAY);

    // MENU BUTTON
    Rectangle menu_btn_rec = {20, 20, 20, 20};
    Texture menu_btn = hoveredRec(menu_btn_rec) ? gs->menu_hovered_from_game_btn : gs->menu_from_game_btn;
    DrawTexturePro(menu_btn, (Rectangle){0, 0, menu_btn.width, menu_btn.height}, menu_btn_rec, Vector2Zero(), 0, WHITE);

    if (clickedRec(menu_btn_rec))
    {
        PlaySound(gs->click_sound);
        gs->page = MENU;
    }

    if (IsKeyPressed(KEY_BACKSPACE))
    {
        if (gs->mode == MULTIVERSE)
            gs->page = LEVELS;
        else
            gs->page = MENU;
    }

    // FINISH BUTTON
    Rectangle finish_btn_rec = {SCREENWIDTH - 20 - 20, SCREENHEIGHT - 20 - 20, 20, 20};

    if (gs->mode == MULTIVERSE || gs->mode == TIME_RUNS_OUT)
    {
        Texture finish_btn = hoveredRec(finish_btn_rec) ? gs->finish_hovered_btn : gs->finish_btn;
        DrawTexturePro(finish_btn, (Rectangle){0, 0, finish_btn.width, finish_btn.height}, finish_btn_rec, Vector2Zero(), 0, WHITE);

        if (clickedRec(finish_btn_rec))
        {
            PlaySound(gs->click_sound);
            addScore(gs);
            gs->page = GAME_FINISH;
        }
    }

    // Change Mouse Cursor
    if (((gs->mode == MULTIVERSE || gs->mode == TIME_RUNS_OUT) && hoveredRec(finish_btn_rec)) || hoveredRec(menu_btn_rec))
    {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    }
    else
    {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    // BRAND NEW MAZE
    // const char *new_maze_msg = "BRAND NEW MAZE";
    // Card new_maze_card = {(Rectangle){(SCREENWIDTH - 500) / 2, (SCREENHEIGHT - 100) / 2, 500, 100},
    //                       DARKBLUE, 0, WHITE, new_maze_msg, gs->msg_font, WHITE, 50, 1, 20, 80, 10, 10};
    // if (gs->current_time <= 1)
    // {
    //     drawCard(new_maze_card);
    // }

    if (gs->mode == BEST_OF_US || gs->mode == DARK_NIGHT)
    {
        // Time Spent
        const char *time_text = formatTime(gs->current_time);
        DrawTextEx(gs->btn_font, time_text, (Vector2){1250, 15}, 20, 1, WHITE);
    }
    else if (gs->mode == TIME_RUNS_OUT)
    {
        // Round
        DrawTextEx(gs->btn_font, TextFormat("ROUND: %2d", gs->round), (Vector2){1190, 15}, 20, 1, WHITE);

        // Time Left
        const char *time_text = TextFormat("TIME: %s", formatTime(gs->time_limit - gs->current_time));
        DrawTextEx(gs->btn_font, time_text, (Vector2){1190, 45}, 20, 1, WHITE);

        // Score
        DrawTextEx(gs->btn_font, TextFormat("SCORE: %5d", gs->last_score), (Vector2){1190, 75}, 20, 1, WHITE);

        // Game Over
        if (gs->time_limit - gs->current_time <= 0)
        {
            PlaySound(gs->game_finish_sound);
            addScore(gs);
            gs->page = GAME_FINISH;
        }
    }
    else if (gs->mode == MULTIVERSE)
    {
        // Level
        DrawTextEx(gs->btn_font, TextFormat("LEVEL: %d", gs->level), (Vector2){1200, 15}, 20, 1, WHITE);

        // Score
        DrawTextEx(gs->btn_font, TextFormat("SCORE: %5d", gs->last_score), (Vector2){1175, 45}, 20, 1, WHITE);
    }

    EndDrawing();
}

// Draw Dark Night
void drawDark(GameState *gs)
{
    Vector2 pos = {(SCREENWIDTH - gs->maze.width * gs->maze.cell_size) / 2,
                   (SCREENHEIGHT - gs->maze.height * gs->maze.cell_size) / 2 + gs->maze.cell_size};
    for (int y = 0; y < gs->maze.height; y++)
    {
        double startx = pos.x;
        int range = 5;
        for (int x = 0; x < gs->maze.width; x++)
        {
            int distance2 = (x - gs->player.x) * (x - gs->player.x) + (y - gs->player.y) * (y - gs->player.y);
            if (gs->square_on)
            {
                if (!(x == gs->maze.width - 1 && y == gs->maze.height - 1) && (((x - gs->player.x) < -(range - 1) || (x - gs->player.x) > (range - 1)) || ((y - gs->player.y) < -(range - 1) || (y - gs->player.y) > (range - 1))))
                {
                    DrawRectangle(pos.x, pos.y, gs->maze.cell_size, gs->maze.cell_size, BLACK);
                }
            }
            else if (!(x == gs->maze.width - 1 && y == gs->maze.height - 1) && (distance2 > range * range))
            {
                DrawRectangle(pos.x, pos.y, gs->maze.cell_size, gs->maze.cell_size, BLACK);
            }

            pos.x += gs->maze.cell_size;
        }
        pos.x = startx;
        pos.y += gs->maze.cell_size;
    }

    Rectangle square_btn_rec = {SCREENWIDTH - 20 - 80, 100, 40, 40};
    Texture square_btn = (gs->square_on) ? gs->square_btn : gs->square_not_btn;
    DrawTexturePro(square_btn, (Rectangle){0, 0, square_btn.width, square_btn.height}, square_btn_rec, Vector2Zero(), 0, WHITE);

    if (clickedRec(square_btn_rec))
    {
        PlaySound(gs->click_sound);
        if (gs->square_on)
        {
            gs->square_on = false;
        }
        else
        {
            gs->square_on = true;
        }
    }
}

void drawTime(GameState *gs)
{
    BeginDrawing();
    ClearBackground(GetColor(0x2e2e2eff));

    // MENU BUTTON
    Rectangle menu_btn_rec = {20, 20, 20, 20};
    Texture menu_btn = hoveredRec(menu_btn_rec) ? gs->menu_hovered_btn : gs->menu_btn;
    DrawTexturePro(menu_btn, (Rectangle){0, 0, menu_btn.width, menu_btn.height}, menu_btn_rec, Vector2Zero(), 0, WHITE);

    if (clickedRec(menu_btn_rec) || IsKeyPressed(KEY_BACKSPACE))
    {
        PlaySound(gs->click_sound);
        gs->page = MENU;
    }

    // Time Card
    const char *time_card_text = TextFormat("%3s\n%s", gs->name, formatTime(gs->last_time));
    Card time_card = {(Rectangle){SCREENWIDTH * (2.0 / 5), SCREENHEIGHT / 2 - 100, SCREENWIDTH * (1.0 / 5), 100}, GetColor(0xd0e6fdff), 0, BLACK, time_card_text, gs->font1, BLACK, 40, 1, 10, 80, 10, 10};

    drawCard(time_card);

    Button quit_btn = {(Rectangle){SCREENWIDTH * (2.0 / 5), SCREENHEIGHT / 2 + 30, 140, 50}, GetColor(0xff6b5bff), 0, BLACK, "QUIT GAME  ", gs->btn_font, WHITE, 15, 1, 0};

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

    Button replay_btn = {(Rectangle){SCREENWIDTH * (2.0 / 5) + 160, SCREENHEIGHT / 2 + 30, 120, 50}, DARKGREEN, 0, BLACK, "REPLAY ", gs->btn_font, WHITE, 15, 1, 0};

    if (hovered(replay_btn))
    {
        replay_btn.buttonColor = GREEN;
        replay_btn.shadow_opacity = 80;
        drawButton(replay_btn);
    }

    if (clicked(replay_btn))
    {

        PlaySound(gs->click_sound);
        gs->page = PLAYING;
        initGameplay(gs);
    }

    drawButton(replay_btn);

    EndDrawing();
}

void drawScore(GameState *gs)
{
    BeginDrawing();
    ClearBackground(GetColor(0x2e2e2eff));

    // MENU BUTTON
    Rectangle menu_btn_rec = {20, 20, 20, 20};
    Texture menu_btn = hoveredRec(menu_btn_rec) ? gs->menu_hovered_btn : gs->menu_btn;
    DrawTexturePro(menu_btn, (Rectangle){0, 0, menu_btn.width, menu_btn.height}, menu_btn_rec, Vector2Zero(), 0, WHITE);

    if (clickedRec(menu_btn_rec) || IsKeyPressed(KEY_BACKSPACE))
    {
        PlaySound(gs->click_sound);
        gs->page = MENU;
    }

    // Score Card
    const char *score_card_text = TextFormat("%2s\n%d", gs->name, gs->last_score);
    Card score_card = {(Rectangle){SCREENWIDTH * (2.0 / 5), SCREENHEIGHT / 2 - 100, SCREENWIDTH * (1.0 / 5), 100}, GetColor(0xd0e6fdff), 0, BLACK, score_card_text, gs->font1, BLACK, 40, 1, 10, 80, 10, 10};

    drawCard(score_card);

    Button quit_btn = {(Rectangle){SCREENWIDTH * (2.0 / 5), SCREENHEIGHT / 2 + 30, 140, 50}, GetColor(0xff6b5bff), 0, BLACK, "QUIT GAME  ", gs->btn_font, WHITE, 15, 1, 0};

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

    Button replay_btn = {(Rectangle){SCREENWIDTH * (2.0 / 5) + 160, SCREENHEIGHT / 2 + 30, 120, 50}, DARKGREEN, 0, BLACK, "REPLAY ", gs->btn_font, WHITE, 15, 1, 0};

    if (hovered(replay_btn))
    {
        replay_btn.buttonColor = GREEN;
        replay_btn.shadow_opacity = 80;
        drawButton(replay_btn);
    }

    if (clicked(replay_btn))
    {

        PlaySound(gs->click_sound);
        gs->last_score = 0;
        if (gs->mode == MULTIVERSE)
            gs->page = LEVELS;
        else
            gs->page = PLAYING;
        initGameplay(gs);
    }

    drawButton(replay_btn);

    EndDrawing();
}

void addTime(GameState *gs)
{
    strcpy(gs->times[100].player_name, gs->name);
    gs->times[100].time = gs->last_time;
    sortBestTimes(gs->times);
}

void addScore(GameState *gs)
{
    strcpy(gs->scores[100].player_name, gs->name);
    gs->scores[100].score = gs->last_score;
    sortHighScores(gs->scores);
}

void drawMultiConq(GameState *gs)
{
    BeginDrawing();
    ClearBackground(GetColor(0x2e2e2eff));

    // MENU BUTTON
    Rectangle menu_btn_rec = {20, 20, 20, 20};
    Texture menu_btn = hoveredRec(menu_btn_rec) ? gs->menu_hovered_btn : gs->menu_btn;
    DrawTexturePro(menu_btn, (Rectangle){0, 0, menu_btn.width, menu_btn.height}, menu_btn_rec, Vector2Zero(), 0, WHITE);

    if (clickedRec(menu_btn_rec) || IsKeyPressed(KEY_BACKSPACE))
    {
        PlaySound(gs->click_sound);
        gs->page = MENU;
    }

    // Congrats Card
    const char *congo_text = "       Jhapana!!\n  Tu si great ho..\nTohfa qabul karo.";
    Card congo_card = {(Rectangle){SCREENWIDTH * (2.0 / 5), SCREENHEIGHT / 2 - 120, SCREENWIDTH * (1.0 / 5), 120}, GetColor(0xd0e6fdff), 0, BLACK, congo_text, gs->font1, BLACK, 30, 1, 10, 80, 10, 10};

    drawCard(congo_card);

    Button quit_btn = {(Rectangle){SCREENWIDTH * (2.0 / 5), SCREENHEIGHT / 2 + 30, 140, 50}, GetColor(0xff6b5bff), 0, BLACK, "QUIT GAME  ", gs->btn_font, WHITE, 15, 1, 0};

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

    Button replay_btn = {(Rectangle){SCREENWIDTH * (2.0 / 5) + 160, SCREENHEIGHT / 2 + 30, 120, 50}, DARKGREEN, 0, BLACK, "REPLAY ", gs->btn_font, WHITE, 15, 1, 0};

    if (hovered(replay_btn))
    {
        replay_btn.buttonColor = GREEN;
        replay_btn.shadow_opacity = 80;
        drawButton(replay_btn);
    }

    if (clicked(replay_btn))
    {

        PlaySound(gs->click_sound);
        gs->page = PLAYING;
        initGameplay(gs);
    }

    drawButton(replay_btn);

    EndDrawing();
}

void updateGame(GameState *gs)
{

    UpdateMusicStream(gs->bg_music);
    gs->player.sprite_index = (int)(GetTime() / 0.1) % 12;
    gs->current_time = GetTime() - gs->start_time;

    updateSettings(gs);

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
        if (gs->mode == BEST_OF_US || gs->mode == DARK_NIGHT)
            drawTime(gs);
        else if (gs->mode == MULTIVERSE || gs->mode == TIME_RUNS_OUT)
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

    case SEARCH_NAME_INPUT:
        updateSearchNameInput(gs);
        drawSearchNameInput(gs);
        break;

    case SEARCH_HIGH_SCORES:
        if (gs->mode == BEST_OF_US || gs->mode == DARK_NIGHT)
            drawSearchBestTimes(gs);
        else if (gs->mode == MULTIVERSE || gs->mode == TIME_RUNS_OUT)
            drawSearchHighScores(gs);
        break;

    default:
        break;
    }
}