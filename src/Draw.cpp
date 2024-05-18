/*
 * Functions related to drawing and rendering.
 */
#include "Draw.h"
#include "App.h"
#include "common.h"

extern App app;

/*
 * <name of a class>::<name of a constructor>(parameter) : initializer list {constructor body}
 * initializer list consists of member variable and value (parameter) passed to constructor
 */
Renderer::Renderer(SDL_Renderer *renderer) : renderer(renderer) {}

void Renderer::prepareScene() {
    SDL_SetRenderDrawColor(renderer, 32, 32, 32, 255);
    SDL_RenderClear(renderer);
}

void Renderer::presentScene() {
    SDL_RenderPresent(renderer);
}

/*
 * Load an image and return it as a texture
 */
SDL_Texture *Renderer::loadTexture(const std::string &filename) {
    SDL_Texture *texture = nullptr;

    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename.c_str());

    texture = IMG_LoadTexture(renderer, filename.c_str());

    if (!texture) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load texture %s: %s", filename.c_str(),
                     IMG_GetError());
    }

    return texture;
}

/*
 * Draws a texture at x and y coordinates
 */
void Renderer::blit(SDL_Texture *texture, int x, int y) {
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
    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

/*
 * It takes rect of texture and copy it. Used for "destroying" ships and rendering text on screen
 * @param *texture source texture that contains the image
 * @param *src pointer that defines the portion of a texture to copy
 * @param x, y position of *src rect
 */
void Renderer::blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y) {
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    dest.w = src->w;
    dest.h = src->h;

    SDL_RenderCopy(renderer, texture, src, &dest);
}
