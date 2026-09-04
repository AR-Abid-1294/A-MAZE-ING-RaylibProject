#ifndef UI_H
#define UI_H

#include "raylib.h"

// ---------- Menu Page Structures and Functions ----------

typedef struct Button
{
    // Main Button
    Rectangle buttonRec;
    Color buttonColor;

    // Stroke
    float stroke;
    Color strokeColor;

    // Text
    const char *text;
    Font font;
    Color textColor;
    float fontSize;
    float textSpacing;

    // Shadow
    int shadow_opacity;
} Button;

void drawButton(Button btn);

bool hovered(Button btn);

bool clicked(Button btn);

typedef struct Card
{
    // Main Card
    Rectangle cardRec;
    Color cardColor;

    // Stroke
    float stroke;
    Color strokeColor;

    // Text
    const char *text;
    Font font;
    Color textColor;
    float fontSize;
    float textSpacing;

    // Shadow
    int shadow_opacity;
} Card;

void drawCard(Card card);

const char *formatTime(double time);

void drawTextureShadowed(Texture2D texture, Rectangle texture_rec);

void drawText(Font font, const char *text, Vector2 pos, float font_size, float spacing, Color color, int shadow_opacity);

#endif