#include "ui.h"

// ---------- Menu Page Function Definitions ----------

void drawButton(Button btn, Font font)
{
    DrawRectangleRec(btn.buttonRec, btn.buttonColor);
    DrawRectangleLinesEx(btn.buttonRec, btn.stroke, btn.strokeColor);
    int textWidth = MeasureText(btn.text, btn.textFontSize);
    Vector2 textPos = (Vector2){btn.buttonRec.x + btn.buttonRec.width / 2 - textWidth / 2,
                                btn.buttonRec.y + btn.buttonRec.height / 2 - btn.textFontSize / 2};
    DrawTextEx(font, btn.text, (Vector2){textPos.x, textPos.y},
               btn.textFontSize, 5, btn.textColor);
}

bool hovered(Button btn)
{
    Vector2 mouse = GetMousePosition();
    if (CheckCollisionPointRec(mouse, btn.buttonRec))
        return true;
    return false;
}

bool clicked(Button btn)
{
    if (hovered(btn) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        return true;
    return false;
}

void drawButtonShadow(Button btn, Font font)
{
    Rectangle shadow = {btn.buttonRec.x + 5,
                        btn.buttonRec.y + 5,
                        btn.buttonRec.width,
                        btn.buttonRec.height};
    DrawRectangleRec(shadow, GetColor(0x00000050));
    drawButton(btn, font);
}

void drawCard(Card card)
{
    DrawRectangleRec(card.cardRec, card.cardColor);
    DrawRectangleLinesEx(card.cardRec, card.stroke, card.strokeColor);
    int textWidth = MeasureText(card.text, card.textFontSize);
    Vector2 textPos = (Vector2){card.cardRec.x + card.cardRec.width / 2 - textWidth / 2,
                                card.cardRec.y + card.cardRec.height / 2 - card.textFontSize};
    DrawTextEx(card.font, card.text, (Vector2){textPos.x, textPos.y}, card.textFontSize, 1, card.textColor);
}

void drawCardShadow(Card card)
{
    Rectangle shadow = {card.cardRec.x + 10,
                        card.cardRec.y + 10,
                        card.cardRec.width,
                        card.cardRec.height};
    // DrawRectangleRec(shadow, GetColor(0x00000050));
    DrawRectangleRec(shadow, GetColor(0x00000050));
    drawCard(card);
}

const char *formatTime(double time)
{
    int min = time / 60;
    time -= min * 60;

    return TextFormat("%2d:%4.2lf", min, time);
}