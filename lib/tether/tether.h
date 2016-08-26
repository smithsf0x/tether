#ifndef TETHER_H
#define TETHER_H

#include <SDL2/SDL.h>

typedef struct{
  SDL_Surface* viewSurface;
  int* data;
} TETHER;

typedef struct{
  int number;
  int flag;
} TET_STATE;

TETHER* iniTether(SDL_Window* window);

int tetherFetchData(TETHER* tether);
int tetherProcessData(TETHER* tether);
int tetherFreeData(TETHER* tether);

int tetherResolveState(TET_STATE state);


#endif
