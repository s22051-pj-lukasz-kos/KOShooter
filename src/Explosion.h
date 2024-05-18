#ifndef EXPLOSION_H
#define EXPLOSION_H

/*
 * Represent explosions when fighter die
 */
class Explosion {
public:
    Explosion();

    float x, y;
    float dx, dy;
    int r, g, b, a;
    Explosion *next;
};

#endif // EXPLOSION_H
