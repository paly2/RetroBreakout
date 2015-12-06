#include <SDL/SDL.h>
#include "defines.h"
#include "racquet.h"

Racquet::Racquet(SDL_Surface *screen) : screen(screen) {
    surface = SDL_CreateRGBSurface(SDL_HWSURFACE, RACQUET_LENGHT, RACQUET_HEIGHT, 16, 0, 0, 0, 0);
    draw(320);
}

Racquet::~Racquet() {
    SDL_FreeSurface(surface);
}

void Racquet::draw(int new_x) {
    x = new_x;
    if(x < 20 + RACQUET_LENGHT/2)
        x = 20 + RACQUET_LENGHT/2;
    else if(x > 620 - RACQUET_LENGHT/2)
        x = 620 - RACQUET_LENGHT/2;
    SDL_Rect racquet_pos;
    racquet_pos.x = x - RACQUET_LENGHT/2;
    racquet_pos.y = 460;
    SDL_FillRect(surface, NULL, SDL_MapRGB(screen->format, 62, 209, 57));
    SDL_BlitSurface(surface, NULL, screen, &racquet_pos);
}
void Racquet::draw() {
    SDL_Rect racquet_pos;
    racquet_pos.x = x - RACQUET_LENGHT/2;
    racquet_pos.y = 460;
    SDL_FillRect(surface, NULL, SDL_MapRGB(screen->format, 62, 209, 57));
    SDL_BlitSurface(surface, NULL, screen, &racquet_pos);
}
