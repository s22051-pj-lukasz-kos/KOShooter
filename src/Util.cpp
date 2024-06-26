#include "Util.h"
#include "common.h"

int Util::collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
    return (MAX(x1, x2) < MIN(x1 + w1, x2 + w2)) && (MAX(y1, y2) < MIN(y1 + h1, y2 + h2));
}

/*
 * Calculate normalized steps from one point to another
 * Use case: for calc bullet steps/path from enemy (2) to player position (1)
 */
void Util::calcSlope(int x1, int y1, int x2, int y2, float *dx, float *dy) {
    int steps = MAX(abs(x1 - x2), abs(y1 - y2));

    if (steps == 0) {
        *dx = 0;
        *dy = 0;
        return;
    }

    *dx = static_cast<float>(x1 - x2) / steps;
    *dy = static_cast<float>(y1 - y2) / steps;
}