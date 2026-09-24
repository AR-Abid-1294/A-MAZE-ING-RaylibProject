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




void sortHighScores(Score *scores);

void loadHighScores(Score *scores, FILE *file);

void storeHighScores(Score *scores, FILE *file);

void sortBestTimes(Time *times);

void nukeBestTimes(Time *times);

void nukeHighScores(Score *scores);


#endif