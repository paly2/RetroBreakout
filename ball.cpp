#include <SDL/SDL.h>
#include <iostream>
#include "defines.h"
#include "ball.h"

using namespace std;

Ball::Ball(SDL_Surface *screen, Racquet *racquet) : screen(screen), racquet(racquet) {
    surface = SDL_CreateRGBSurface(SDL_HWSURFACE, BALL_SIDE, BALL_SIDE, 16, 0, 0, 0, 0);
    x = 315;
    y = 445;
    draw();
    x_vel = 0;
    y_vel = 0;
}
Ball::~Ball() {
    SDL_FreeSurface(surface);
}

void Ball::run(bool move) {
    x = 315;
    y = 445;
    x_vel = 0;
    y_vel = (move) ? BALL_Y_SPEED : 0;
}

bool Ball::handle(int ellapsed_time) {
    x = x - x_vel*ellapsed_time/1000.0;
    y = y - y_vel*ellapsed_time/1000.0;
    if(y < 20)
        rebound_y(); // Rebound on the edge !
    else if(x < 20)
        rebound_x(); // Rebound on the edge !
    else if(x > 620)
        rebound_x(); // Rebound on the edge !
    else if(y > 470) {
        cout << "You lost !" << endl;
        return true;
    }
    else if(y > 455 &&
            racquet->get_x()-RACQUET_LENGHT/2 < x && racquet->get_x()+RACQUET_LENGHT/2 > x) { // Racquet collision ?
        rebound_y(); // Rebound on the racquet !
        x_vel=(racquet->get_x()-x)*10; // Change the horizontal velocity
    }
    draw();
    return false;
}

void Ball::draw() {
    SDL_Rect ball_pos;
    ball_pos.x = (int)x - BALL_SIDE/2;
    ball_pos.y = (int)y - BALL_SIDE/2;
    SDL_FillRect(surface, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
    SDL_BlitSurface(surface, NULL, screen, &ball_pos);
}
