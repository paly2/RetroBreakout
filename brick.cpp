#include <SDL/SDL.h>
#include <cstdio>
#include <iostream>

#include "brick.h"
#include "ball.h"
#include "defines.h"

using namespace std;

Brick::Brick() {
    surface = SDL_CreateRGBSurface(SDL_HWSURFACE, BRICK_LENGHT, BRICK_HEIGHT, 16, 0, 0, 0, 0);
}
Brick::~Brick() {
    SDL_FreeSurface(surface);
}

void Brick::coords(int i, int j, SDL_Surface *screen_, Ball *ball_) {
    brick_pos.x = 20+BRICK_LENGHT*(j);
    brick_pos.y = 20+BRICK_HEIGHT*(i);
    screen = screen_;
    ball = ball_;
}

void Brick::draw() {
    int r = 0, g = 0, b = 0;
    switch(type) {
        case RED:
            r = 255; g = 0; b = 0;
            break;
        case ORANGE:
            r = 255; g = 128; b = 0;
            break;
        case BLUE1:
            r = 0; g = 0; b = 255;
            break;
        case BLUE2:
            r = 0; g = 255; b = 255;
            break;
        case GREEN1:
            r = 0; g = 153; b = 0;
            break;
        case GREEN2:
            r = 51; g = 255; b = 51;
            break;
        case YELLOW:
            r = 255; g = 255; b = 0;
            break;
        case GREY:
            r = 96; g = 96; b = 96;
            break;
        case WHITE:
            r = 190; g = 190; b = 190;
            break;
        case UNBREAKABLE:
            r = 255; g = 255; b = 255;
    }
    SDL_FillRect(surface, NULL, SDL_MapRGB(screen->format, r, g, b));
    SDL_BlitSurface(surface, NULL, screen, &brick_pos);
}

bool Brick::handle(int& brick_number) {
    if(type == NONE)
        return false;

    bool broken = false;

    if(ball->get_x() > brick_pos.x && ball->get_x() < brick_pos.x+BRICK_LENGHT) {
        if(ball->get_y()-BALL_SIDE/2 < brick_pos.y+BRICK_HEIGHT && ball->get_y()+BALL_SIDE/2 > brick_pos.y) { // Rebound on the top/bottom edge ?
            ball->rebound_y();
            if(type != UNBREAKABLE) {
                set_type(NONE);
                broken = true;
            }
        }
    }
    else if(ball->get_y() > brick_pos.y && ball->get_y() < brick_pos.y+BRICK_HEIGHT) {
        if(ball->get_x()-BALL_SIDE/2 < brick_pos.x+BRICK_LENGHT && ball->get_x()+BALL_SIDE/2 > brick_pos.x) { // Rebound on the right/left edge ?
            ball->rebound_x();
            if(type != UNBREAKABLE) {
                set_type(NONE);
                broken = true;
            }
        }
    }
    draw();

    if(broken) {
        brick_number--;
        cout << "Brick broken ! There remains " << brick_number << " bricks." << endl;
        if(brick_number == 0) {
            cout << "You won !" << endl;
            return true;
        }
    }

    return false;
}
