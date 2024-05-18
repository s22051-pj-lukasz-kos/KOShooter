#include "Debris.h"

Debris::Debris() : x(0), y(0), dx(0), dy(0), texture(nullptr), life(0), next(nullptr) {
    rect = {0, 0, 0, 0};
}