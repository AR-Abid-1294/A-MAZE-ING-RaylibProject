#include "scores.h"

void loadTimes(Time times[], const char *file_name)
{
    FILE *times_file = fopen(file_name, "r");
    for (int i = 0; i < 100; i++)
        fscanf(times_file, "%f %[^\n]", &times[i].time, times[i].player_name);
    fclose(times_file);
}

void storeTimes(Time times[], const char *file_name)
{
    FILE *times_file = fopen(file_name, "w");
    for (int i = 0; i < 100; i++)
        fprintf(times_file, "%f %s\n", times[i].time, times[i].player_name);
    fclose(times_file);
}

void loadScores(Score scores[], const char *file_name)
{
    FILE *scores_file = fopen(file_name, "r");
    for (int i = 0; i < 100; i++)
        fscanf(scores_file, "%d %[^\n]", &scores[i].score, scores[i].player_name);
    fclose(scores_file);
}

void storeScores(Score scores[], const char *file_name)
{
    FILE *scores_file = fopen(file_name, "w");
    for (int i = 0; i < 100; i++)
        fprintf(scores_file, "%d %s\n", scores[i].score, scores[i].player_name);
    fclose(scores_file);
}

// afif koreche check korte
void sortBestTimes(Time *times)
{
    for (int i = 0; i < 100; i++)
        for (int j = i + 1; j < 101; j++)
            if (times[j].time < times[i].time)
            {
                Time temp = times[i];
                times[i] = times[j];
                times[j] = temp;
            }
}

void nukeBestTimes(Time *times)
{
    for (int i = 0; i < 101; i++)
    {
        strcpy(times[i].player_name, "-");
        times[i].time = 3599.9880;
    }
}

void sortHighScores(Score *scores)
{
    for (int i = 0; i < 101; i++)
        for (int j = i + 1; j < 101; j++)
            if (scores[j].score > scores[i].score)
            {
                Score temp = scores[i];
                scores[i] = scores[j];
                scores[j] = temp;
            }
}

void nukeHighScores(Score *scores)
{
    for (int i = 0; i < 101; i++)
    {
        strcpy(scores[i].player_name, "-");
        scores[i].score = 0;
    }
}
