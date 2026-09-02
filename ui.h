#ifndef UI_H
#define UI_H

#include "raylib.h"

// ---------- Menu Page Structures and Functions ----------

typedef struct Button
{
    Rectangle buttonRec;
    Color buttonColor;
    float stroke;
    Color strokeColor;
    char text[50];
    Color textColor;
    int textFontSize;
} Button;

void drawButton(Button btn);

bool hovered(Button btn);

bool clicked(Button btn);

void drawButtonShadow(Button btn);

typedef struct Card
{
    Rectangle cardRec;
    Color cardColor;
    float stroke;
    Color strokeColor;
    char text[1000];
    Color textColor;
    int textFontSize;
} Card;

void drawCard(Card card);

void drawCardShadow(Card card);

#endif