#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include <SDL/SDL.h>
#include "racquet.h"

class Ball {
    public:
    Ball(SDL_Surface *screen, Racquet *racquet);
    ~Ball();
    bool handle(int ellapsed_time);
    void run(bool move);
    int get_x() {
        return x;
    }
    int get_y() {
        return y;
    }
    void set_difficulty(int new_difficulty);
    void rebound(int direction);

    private:
    void calc_vel(const double Radians);
    void draw();
    double x, y;
    int x_vel, y_vel, vel;
    int difficulty;
    double radians;
    SDL_Surface *surface, *screen;
    Racquet *racquet;
};

#endif // BALL_H_INCLUDED
