#ifndef ENGELLER_H
#define ENGELLER_H

#include <SDL2/SDL.h>

struct Engel {
    SDL_Rect rect;
    int tip; // 0: Normal Spike, 1: Mini Spike, 2: Blok
    bool aktif;
};

#endif
