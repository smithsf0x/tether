#ifndef WIDGETS_H
#define WIDGETS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include "../printerr/printerr.h"

#define WIDGET_MOUSE_BUTTON(x) (widgetMouseState & SDL_BUTTON(x))

#define STATE_CLICK 16
#define STATE_HOVER 8
#define STATE_IDLE  0

typedef enum{
    idle,
    hover,
    clicked
}widget_button_state;

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
    int w;
    int h;
    char* text;
    SDL_Rect rect;
    SDL_Surface* surface;
    SDL_Texture* texture;
    widget_style style;
    int state;
}  widget_button;



int widgetMousePosX;
int widgetMousePosY;
int widgetMouseState;

void getMousePosition(void );

widget_button* newWidgetButton(char* ,widget_style*, int, int);

int widgetSetColor(_widget_color*, Uint8, Uint8, Uint8, Uint8);

int drawWidgetButton(SDL_Renderer*, widget_button* , int , int );
int isWidgetButtonPressed(widget_button* );
int isWidgetButtonHovered(widget_button* );
int freeWidgetButton(widget_button* );


#endif
