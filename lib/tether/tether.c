#include "tether.h"

TETHER* iniTether(SDL_Window* window){
  TETHER* newTether = malloc(sizeof(newTether));

  newTether->viewSurface = SDL_GetWindowSurface( window );

  return newTether;
}

int tetherFetchData(TETHER* tether){
  //


  return 0;
}
int tetherProcessData(TETHER* tether){

  return 0;
}

int tetherFreeData(TETHER* tether){
  free(tether->data);
  return 0;
}
