#ifndef STAGE_H
#define STAGE_H

#include "common.h"
#include "Entity.h"
#include "Explosion.h"
#include "Debris.h"
#include "Star.h"

/*
 * To hold information about the stage: fighters, bullets, explosions, background etc.
 */
class Stage {
public:
    Stage();

    ~Stage();

    void initStage();

    void resetStage();

    void logic();

    void draw();

private:
    void initPlayer();

    void initStarfield();

    void doBackground();

    void doStarfield();

    void doPlayer();

    void doEnemies();

    void doFighters();

    void doBullets();

    void doExplosions();

    void doDebris();

    void doPointsPods();

    void spawnEnemies();

    void clipPlayer();

    void fireBullet();

    void fireAlienBullet(Entity *e);

    int bulletHitFighter(Entity *b);

    void addExplosions(int x, int y, int num);

    void addDebris(Entity *e);

    void addPointsPod(int x, int y);

    void drawBackground();

    void drawStarfield();

    void drawPointsPods();

    void drawFighters();

    void drawBullets();

    void drawDebris();

    void drawExplosions();

    void drawHud();

    /*
     * Head represents the beginning of linked list. By defining Head as a value,
     * it ensures that the list always has a node to start from. Head doesn't contain actual data,
     * but provides an anchor to list. When list is empty Head.next is NULL
     * Head.next contains first element in the list with actual value.
     *
     * Tail is a pointer to the last element in the linked list. This allows for adding new elements to list.
     * When list is empty, Tail points to Head. This allows to quickly check if Head.next is NULL.
     */
    Entity fighterHead, *fighterTail;
    Entity bulletHead, *bulletTail;
    Entity pointsHead, *pointsTail;
    Explosion explosionHead, *explosionTail;
    Debris debrisHead, *debrisTail;
    int score;

    Entity *player;
    SDL_Texture *bulletTexture;
    SDL_Texture *enemyTexture;
    SDL_Texture *alienBulletTexture;
    SDL_Texture *playerTexture;
    SDL_Texture *background;
    SDL_Texture *explosionTexture;
    SDL_Texture *pointsTexture;
    int enemySpawnTimer;
    int stageResetTimer;
    int backgroundX;
    Star stars[MAX_STARS];
    int highscore;
};

#endif // STAGE_H
