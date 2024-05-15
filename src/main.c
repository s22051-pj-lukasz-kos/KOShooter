#include "common.h"

#include "draw.h"
#include "init.h"
#include "input.h"
#include "main.h"
#include "stage.h"

App app;
Stage stage;

static void capFrameRate(long *then, float *remainder);

int main(int argc, char *argv[]) {
    long then;
    float remainder;

    // zeruje bloki pamięci zarezerwowany na aplikację
    memset(&app, 0, sizeof(App));

    initSDL();

    // from init.c
    atexit(cleanup);

    initStage();

    then = SDL_GetTicks();

    remainder = 0;

    while (1) {
        // setup rendering
        prepareScene();

        // collect and process user input
        doInput();

        app.delegate.logic();

        app.delegate.draw();

        // display a scene
        presentScene();

        // limit loop to 60 frames/s
        capFrameRate(&then, &remainder);
    }

    return 0;
}

static void capFrameRate(long *then, float *remainder) {
    long wait, frameTime;

    wait = 16 + *remainder;

    *remainder -= (int) *remainder;

    frameTime = SDL_GetTicks() - *then;

    wait -= frameTime;

    if (wait < 1) {
        wait = 1;
    }

    SDL_Delay(wait);

    *remainder += 0.667;

    *then = SDL_GetTicks();
}
