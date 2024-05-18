#ifndef DRAW_H
#define DRAW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class App;

class Renderer {
public:
    Renderer(SDL_Renderer *renderer);

    void prepareScene();

    void presentScene();

    SDL_Texture *loadTexture(const std::string &filename);

    void blit(SDL_Texture *texture, int x, int y);

    void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y);

private:
    SDL_Renderer *renderer;
};

#endif // DRAW_H
