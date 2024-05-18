#ifndef UTIL_H
#define UTIL_H

class Util {
public:
    static int collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);

    static void calcSlope(int x1, int y1, int x2, int y2, float *dx, float *dy);
};

#endif // UTIL_H
