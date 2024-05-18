#include "App.h"
#include "Draw.h"
#include "Input.h"
#include "Init.h"

Initializer App::initializer;

void App::cleanup() {
    initializer.cleanupWrapper();
}

App::App() : then(0), remainder(0.0f), soundManager(), textManager(), inputHandler(), stage() {
    rendererObj = new Renderer(renderer);
    atexit(App::cleanup);
    soundManager.initSounds();
    textManager.initFonts();
    stage.initStage();
    then = SDL_GetTicks();
}

App::~App() {
    delete rendererObj;
    App::cleanup();
}

SDL_Renderer *App::getRenderer() const {
    return renderer;
}

Renderer *App::getRendererObj() const {
    return rendererObj;
}

SoundManager& App::getSoundManager() {
    return soundManager;
}

TextManager& App::getTextManager() {
    return textManager;
}

void App::run() {
    while (true) {
        soundManager.loadMusic("music/Mercury.ogg");
        soundManager.playMusic(1);
        rendererObj->prepareScene();
        inputHandler.doInput();
        delegate.logic();
        delegate.draw();
        rendererObj->presentScene();
        capFrameRate();
    }
}

void App::capFrameRate() {
    long wait = 16 + remainder;
    remainder -= static_cast<int>(remainder);
    long frameTime = SDL_GetTicks() - then;
    wait -= frameTime;
    if (wait < 1) {
        wait = 1;
    }
    SDL_Delay(wait);
    remainder += 0.667f;
    then = SDL_GetTicks();
}