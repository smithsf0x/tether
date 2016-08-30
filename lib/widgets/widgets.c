#include "widgets.h"

void getMousePosition(void ){
    widgetMouseState = SDL_GetMouseState(&widgetMousePosX, &widgetMousePosY);
}


_widget* createWidget(widget_type type, widget_style* style, int w, int h){
    _widget* widget = malloc(sizeof(widget));

    if(type == wtButton){ widget->data = malloc(sizeof(_widget_button)); }
    else if(type == wtToggle){ widget->data = malloc(sizeof(_widget_button)); }
    else {
      free(widget);
      return NULL;
    }
    widget->state = STATE_IDLE;
    widget->h = h;
    widget->w = w;
    widget->rect.x = 0;
    widget->rect.y = 0;
    widget->rect.w = w;
    widget->rect.h = h;

    widget->style = *style;
    widget->surface = SDL_CreateRGBSurface(0,w,h,32,0,0,0,0);
    SDL_FillRect(
        widget->surface,
        &widget->rect,
        SDL_MapRGBA(
            widget->surface->format,
            widget->style.background.r,
            widget->style.background.g,
            widget->style.background.b,
            widget->style.background.a
        )
    );

    return widget;
}

widget_state getWidgetState(_widget* widget){
  if(widgetMousePosX >= widget->rect.x && widgetMousePosX <= widget->rect.x + widget->w){
      if(widgetMousePosY >= widget->rect.y && widgetMousePosY <= widget->rect.y + widget->h  ){
          if(WIDGET_MOUSE_BUTTON(SDL_BUTTON_LEFT)){ return STATE_LMB; }
          if(WIDGET_MOUSE_BUTTON(SDL_BUTTON_RIGHT)){ return STATE_RMB; }
          return STATE_HOVER;
      }
  }
  return STATE_IDLE;
}

int drawWidget(SDL_Renderer* renderer, _widget* widget, int x, int y){
  _widget_color color;

  int hovered = getWidgetState(widget);
  int stateFlag = 0;

  widget->rect.x = x;
  widget->rect.y = y;

  if(hovered != widget->state){
    stateFlag = 1;
    printfError(TINFO, "Changed// widget->state == %d  hovered == %d \n", widget->state, hovered);
  }

  if(hovered == STATE_HOVER){
      widget->state = STATE_HOVER;
      color = widget->style.active;
  }else{
      widget->state = STATE_IDLE;
      color = widget->style.background;
  }

  if(stateFlag){
      printf("state flag !!\n");
      SDL_FillRect(
          widget->surface,
          &widget->rect,
          SDL_MapRGBA(
              widget->surface->format,
              color.r,
              color.g,
              color.b,
              color.a
          )
      );
  }



  widget->texture = SDL_CreateTextureFromSurface(renderer, widget->surface);
  return SDL_RenderCopy(
      renderer,
      widget->texture,
      NULL,
      &widget->rect
  );
}

int widgetSetColor(_widget_color* color, Uint8 r, Uint8 g, Uint8 b, Uint8 a){
    if(color == NULL) { return 0; }
    color->r = r;
    color->g = g;
    color->b = b;
    color->a = a;
    return 0;
}
