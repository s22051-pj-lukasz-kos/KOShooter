/*
 * Functions concerned with setting up SDL.
 */
#include "Init.h"
#include "common.h"
#include "App.h"

extern App app;

Initializer::Initializer() {
    initSDL();
}

Initializer::~Initializer() {
    cleanup();
}

void Initializer::initSDL() {
    int rendererFlags = SDL_RENDERER_ACCELERATED;
    int windowFlags = 0;

    // initialize SDL_INIT_VIDEO subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }
    // initialize the audio
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
        printf("Couldn't initialize SDL Mixer\n");
        exit(1);
    }

    Mix_AllocateChannels(MAX_SND_CHANNELS);

    // Create window. SDL_WINDOWPOS_UNDEFINED means OS position the window wherever it likes
    app.window = SDL_CreateWindow("KOShooter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, windowFlags);

    if (!app.window) {
        printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    // Create renderer. -1 tells SDL to use the first graphics acceleration device it finds
    app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);

    if (!app.renderer) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        exit(1);
    }

    // old
//    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    // init SDL Image to load textures
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        SDL_Log("Failed to initialize SDL_Image: %s", IMG_GetError());
        exit(1);
    }

    SDL_ShowCursor(SDL_DISABLE);
}

void Initializer::cleanup() {
    Mix_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    SDL_Quit();
}

void Initializer::cleanupWrapper() {
    cleanup();
}