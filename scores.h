#ifndef SCORES_H
#define SCORES_H

#include <stdio.h>

typedef struct BestTime
{
    char *player_name;
    float time;
} BestTime;

void sortBestTimes(BestTime *times);

void loadBestTimes(BestTime *times, FILE *file);

void storeBestTimes(BestTime *times, FILE *file);

#endif