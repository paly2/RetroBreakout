#ifndef RACQUET_H_INCLUDED
#define RACQUET_H_INCLUDED

#include <SDL/SDL.h>

class Racquet {
    public:
    Racquet(SDL_Surface *screen);
    ~Racquet();
    void draw(int new_x);
    void draw();
    int get_x() {
        return x;
    }

    private:
    int x;
    SDL_Surface *surface, *screen;
};

#endif // RACQUET_H_INCLUDED
