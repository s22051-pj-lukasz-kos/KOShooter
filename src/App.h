#ifndef APP_H
#define APP_H

#include <SDL2/SDL.h>
#include "Delegate.h"
#include "SoundManager.h"
#include "TextManager.h"
#include "Draw.h"
#include "Input.h"
#include "Stage.h"

class Initializer;

/*
 * App will hold reference to all related logic, window, keyboard events, etc.
 */
class App {
public:
    App();

    ~App();

    void run();

    SDL_Renderer *getRenderer() const;

    Renderer *getRendererObj() const;

    SoundManager& getSoundManager();

    TextManager& getTextManager();

    SDL_Renderer *renderer;
    SDL_Window *window;
    Delegate delegate;
    int keyboard[MAX_KEYBOARD_KEYS];

private:
    long then;
    float remainder;
    SoundManager soundManager;
    TextManager textManager;

    static Initializer initializer;

    static void cleanup();

    Renderer *rendererObj;
    InputHandler inputHandler;
    Stage stage;

    void capFrameRate();
};

#endif // APP_H