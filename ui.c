#include "ui.h"

// ---------- Menu Page Function Definitions ----------

void drawButton(Button btn)
{
    // Shadow
    Rectangle shadow = {btn.buttonRec.x + 5,
                        btn.buttonRec.y + 5,
                        btn.buttonRec.width,
                        btn.buttonRec.height};
    Color shadow_color = {0, 0, 0, btn.shadow_opacity};
    DrawRectangleRec(shadow, shadow_color);

    // Main Button
    DrawRectangleRec(btn.buttonRec, btn.buttonColor);

    // Stroke
    DrawRectangleLinesEx(btn.buttonRec, btn.stroke, btn.strokeColor);

    // Text
    int textWidth = MeasureText(btn.text, btn.fontSize);
    Vector2 textPos = (Vector2){btn.buttonRec.x + btn.buttonRec.width / 2 - textWidth / 2,
                                btn.buttonRec.y + btn.buttonRec.height / 2 - btn.fontSize / 2};
    DrawTextEx(btn.font, btn.text, (Vector2){textPos.x, textPos.y},
               btn.fontSize, 1, btn.textColor);
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

void drawCard(Card card)
{
    // Shadow
    Rectangle shadow = {card.cardRec.x + card.shadowX,
                        card.cardRec.y + card.shadowY,
                        card.cardRec.width,
                        card.cardRec.height};
    Color shadow_color = {0, 0, 0, card.shadow_opacity};
    DrawRectangleRec(shadow, shadow_color);

    // Main Card
    DrawRectangleRec(card.cardRec, card.cardColor);

    // Stroke
    DrawRectangleLinesEx(card.cardRec, card.stroke, card.strokeColor);

    // Text
    int textWidth = MeasureText(card.text, card.fontSize);
    Vector2 textPos = (Vector2){card.cardRec.x + card.cardRec.width / 2 - textWidth / 2,
                                card.cardRec.y + card.textPosY};
    DrawTextEx(card.font, card.text, (Vector2){textPos.x, textPos.y}, card.fontSize, 1, card.textColor);
}

const char *formatTime(double time)
{
    int min = time / 60;
    time -= min * 60;

    return TextFormat("%2d:%4.2lf", min, time);
}

void drawTextureShadowed(Texture2D texture, Rectangle texture_rec)
{
    Rectangle shadow = {texture_rec.x + 10,
                        texture_rec.y + 10,
                        texture_rec.width,
                        texture_rec.height};
    DrawRectangleRec(shadow, GetColor(0x00000050));
    DrawTexturePro(texture, (Rectangle){0, 0, texture.width, texture.height},
                   texture_rec, (Vector2){0, 0}, 0, WHITE);
}

void drawText(Font font, const char *text, Vector2 pos, float font_size, float spacing, Color color, int shadow_opacity)
{
    // Shadow
    Vector2 shadow_pos = {pos.x + 5, pos.y + 5};
    Color shadow_color = {0, 0, 0, shadow_opacity};
    DrawTextEx(font, text, shadow_pos, font_size, spacing, shadow_color);

    // Main Text
    DrawTextEx(font, text, pos, font_size, spacing, color);
}