#include <SDL/SDL.h>
#include <iostream>
#include <cmath>
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
    difficulty = DEFAULT_DIFFICULTY;
    min_difficulty = 0;
}
Ball::~Ball() {
    SDL_FreeSurface(surface);
}

void Ball::rebound(int direction) {
    if(direction == -1 && x_vel > 0 ||
       direction == 1 && x_vel < 0)
        x_vel *= -1;
    else if(direction == -2 && y_vel > 0 ||
            direction == 2 && y_vel < 0)
        y_vel *= -1;
}

void Ball::calc_vel(const double Radians) {
    radians = Radians;
    y_vel = cos(radians)*vel;
    x_vel = sin(radians)*vel;
}

void Ball::run(bool move) {
    x = 315;
    y = 445;
    vel = (move) ? difficulty*100 : 0;
    calc_vel(0);
    if(min_difficulty == 0 && move == true)
        min_difficulty = difficulty;
}

void Ball::set_difficulty(int new_difficulty) {
    difficulty = new_difficulty;
    if(difficulty < min_difficulty || min_difficulty == 0)
        min_difficulty = difficulty;
    vel = difficulty*100;
    if(y_vel == 0 && x_vel == 0)
        return;

    bool inv_y = false, inv_x = false;
    if(y_vel < 0)
        inv_y = true;
    if(x_vel > 0)
        inv_x = true;
    if(radians > 0)
        inv_x = !inv_x;
    calc_vel(radians);
    if(inv_y)
        y_vel *= -1;
    if(inv_x)
        x_vel *= -1;
}

bool Ball::handle(int ellapsed_time) {
    x = x - x_vel*ellapsed_time/1000.0;
    y = y - y_vel*ellapsed_time/1000.0;
    if(y < 20)
        rebound(-2); // Rebound on the top edge !
    else if(x < 20)
        rebound(-1); // Rebound on the right edge !
    else if(x > WINDOW_WIDTH-20)
        rebound(1); // Rebound on the left edge !
    else if(y > WINDOW_HEIGHT-10) {
        cout << "You lost !" << endl;
        return true;
    }
    else if(y > WINDOW_HEIGHT-25 &&
            racquet->get_x()-RACQUET_WIDTH/2 < x && racquet->get_x()+RACQUET_WIDTH/2 > x) { // Racquet collision ?
        rebound(2); // Rebound on the racquet !
        calc_vel((racquet->get_x()-x)*(M_PI_2/(RACQUET_WIDTH/2))); // Change radians
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
