#ifndef BRICK_H_INCLUDED
#define BRICK_H_INCLUDED

#include <SDL/SDL.h>
#include "ball.h"

enum brick_type { NONE = '0', RED = '1', ORANGE = '2', BLUE1 = '3', BLUE2 = '4', GREEN1 = '5', GREEN2 = '6', YELLOW = '7', GREY = '8', WHITE  = '9', UNBREAKABLE = 'U' };

class Brick {
    public:
    Brick();
    ~Brick();
    void coords(int i, int j, SDL_Surface *screen_, Ball *ball_);
    brick_type get_type() {
        return type;
    }
    void set_type(brick_type new_type) {
        type = new_type;
    }
    bool handle(int& brick_number);

    private:
    void draw();
    brick_type type;
    SDL_Surface *surface, *screen;
    SDL_Rect brick_pos;
    Ball *ball;
};

#endif // BRICK_H_INCLUDED
