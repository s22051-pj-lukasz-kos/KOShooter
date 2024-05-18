#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SDL2/SDL_mixer.h>
#include <string>
#include "common.h"

class SoundManager {
public:
    SoundManager();

    ~SoundManager();

    void initSounds();

    void loadMusic(const std::string &filename);

    void playMusic(int loop);

    void playSound(int id, int channel);

private:
    void loadSounds();

    Mix_Chunk *sounds[SND_MAX];
    Mix_Music *music;
};


#endif // SOUNDMANAGER_H
