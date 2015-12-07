#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include <SDL/SDL.h>
#include "brick.h"
#include "ball.h"
#include <cstring>
#include <iostream>

using namespace std;

namespace level {
    extern Brick bricks[30][20];
    extern int brick_number;
    extern int level_number;

    extern SDL_Surface *screen;
    extern Ball *ball;

    void draw();
    void load(SDL_Surface *screen_, Ball *ball_, int Level_number);
}

#endif // LEVEL_H_INCLUDED
