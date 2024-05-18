#ifndef DEBRIS_H
#define DEBRIS_H

#include <SDL2/SDL.h>

/*
 * Represents debris that is thrown when a ship is destroyed
 */
class Debris {
public:
    Debris();

    float x, y;
    float dx, dy;
    SDL_Rect rect;
    SDL_Texture *texture;
    int life;
    Debris *next;
};

#endif // DEBRIS_H
