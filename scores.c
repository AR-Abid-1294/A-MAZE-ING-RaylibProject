#include <scores.h>

void sortBestTimes(BestTime *times)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (times[j].time < times[j + 1].time)
            {
                BestTime temp = times[j];
                times[j] = times[j + 1];
                times[j + 1] = temp;
            }
        }
    }
}

void loadBestTimes(BestTime *times, FILE *file)
{
    while (fscanf(file, "%s %d", times->player_name, &times->time))
    {
    }
}

void storeBestTimes(BestTime *times, FILE *file)
{
    
}