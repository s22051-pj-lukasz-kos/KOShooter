#include "SoundManager.h"
#include "common.h"

SoundManager::SoundManager() {
    memset(sounds, 0, sizeof(Mix_Chunk * ) * SND_MAX);
    music = nullptr;
}

SoundManager::~SoundManager() {
    for (int i = 0; i < SND_MAX; ++i) {
        if (sounds[i] != nullptr) {
            Mix_FreeChunk(sounds[i]);
        }
    }

    if (music != nullptr) {
        Mix_FreeMusic(music);
    }
}

void SoundManager::initSounds() {
    memset(sounds, 0, sizeof(Mix_Chunk *) * SND_MAX);
    music = nullptr;
    loadSounds();
}

void SoundManager::loadMusic(const std::string &filename) {
    if (music != nullptr) {
        Mix_HaltMusic();
        Mix_FreeMusic(music);
        music = nullptr;
    }
    // returns a pointer to music file (loads it to memory)
    music = Mix_LoadMUS(filename.c_str());
    if (music == nullptr) {
        SDL_Log("Failed to load music: %s", Mix_GetError());
    }
}

void SoundManager::playMusic(int loop) {
    if (Mix_PlayMusic(music, (loop) ? -1 : 0) == -1) {
        SDL_Log("Failed to play music: %s", Mix_GetError());
    }
}

void SoundManager::playSound(int id, int channel) {
    if (Mix_PlayChannel(channel, sounds[id], 0) == -1) {
        SDL_Log("Failed to play sound: %s", Mix_GetError());
    }
}

void SoundManager::loadSounds() {
    sounds[SND_PLAYER_FIRE] = Mix_LoadWAV("sound/player_fire.ogg");
    sounds[SND_PLAYER_DIE] = Mix_LoadWAV("sound/player_die.ogg");
    sounds[SND_ALIEN_FIRE] = Mix_LoadWAV("sound/alien_fire.ogg");
    sounds[SND_ALIEN_DIE] = Mix_LoadWAV("sound/alien_die.ogg");
    sounds[SND_POINTS] = Mix_LoadWAV("sound/points.ogg");

    for (int i = 0; i < SND_MAX; ++i) {
        if (sounds[i] == nullptr) {
            SDL_Log("Failed to load sound: %s", Mix_GetError());
        }
    }
}