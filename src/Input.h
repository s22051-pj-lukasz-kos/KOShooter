#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>

class App;

class InputHandler {
public:
    InputHandler();

    void doInput();

private:
    void doKeyDown(SDL_KeyboardEvent *event);

    void doKeyUp(SDL_KeyboardEvent *event);
};

#endif // INPUT_H
