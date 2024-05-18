/*
 * Handles input, such as reading the keyboard.
 */
#include "Input.h"
#include "App.h"
#include "common.h"

extern App app;

InputHandler::InputHandler() {}

void InputHandler::doKeyDown(SDL_KeyboardEvent *event) {
    if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS) {
        app.keyboard[event->keysym.scancode] = 1;
    }
}

void InputHandler::doKeyUp(SDL_KeyboardEvent *event) {
    if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS) {
        app.keyboard[event->keysym.scancode] = 0;
    }
}

void InputHandler::doInput() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                exit(0);
                break;

            case SDL_KEYDOWN:
                doKeyDown(&event.key);
                break;

            case SDL_KEYUP:
                doKeyUp(&event.key);
                break;

            default:
                break;
        }
    }
}
