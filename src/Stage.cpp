#include "Stage.h"
#include "common.h"
#include "Draw.h"
#include "Util.h"
#include "App.h"

extern App app;

// If linked list is empty, Tail points to Head.
Stage::Stage() : fighterTail(&fighterHead), bulletTail(&bulletHead), pointsTail(&pointsHead),
                 explosionTail(&explosionHead), debrisTail(&debrisHead), score(0), player(nullptr),
                 bulletTexture(nullptr), enemyTexture(nullptr), alienBulletTexture(nullptr), playerTexture(nullptr),
                 background(nullptr), explosionTexture(nullptr), pointsTexture(nullptr), enemySpawnTimer(0),
                 stageResetTimer(0), backgroundX(0), highscore(0) {
    for (int i = 0; i < MAX_STARS; ++i) {
        stars[i] = Star();
    }
}

Stage::~Stage() {
    resetStage();
}

void Stage::initStage() {
    app.delegate.logic = std::bind(&Stage::logic, this);
    app.delegate.draw = std::bind(&Stage::draw, this);

    score = 0;
    player = nullptr;
    bulletTexture = nullptr;
    enemyTexture = nullptr;
    alienBulletTexture = nullptr;
    playerTexture = nullptr;
    background = nullptr;
    explosionTexture = nullptr;
    pointsTexture = nullptr;
    enemySpawnTimer = 0;
    stageResetTimer = FPS * 3;
    backgroundX = 0;
    highscore = 0;

    fighterTail = &fighterHead;
    bulletTail = &bulletHead;
    explosionTail = &explosionHead;
    debrisTail = &debrisHead;
    pointsTail = &pointsHead;

    bulletTexture = app.getRendererObj()->loadTexture("gfx/playerBullet.png");
    enemyTexture = app.getRendererObj()->loadTexture("gfx/enemy.png");
    alienBulletTexture = app.getRendererObj()->loadTexture("gfx/alienBullet.png");
    playerTexture = app.getRendererObj()->loadTexture("gfx/player.png");
    background = app.getRendererObj()->loadTexture("gfx/background.png");
    explosionTexture = app.getRendererObj()->loadTexture("gfx/explosion.png");
    pointsTexture = app.getRendererObj()->loadTexture("gfx/points.png");


    app.getSoundManager().loadMusic("music/Mercury.ogg");
    app.getSoundManager().playMusic(1);

    resetStage();
}

/*
 * Used to reset a game stage.
 * Iterates over various linked lists to remove:
 * - fighters,
 * - bullets,
 * - explosions,
 * - debris,
 * - points.
 *
 * Also initialize background and player. And reset a score.
 */
void Stage::resetStage() {
    Entity *e;
    Explosion *ex;
    Debris *d;

    // in first iteration fighterHead.next is the first element in the list (a pointer)
    while (fighterHead.next) {
        e = fighterHead.next;
        // updating head pointer to next element in the list
        fighterHead.next = e->next;
        // free e from memory. Next iteration goes to e->next
        delete e;
    }

    while (bulletHead.next) {
        e = bulletHead.next;
        bulletHead.next = e->next;
        delete e;
    }

    while (explosionHead.next) {
        ex = explosionHead.next;
        explosionHead.next = ex->next;
        delete ex;
    }

    while (debrisHead.next) {
        d = debrisHead.next;
        debrisHead.next = d->next;
        delete d;
    }

    while (pointsHead.next) {
        e = pointsHead.next;
        pointsHead.next = e->next;
        delete e;
    }

    // reseting linked lists: tail point to head, where head.next == nullptr
    fighterTail = &fighterHead;
    bulletTail = &bulletHead;
    explosionTail = &explosionHead;
    debrisTail = &debrisHead;
    pointsTail = &pointsHead;
    score = 0;

    initPlayer();
    initStarfield();
    enemySpawnTimer = 0;
    stageResetTimer = FPS * 3;
}

void Stage::initPlayer() {
    player = new Entity();
    player->x = 100.0f;
    player->y = (SCREEN_HEIGHT / 2) - (player->h / 2);
    player->w = 0;
    player->h = 0;
    player->dx = 0.0f;
    player->dy = 0.0f;
    player->health = 5;
    player->reload = 0;
    player->side = SIDE_PLAYER;
    player->texture = playerTexture;
    player->next = nullptr;

    // player is the first actual element of the fighter linked list
    fighterTail->next = player;
    fighterTail = player;

    SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);

    player->side = SIDE_PLAYER;
}

void Stage::initStarfield() {
    for (int i = 0; i < MAX_STARS; i++) {
        stars[i].x = rand() % SCREEN_WIDTH;
        stars[i].y = rand() % SCREEN_HEIGHT;
        stars[i].speed = 1 + rand() % 8;
    }
}

