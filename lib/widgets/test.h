#include "widgets.h"
#include "../printerr/printerr.h"

#define EC_SDL_INIT     -10
#define EC_WIN_CREATE   -12
#define EC_TET_INIT     -20

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 768;


SDL_Window* mainWindow;
SDL_Renderer* renderer;
