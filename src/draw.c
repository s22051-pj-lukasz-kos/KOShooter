/*
 * Functions related to drawing and rendering.
 */
#include <SDL2/SDL_image.h>
#include "common.h"
#include "draw.h"

extern App app;

void prepareScene(void) {
    SDL_SetRenderDrawColor(app.renderer, 32, 32, 32, 255);
    SDL_RenderClear(app.renderer);
}

void presentScene(void) {
    SDL_RenderPresent(app.renderer);
}

/*
 * Load an image and return it as a texture
 */
SDL_Texture *loadTexture(char *filename) {
    SDL_Texture *texture;

    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

    texture = IMG_LoadTexture(app.renderer, filename);

    return texture;
}

/*
 * Draws a texture at x and y coordinates
 */
void blit(SDL_Texture *texture, int x, int y) {
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

    /*
     * Actual drawing
     * @param *renderer
     * @param *texture
     * @param *srcrect rectangular region of the source texture. If NULL, pass the entire texture
     * @param *dstrect rectangular region of the target renderer
     */
    SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}

/*
 * It takes rect of texture and copy it. Used for "destroying" ships
 */
void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y) {
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    dest.w = src->w;
    dest.h = src->h;

    SDL_RenderCopy(app.renderer, texture, src, &dest);
}


