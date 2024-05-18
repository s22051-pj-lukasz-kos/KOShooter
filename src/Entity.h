#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>

/*
 * Represents the entity (player, bullets, enemies, etc.)
 * Entities could structure linked list, using next pointer
 */
class Entity {
public:
    Entity();

    float x, y;
    int w, h;
    float dx, dy;
    int health;
    int reload;
    int side; ///< side defined in defs (player or alien)
    SDL_Texture *texture;
    Entity *next; ///< Pointer to next Entity (for linked list)
};

#endif //ENTITY_H
