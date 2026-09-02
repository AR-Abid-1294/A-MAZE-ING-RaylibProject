#include "ui.h"

// ---------- Menu Page Function Definitions ----------

void drawButton(Button btn)
{
    DrawRectangleRounded(btn.buttonRec, 2, 100, btn.buttonColor);
    DrawRectangleLinesEx(btn.buttonRec, btn.stroke, btn.strokeColor);
    int textWidth = MeasureText(btn.text, btn.textFontSize);
    Vector2 textPos = (Vector2){btn.buttonRec.x + btn.buttonRec.width / 2 - textWidth / 2,
                                btn.buttonRec.y + btn.buttonRec.height / 2 - btn.textFontSize / 2};
    DrawText(btn.text, textPos.x, textPos.y, btn.textFontSize, btn.textColor);
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

void drawButtonShadow(Button btn)
{
    Rectangle shadow = {btn.buttonRec.x + 5,
                        btn.buttonRec.y + 5,
                        btn.buttonRec.width,
                        btn.buttonRec.height};
    // DrawRectangleRec(shadow, GetColor(0x00000050));
    DrawRectangleRounded(shadow, 2, 100, GetColor(0x00000050));
    drawButton(btn);
}

void drawCard(Card card)
{
    DrawRectangleRec(card.cardRec, card.cardColor);
    DrawRectangleLinesEx(card.cardRec, card.stroke, card.strokeColor);
    int textWidth = MeasureText(card.text, card.textFontSize);
    Vector2 textPos = (Vector2){card.cardRec.x + card.cardRec.width / 2 - textWidth / 2,
                                card.cardRec.y + card.cardRec.height / 2 - card.textFontSize};
    DrawText(card.text, textPos.x, textPos.y, card.textFontSize, card.textColor);
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