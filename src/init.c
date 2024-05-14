/*
 * Functions concerned with setting up SDL.
 */
#include <SDL2/SDL_image.h>

#include "common.h"

#include "init.h"

extern App app;

void initSDL(void) {
    int rendererFlags, windowFlags;

    rendererFlags = SDL_RENDERER_ACCELERATED;

    windowFlags = 0;

    // initialize SDL_INIT_VIDEO subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    // Create window. SDL_WINDOWPOS_UNDEFINED means OS position the window wherever it likes
    app.window = SDL_CreateWindow("SDL Shooter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, windowFlags);

    if (!app.window) {
        printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    // Create renderer. -1 tells SDL to use the first graphics acceleration device it finds
    app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);

    // init SDL Image to load textures
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    if (!app.renderer) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        exit(1);
    }
}

void cleanup(void) {
    IMG_Quit();

    SDL_DestroyRenderer(app.renderer);

    SDL_DestroyWindow(app.window);

    SDL_Quit();
}