void Stage::logic() {
    doBackground();
    doStarfield();
    doPlayer();
    doEnemies();
    doFighters();
    doBullets();
    doExplosions();
    doDebris();
    doPointsPods();
    spawnEnemies();
    clipPlayer();

    if (player == nullptr && --stageResetTimer <= 0) {
        resetStage();
    }
}

void Stage::doBackground() {
    if (--backgroundX < -SCREEN_WIDTH) {
        backgroundX = 0;
    }
}

void Stage::doStarfield() {
    for (int i = 0; i < MAX_STARS; i++) {
        stars[i].x -= stars[i].speed;
        // this will prevent the lineup of stars after some time
        if (stars[i].x < 0) {
            stars[i].x = SCREEN_WIDTH + stars[i].x;
        }
    }
}

void Stage::doPlayer() {
    if (player != nullptr) {
        player->dx = player->dy = 0;

        if (player->reload > 0) {
            player->reload--;
        }

        if (app.keyboard[SDL_SCANCODE_UP]) {
            player->dy = -PLAYER_SPEED;
        }

        if (app.keyboard[SDL_SCANCODE_DOWN]) {
            player->dy = PLAYER_SPEED;
        }

        if (app.keyboard[SDL_SCANCODE_LEFT]) {
            player->dx = -PLAYER_SPEED;
        }

        if (app.keyboard[SDL_SCANCODE_RIGHT]) {
            player->dx = PLAYER_SPEED;
        }

        if (app.keyboard[SDL_SCANCODE_LCTRL] && player->reload <= 0) {
            app.getSoundManager().playSound(SND_PLAYER_FIRE, CH_PLAYER);
            fireBullet();
        }
        if (app.keyboard[SDL_SCANCODE_ESCAPE]) {
            exit(0);
        }
    }
}

void Stage::fireBullet() {
    Entity *bullet = new Entity();
    bullet->x = player->x + player->w;
    bullet->y = player->y;
    bullet->w = 0;
    bullet->h = 0;
    bullet->dx = PLAYER_BULLET_SPEED;
    bullet->dy = 0.0f;
    bullet->health = 1;
    bullet->reload = 0;
    bullet->side = SIDE_PLAYER;
    bullet->texture = bulletTexture;
    bullet->next = nullptr;
    bulletTail->next = bullet;
    bulletTail = bullet;

    SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

    bullet->y += (player->h / 2) - (bullet->h / 2);
    player->reload = 8;
}

void Stage::doEnemies() {
    for (Entity *e = fighterHead.next; e != nullptr; e = e->next) {
        if (e != player && player != nullptr && --e->reload <= 0) {
            fireAlienBullet(e);
            app.getSoundManager().playSound(SND_ALIEN_FIRE, CH_ALIEN_FIRE);
        }
    }
}

void Stage::fireAlienBullet(Entity *e) {
    Entity *bullet = new Entity();
    bullet->x = e->x;
    bullet->y = e->y;
    bullet->w = 0;
    bullet->h = 0;
    bullet->dx = ALIEN_BULLET_SPEED;
    bullet->dy = 0.0f;
    bullet->health = 1;
    bullet->reload = 0;
    bullet->side = SIDE_ALIEN;
    bullet->texture = alienBulletTexture;
    bullet->next = nullptr;
    bulletTail->next = bullet;
    bulletTail = bullet;

    SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

    bullet->x += (e->w / 2) - (bullet->w / 2);
    bullet->y += (e->h / 2) - (bullet->h / 2);

    Util::calcSlope(player->x + (player->w / 2), player->y + (player->h / 2), e->x, e->y, &bullet->dx, &bullet->dy);
    bullet->dx *= ALIEN_BULLET_SPEED;
    bullet->dy *= ALIEN_BULLET_SPEED;

    e->reload = (rand() % FPS * 2);
}

void Stage::doFighters() {
    /*
     * *e currently processed Entity
     * *prev previous Entity. Necessary for further remove of e
     */
    Entity *e = nullptr;
    Entity *prev = &fighterHead;

    for (e = fighterHead.next; e != nullptr; e = e->next) {
        // updating positions of all Entities (player, enemies, etc.)
        e->x += e->dx;
        e->y += e->dy;

        // if enemy or bullet is of the screen
        if (e != player && (e->x < -e->w)) {
            e->health = 0;
        }

        if (e->health <= 0) {
            if (e == player) {
                player = nullptr;
            }
            // if e is the last element of linked list, then
            // point the end of the linked list to previous element
            if (e == fighterTail) {
                fighterTail = prev;
            }
            // omitting e, so it could be safely removed
            prev->next = e->next;
            delete e;
            e = prev;
        }
        // sets prev for next iteration
        prev = e;
    }
}

