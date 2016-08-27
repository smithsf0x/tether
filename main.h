#ifndef MAIN_H
#define MAIN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <stdio.h>
#include <unistd.h>
#include "lib/tether/tether.h"

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

/* ExitCodes */
#define EC_SDL_INIT     -10
#define EC_WIN_CREATE   -12
#define EC_TET_INIT     -20

#define STATE_OK        1


typedef struct{
    int code;
}STATE;




#endif
