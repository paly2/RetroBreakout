#include <SDL/SDL.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>

#include "defines.h"
#include "racquet.h"
#include "ball.h"
#include "brick.h"
#include "level.h"

using namespace std;

int main (int argc, char** argv) {
    // initialize SDL video
    if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
        cout << "Unable to init SDL: " << SDL_GetError() << endl;
        return 1;
    }
    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window with a title
    SDL_Surface *screen = SDL_SetVideoMode(640, 480, 16, SDL_HWSURFACE|SDL_DOUBLEBUF);
    if (!screen) {
        cout << "Unable to set 640x480 video: " << SDL_GetError() << endl;
        return 1;
    }
    SDL_WM_SetCaption("Retro Breakout!", NULL);

    // disable cursor
    SDL_ShowCursor(SDL_DISABLE);

    // construct racquet and ball
    Racquet racquet(screen);
    Ball ball(screen, &racquet);
    // load level
    level::load(screen, &ball, 1);

    // Time...
    Uint32 last_time = SDL_GetTicks();
    Uint32 current_time,ellapsed_time;
    Uint32 start_time;

    // program main loop
    bool done = false;
    bool pause = false;
    while (!done) {
        // message processing loop
        start_time = SDL_GetTicks();
        int racket_x = racquet.get_x();
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            // check for messages
            switch (event.type) {
            case SDL_QUIT: // exit if the window is closed
                done = true;
                break;

            // check for keypresses
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE: // exit if ESCAPE is pressed
                    done = true;
                    break;
                case SDLK_RETURN: // run the ball if RETURN is pressed
                    ball.run(true);
                    break;
                case SDLK_p: // pause if P pressed
                    pause = !pause;
                    break;
                }
                break;
            case SDL_MOUSEMOTION:
                racket_x = event.motion.x;
                break;
            }
        }
        current_time = SDL_GetTicks();
        ellapsed_time = current_time - last_time;
        last_time = current_time;

        if(!pause) {
            SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0)); // Clear screen
            racquet.draw(racket_x); // Draw racquet
            if(ball.handle(ellapsed_time)) // Handle ball
                level::load(screen, &ball, 1);
            level::draw(); // Draw level

            SDL_Flip(screen); // Update screen
        }

        ellapsed_time = SDL_GetTicks() - start_time;
        if (ellapsed_time < 20) {
            SDL_Delay(20 - ellapsed_time);
        }
    }

    return 0;
}
