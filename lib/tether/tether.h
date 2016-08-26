#ifndef TETHER_H
#define TETHER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <gphoto2/gphoto2.h>
#include "helper.h"

typedef struct{
  Camera* camera;
  GPContext* context;
} TETHER_CAMERA;

typedef struct{
  SDL_Surface* viewSurface;
  SDL_Texture* viewTexture;
  SDL_Renderer* renderer;
  TETHER_CAMERA* camera;
  int* data;
  CameraFile* file;
} TETHER;



typedef struct{
  int number;
  int flag;
} TET_STATE;

TETHER* iniTether(SDL_Window* window);
int tetherSetupCamera(TETHER* tether);
int tetherFetchData(TETHER* tether);
int tetherProcessData(TETHER* tether);
int tetherFreeData(TETHER* tether);

int tetherResolveState(TET_STATE state);


#endif
