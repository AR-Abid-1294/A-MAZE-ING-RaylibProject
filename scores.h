#ifndef SCORES_H
#define SCORES_H

#include <stdio.h>

typedef struct Score
{
    char *player_name;
    float score;    // or time
} Score;

void sortHighScores(Score *scores);

void loadHighScores(Score *scores, FILE *file);

void storeHighScores(Score *scores, FILE *file);

void sortBestTimes(Score *times);

int loadBestTimes(Score *times, FILE *file);

void storeBestTimes(Score *times, FILE *file);

#endif