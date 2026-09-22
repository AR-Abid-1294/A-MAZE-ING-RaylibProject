#include "scores.h"

// best times for THE BEST OF US mode

/*void sortBestTimes(Time *times)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10-i; j++)
        {
            if (times[j].time > times[j + 1].time)
            {
                Time temp = times[j];
                times[j] = times[j + 1];
                times[j + 1] = temp;
            }
        }
    }
}*/

// afif koreche check korte
void sortBestTimes(Time *times)
{
    for (int i = 0; i < 11; i++)
        for (int j = i + 1; j < 11; j++)
            if (times[j].time < times[i].time)
            {
                Time temp = times[i];
                times[i] = times[j];
                times[j] = temp;
            }
}

void nukeBestTimes(Time *times)
{
    for (int i = 0; i < 11; i++)
    {
        strcpy(times[i].player_name, "-");
        times[i].time = 3599.9880;
    }
}

// highest score for the multiverse of madmaze

/*void sortHighScores(Score *scores)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9-i; j++)
        {
            if (scores[j].score < scores[j + 1].score)
            {
                Score temp = scores[j];
                scores[j] = scores[j + 1];
                scores[j + 1] = temp;
            }
        }
    }
}*/
void sortHighScores(Score *scores)
{
    for (int i = 0; i < 11; i++)
        for (int j = i + 1; j < 11; j++)
            if (scores[j].score > scores[i].score)
            {
                Score temp = scores[i];
                scores[i] = scores[j];
                scores[j] = temp;
            }
}

void nukeHighScores(Score *scores)
{
    for (int i = 0; i < 11; i++)
    {
        strcpy(scores[i].player_name, "-");
        scores[i].score = 0;
    }
}