void Stage::doBullets() {
    Entity *b = nullptr;
    Entity *prev = &bulletHead;

    for (b = bulletHead.next; b != nullptr; b = b->next) {
        b->x += b->dx;
        b->y += b->dy;

        if (bulletHitFighter(b) || b->x < -b->w || b->y < -b->h || b->x > SCREEN_WIDTH || b->y > SCREEN_HEIGHT) {
            if (b == bulletTail) {
                bulletTail = prev;
            }
            prev->next = b->next;
            delete b;
            b = prev;
        }
        prev = b;
    }
}

int Stage::bulletHitFighter(Entity *b) {
    for (Entity *e = fighterHead.next; e != nullptr; e = e->next) {
        if (e->side != b->side && Util::collision(b->x, b->y, b->w, b->h, e->x, e->y, e->w, e->h)) {
            b->health = 0;
            e->health -= 1;
            addExplosions(e->x, e->y, 32);
            addDebris(e);

            if (e->health <= 0) {
                if (e == player) {
                    app.getSoundManager().playSound(SND_PLAYER_DIE, CH_PLAYER);
                } else {
                    addPointsPod(e->x + e->w / 2, e->y + e->h / 2);
                    app.getSoundManager().playSound(SND_ALIEN_DIE, CH_ANY);
                }
            }
            return 1;
        }
    }
    return 0;
}

void Stage::spawnEnemies() {
    if (--enemySpawnTimer <= 0) {
        Entity *enemy = new Entity();
        enemy->x = SCREEN_WIDTH;
        enemy->y = rand() % SCREEN_HEIGHT;
        enemy->w = 0;
        enemy->h = 0;
        enemy->dx = -(2 + (rand() % 4));
        enemy->dy = 0.0f;
        enemy->health = rand() % 4;
        enemy->reload = FPS * (1 + (rand() % 3));
        enemy->side = SIDE_ALIEN;
        enemy->texture = enemyTexture;
        enemy->next = nullptr;

        fighterTail->next = enemy;
        fighterTail = enemy;

        SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->w, &enemy->h);

        // ensure that enemy will not fire during spawn
        enemySpawnTimer = 30 + (rand() % FPS);
    }
}

void Stage::clipPlayer() {
    if (player != nullptr) {
        if (player->x < 0) {
            player->x = 0;
        }

        if (player->y < 0) {
            player->y = 0;
        }

        if (player->x > (SCREEN_WIDTH - player->w)) {
            player->x = SCREEN_WIDTH - player->w;
        }

        if (player->y > SCREEN_HEIGHT - player->h) {
            player->y = SCREEN_HEIGHT - player->h;
        }
    }
}

void Stage::doExplosions() {
    Explosion *e = nullptr;
    Explosion *prev = &explosionHead;

    for (e = explosionHead.next; e != nullptr; e = e->next) {
        e->x += e->dx;
        e->y += e->dy;

        // a is explosions alpha number
        if (--e->a <= 0) {
            if (e == explosionTail) {
                explosionTail = prev;
            }
            prev->next = e->next;
            delete e;
            e = prev;
        }
        prev = e;
    }
}

void Stage::doDebris() {
    Debris *d = nullptr;
    Debris *prev = &debrisHead;

    for (d = debrisHead.next; d != nullptr; d = d->next) {
        d->x += d->dx;
        d->y += d->dy;

        d->dy += 0.5;

        if (--d->life <= 0) {
            if (d == debrisTail) {
                debrisTail = prev;
            }

            prev->next = d->next;
            delete d;
            d = prev;
        }
        prev = d;
    }
}

void Stage::doPointsPods() {
    Entity *e = nullptr;
    Entity *prev = &pointsHead;

    for (e = pointsHead.next; e != nullptr; e = e->next) {
        if (e->x < 0) {
            e->x = 0;
            e->dx = -e->dx;
        }

        if (e->x + e->w > SCREEN_WIDTH) {
            e->x = SCREEN_WIDTH - e->w;
            e->dx = -e->dx;
        }

        if (e->y < 0) {
            e->y = 0;
            e->dy = -e->dy;
        }

        if (e->y + e->h > SCREEN_HEIGHT) {
            e->y = SCREEN_HEIGHT - e->h;
            e->dy = -e->dy;
        }

        e->x += e->dx;
        e->y += e->dy;

        if (player != nullptr && Util::collision(e->x, e->y, e->w, e->h, player->x, player->y, player->w, player->h)) {
            e->health = 0;
            score++;
            highscore = std::max(score, highscore);
            app.getSoundManager().playSound(SND_POINTS, CH_POINTS);
        }
        if (--e->health <= 0) {
            if (e == pointsTail) {
                pointsTail = prev;
            }
            prev->next = e->next;
            delete e;
            e = prev;
        }
        prev = e;
    }
}

