#include "TextManager.h"
#include "common.h"
#include "Draw.h"
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include "App.h"

#define GLYPH_HEIGHT 28
#define GLYPH_WIDTH  18

extern App app;

TextManager::TextManager() : fontTexture(nullptr), drawTextBuffer{} {}

TextManager::~TextManager() {
    if (fontTexture) {
        SDL_DestroyTexture(fontTexture);
    }
}

void TextManager::initFonts() {
    fontTexture = app.getRendererObj()->loadTexture("gfx/font.png");
    if (!fontTexture) {
        SDL_Log("Failed to load font texture: %s", SDL_GetError());
    }
}

/*
 * @param x The x coordinate for text
 * @param y The y coordinate for text
 * @param r Red part of RGB color
 * @param g Green part of RGB color
 * @param b Blue part of RGB color
 * @param format The text to render
 */
void TextManager::drawText(int x, int y, int r, int g, int b, const char *format, ...) {
    int len, c;
    SDL_Rect rect;
    // variable list of arguments
    va_list args;

    // clearing text
    std::memset(&drawTextBuffer, '\0', sizeof(drawTextBuffer));

    // init va_list with the last fixed argument format
    va_start(args, format);
    // formats the text into drawTextBuffer using the format string and variable arguments.
    vsprintf(drawTextBuffer, format, args);
    // cleans va_list (args)
    va_end(args);

    // length of formatted text
    len = std::strlen(drawTextBuffer);

    rect.w = GLYPH_WIDTH;
    rect.h = GLYPH_HEIGHT;
    rect.y = 0;

    // set font color
    SDL_SetTextureColorMod(fontTexture, r, g, b);

    for (int i = 0; i < len; i++) {
        c = drawTextBuffer[i];

        if (c >= ' ' && c <= 'Z') {
            rect.x = (c - ' ') * GLYPH_WIDTH;
            app.getRendererObj()->blitRect(fontTexture, &rect, x, y);
            // adjustments, so fonts won't stack on top of each other
            x += GLYPH_WIDTH;
        }
    }
}