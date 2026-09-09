#include "scores.h"

void sortBestTimes(Score *times)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (times[j].score < times[j + 1].score)
            {
                Score temp = times[j];
                times[j] = times[j + 1];
                times[j + 1] = temp;
            }
        }
    }
}

int loadBestTimes(Score *times, FILE *file)
{
    int time_count = 0;
    while (fscanf(file, "%s %f", times[time_count].player_name, &times[time_count].score) == 2 && time_count<=10)
    {
        time_count++;
    }
    return time_count;
}

void storeBestTimes(Score *times, FILE *file)
{

}