void Stage::addExplosions(int x, int y, int num) {
    for (int i = 0; i < num; i++) {
        Explosion *e = new Explosion();

        e->x = x + (rand() % 32) - (rand() % 32);
        e->y = y + (rand() % 32) - (rand() % 32);
        e->dx = (rand() % 10) - (rand() % 10);
        e->dy = (rand() % 10) - (rand() % 10);
        e->r = 0;
        e->g = 0;
        e->b = 0;
        e->a = 0;
        e->next = nullptr;

        explosionTail->next = e;
        explosionTail = e;

        e->dx /= 10;
        e->dy /= 10;

        switch (rand() % 4) {
            case 0:
                e->r = 255;
                break;
            case 1:
                e->r = 255;
                e->g = 128;
                break;
            case 2:
                e->r = 255;
                e->g = 255;
                break;
            default:
                e->r = 255;
                e->g = 255;
                e->b = 255;
                break;
        }

        e->a = rand() % FPS * 3;
    }
}

void Stage::addDebris(Entity *e) {
    int w = e->w / 2;
    int h = e->h / 2;

    for (int y = 0; y <= h; y += h) {
        for (int x = 0; x <= w; x += w) {
            Debris *d = new Debris();
            d->x = e->x + e->w / 2;
            d->y = e->y + e->h / 2;
            d->dx = (rand() % 5) - (rand() % 5);
            d->dy = -(5 + (rand() % 12));
            d->rect.x = x;
            d->rect.y = y;
            d->rect.w = w;
            d->rect.h = h;
            d->texture = e->texture;
            d->life = FPS * 2;
            d->next = nullptr;

            debrisTail->next = d;
            debrisTail = d;
        }
    }
}

void Stage::addPointsPod(int x, int y) {
    Entity *e = new Entity();
    e->x = x;
    e->y = y;
    e->w = 0;
    e->h = 0;
    e->dx = -(rand() % 5);
    e->dy = (rand() % 5) - (rand() % 5);
    e->health = FPS * 10;
    e->reload = 0;
    e->side = 0;
    e->texture = pointsTexture;
    e->next = nullptr;

    pointsTail->next = e;
    pointsTail = e;

    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);

    e->x -= e->w / 2;
    e->y -= e->h / 2;
}

void Stage::draw() {
    drawBackground();
    drawStarfield();
    drawPointsPods();
    drawFighters();
    drawDebris();
    drawExplosions();
    drawBullets();
    drawHud();
}

void Stage::drawPointsPods() {
    for (Entity *e = pointsHead.next; e != nullptr; e = e->next) {
        app.getRendererObj()->blit(e->texture, e->x, e->y);
    }
}

void Stage::drawFighters() {
    for (Entity *e = fighterHead.next; e != nullptr; e = e->next) {
        app.getRendererObj()->blit(e->texture, e->x, e->y);
    }
}

void Stage::drawBullets() {
    for (Entity *b = bulletHead.next; b != nullptr; b = b->next) {
        app.getRendererObj()->blit(b->texture, b->x, b->y);
    }
}

void Stage::drawStarfield() {
    int c;
    for (int i = 0; i < MAX_STARS; i++) {
        c = 32 * stars[i].speed;

        SDL_SetRenderDrawColor(app.renderer, c, c, c, 255);
        SDL_RenderDrawLine(app.renderer, stars[i].x, stars[i].y, stars[i].x + 3, stars[i].y);
    }
}

void Stage::drawBackground() {
    SDL_Rect dest;
    for (int x = backgroundX; x < SCREEN_WIDTH; x += SCREEN_WIDTH) {
        dest.x = x;
        dest.y = 0;
        dest.w = SCREEN_WIDTH;
        dest.h = SCREEN_HEIGHT;
        SDL_RenderCopy(app.renderer, background, NULL, &dest);
    }
}

void Stage::drawDebris() {
    for (Debris *d = debrisHead.next; d != nullptr; d = d->next) {
        app.getRendererObj()->blitRect(d->texture, &d->rect, d->x, d->y);
    }
}

void Stage::drawExplosions() {
    SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_ADD);
    SDL_SetTextureBlendMode(explosionTexture, SDL_BLENDMODE_ADD);

    for (Explosion *e = explosionHead.next; e != nullptr; e = e->next) {
        SDL_SetTextureColorMod(explosionTexture, e->r, e->g, e->b);
        SDL_SetTextureAlphaMod(explosionTexture, e->a);
        app.getRendererObj()->blit(explosionTexture, e->x, e->y);
    }
    // reset BLENDMODE
    SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);
}

void Stage::drawHud() {
    app.getTextManager().drawText(10, 10, 255, 255, 255, "SCORE: %03d", score);

    if (score > 0 && score == highscore) {
        app.getTextManager().drawText(960, 10, 0, 255, 0, "HIGH SCORE: %03d", highscore);
    } else {
        app.getTextManager().drawText(960, 10, 255, 255, 255, "HIGH SCORE: %03d", highscore);
    }
}
