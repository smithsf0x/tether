#ifndef WIDGETS_H
#define WIDGETS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include "../printerr/printerr.h"

#define WIDGET_MOUSE_BUTTON(x) (widgetMouseState & SDL_BUTTON(x))

typedef enum{
    idle,
    hover,
    clicked
}widget_button_state;

typedef enum{
  wtButton,
  wtToggle
}widget_type;

typedef enum{
  STATE_IDLE,
  STATE_LMB,
  STATE_RMB,
  STATE_MMB,
  STATE_HOVER
} widget_state;

typedef struct{
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
}_widget_color;

typedef struct{
    _widget_color background;
    _widget_color active;
} widget_style;

typedef struct{
  long _id;
  widget_type type;
  void* data;
  int w;
  int h;
  SDL_Rect rect;
  SDL_Surface* surface;
  SDL_Texture* texture;
  widget_style style;
  int state;
} _widget;

typedef struct{
  int state;
} _widget_button;

int widgetMousePosX;
int widgetMousePosY;
int widgetMouseState;

void getMousePosition(void );

int widgetSetColor(_widget_color*, Uint8, Uint8, Uint8, Uint8);

_widget* createWidget(widget_type, widget_style*, int, int);
widget_state getWidgetState(_widget*);
int drawWidget(SDL_Renderer*, _widget*, int, int);


#endif
