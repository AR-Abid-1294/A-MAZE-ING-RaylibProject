#ifndef SCORES_H
#define SCORES_H

#include <stdio.h>
#include <string.h>

typedef struct Score
{
    char player_name[30];
    int score;
} Score;

typedef struct Time
{
    char player_name[30];
    float time;
} Time;

void loadTimes(Time times[], const char *file_name);

void storeTimes(Time times[], const char *file_name);

void loadScores(Score scores[], const char *file_name);

void storeScores(Score scores[], const char *file_name);

void sortHighScores(Score *scores);

void sortBestTimes(Time *times);

void nukeBestTimes(Time *times);

void nukeHighScores(Score *scores);

#endif