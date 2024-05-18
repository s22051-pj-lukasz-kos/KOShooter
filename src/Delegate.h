#ifndef DELEGATE_H
#define DELEGATE_H

#include <functional>

/*
 * Delegate for handling the logic and draw functions in the game's main loop
 */
class Delegate {
public:
    std::function<void()> logic;

    std::function<void()> draw;
};

#endif // DELEGATE_H
