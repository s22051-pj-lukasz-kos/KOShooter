#ifndef INIT_H
#define INIT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "common.h"

class Initializer {
public:
    Initializer();

    ~Initializer();

    void cleanupWrapper();

private:
    void initSDL();

    void cleanup();
};

#endif // INIT_H
