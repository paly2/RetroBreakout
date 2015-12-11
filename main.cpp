#include <SDL/SDL.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <cstring>

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

    // create a new window with a title and an icon
    SDL_WM_SetIcon(SDL_LoadBMP("icon.bmp"), NULL);
    SDL_Surface *screen = NULL;
    if(strcmp(argv[argc-1], "--fullscreen") == 0)
        screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 16, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
    else
        screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 16, SDL_HWSURFACE|SDL_DOUBLEBUF);
    if (!screen) {
        cout << "Unable to set " << WINDOW_WIDTH << "x" << WINDOW_HEIGHT << " video: " << SDL_GetError() << endl;
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
    bool pause = false, focus = true, input_focus = true;
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
                case SDLK_g:
                    if(SDL_WM_GrabInput(SDL_GRAB_QUERY) == SDL_GRAB_OFF)
                        SDL_WM_GrabInput(SDL_GRAB_ON);
                    else
                        SDL_WM_GrabInput(SDL_GRAB_OFF);
                    break;
                case SDLK_F5:
                    SDL_WM_ToggleFullScreen(screen);
                    break;
                case SDLK_KP1:
                    ball.set_difficulty(1);
                    break;
                case SDLK_KP2:
                    ball.set_difficulty(2);
                    break;
                case SDLK_KP3:
                    ball.set_difficulty(3);
                    break;
                case SDLK_KP4:
                    ball.set_difficulty(4);
                    break;
                case SDLK_KP5:
                    ball.set_difficulty(5);
                    break;
                case SDLK_KP6:
                    ball.set_difficulty(6);
                    break;
                case SDLK_KP7:
                    ball.set_difficulty(7);
                    break;
                case SDLK_KP8:
                    ball.set_difficulty(8);
                    break;
                case SDLK_KP9:
                    ball.set_difficulty(9);
                    break;
                }
                break;
            case SDL_MOUSEMOTION:
                racket_x = event.motion.x;
                break;
            case SDL_ACTIVEEVENT:
                if((event.active.state & SDL_APPMOUSEFOCUS) == SDL_APPMOUSEFOCUS) {
                    if(event.active.gain == 0)
                        focus = false;
                    else if(event.active.gain == 1 && input_focus)
                        focus = true;
                }
                if((event.active.state & SDL_APPINPUTFOCUS) == SDL_APPINPUTFOCUS) {
                    if(event.active.gain == 0) {
                        input_focus = false;
                        focus = false;
                    }
                    else if(event.active.gain == 1) {
                        input_focus = true;
                        focus = true;
                    }
                }
                break;
            }
        }
        current_time = SDL_GetTicks();
        ellapsed_time = current_time - last_time;
        last_time = current_time;

        if(!pause && focus) {
            SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0)); // Clear screen
            racquet.draw(racket_x); // Draw racquet
            if(ball.handle(ellapsed_time)) // Handle ball
                level::load(screen, &ball, 1);
            level::draw(); // Draw level

            SDL_Flip(screen); // Update screen
        }

        ellapsed_time = SDL_GetTicks() - start_time;
        if (ellapsed_time < 12) {
            SDL_Delay(12 - ellapsed_time);
        }
    }

    return 0;
}
