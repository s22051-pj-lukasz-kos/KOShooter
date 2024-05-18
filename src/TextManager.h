#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H

#include <SDL2/SDL.h>
#include "common.h"
#include <string>

    class TextManager {
public:
    TextManager();

    ~TextManager();

    void initFonts();

    void drawText(int x, int y, int r, int g, int b, const char *format, ...);

private:
    SDL_Texture *fontTexture;
    char drawTextBuffer[MAX_LINE_LENGTH];
};

#endif // TEXTMANAGER_H
