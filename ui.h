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

void drawButton(Button btn, Font font);

bool hovered(Button btn);

bool clicked(Button btn);

void drawButtonShadow(Button btn, Font font);

typedef struct Card
{
    Rectangle cardRec;
    Color cardColor;
    float stroke;
    Color strokeColor;
    const char *text;
    Font font;
    Color textColor;
    int textFontSize;
} Card;

void drawCard(Card card);

void drawCardShadow(Card card);

const char *formatTime(double time);

void drawTextureShadow(Texture2D texture, Rectangle texture_rec);

#endif