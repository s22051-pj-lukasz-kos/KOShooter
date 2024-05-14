#include "common.h"

#include "draw.h"
#include "init.h"
#include "input.h"
#include "main.h"

// single instance of App and player
App app;
Entity player;

int main(int argc, char *argv[]) {
    // zeruje bloki pamięci zarezerwowany na aplikację i tekstury
    memset(&app, 0, sizeof(App));
    memset(&player, 0, sizeof(Entity));

    initSDL();

    atexit(cleanup);

    player.x = 500;
    player.y = 500;
    player.texture = loadTexture("gfx/player.png");

    while (1) {
        // setup rendering
        prepareScene();

        // collect and process user input
        doInput();

        if (app.up) {
            player.y -= 4;
        }

        if (app.down) {
            player.y += 4;
        }

        if (app.left) {
            player.x -= 4;
        }

        if (app.right) {
            player.x += 4;
        }

        // draw player texture
        blit(player.texture, player.x, player.y);

        // display a scene
        presentScene();

        // limit loop to 62 frames/s
        SDL_Delay(16);
    }

    return 0;
}
