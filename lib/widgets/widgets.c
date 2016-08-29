#include "widgets.h"

void getMousePosition(void ){
    widgetMouseState = SDL_GetMouseState(&widgetMousePosX, &widgetMousePosY);
}

int widgetSetColor(_widget_color* color, Uint8 r, Uint8 g, Uint8 b, Uint8 a){
    if(color == NULL) { return 0; }
    color->r = r;
    color->g = g;
    color->b = b;
    color->a = a;
    return 0;
}

widget_button* newWidgetButton(char* text,widget_style* style, int w, int h){
    widget_button* button = malloc(sizeof(button));
    button->text = text;
    button->h = h;
    button->w = w;
    button->rect.x = 0;
    button->rect.y = 0;
    button->rect.w = w;
    button->rect.h = h;

    button->style = *style;
    button->surface = SDL_CreateRGBSurface(0,w,h,32,0,0,0,0);
    SDL_FillRect(
        button->surface,
        &button->rect,
        SDL_MapRGBA(
            button->surface->format,
            button->style.background.r,
            button->style.background.g,
            button->style.background.b,
            button->style.background.a
        )
    );
    return button;
}

int drawWidgetButton(SDL_Renderer* renderer, widget_button* button, int x, int y){
    button->rect.x = x;
    button->rect.y = y;

    int hovered = isWidgetButtonHovered(button);
    int stateFlag = STATE_IDLE;
    if(hovered != button->state){
        stateFlag = 1;
    }

    _widget_color color;

    if(hovered){
        button->state = STATE_HOVER;
        color = button->style.active;
    }else{
        button->state = STATE_IDLE;
        color = button->style.background;
    }
    if(stateFlag){
        SDL_FillRect(
            button->surface,
            &button->rect,
            SDL_MapRGBA(
                button->surface->format,
                color.r,
                color.g,
                color.b,
                color.a
            )
        );
    }


    button->texture = SDL_CreateTextureFromSurface(renderer, button->surface);
    return SDL_RenderCopy(
        renderer,
        button->texture,
        NULL,
        &button->rect
    );

}

int isWidgetButtonHovered(widget_button* button){
    if(widgetMousePosX >= button->rect.x && widgetMousePosX <= button->rect.x + button->w){
        if(widgetMousePosY >= button->rect.y && widgetMousePosY <= button->rect.y + button->h  ){
            return STATE_HOVER;
        }
    }
    return STATE_IDLE;
}

int getWidgetButtonState(widget_button* button){
    if(isWidgetButtonHovered(button)){
        if(WIDGET_MOUSE_BUTTON(SDL_BUTTON_LEFT)){ return SDL_BUTTON_LEFT; }
        if(WIDGET_MOUSE_BUTTON(SDL_BUTTON_RIGHT)){ return SDL_BUTTON_RIGHT; }
        return STATE_HOVER;
    }
    return STATE_IDLE;
}

int isWidgetButtonPressed(widget_button* button){
    if(isWidgetButtonHovered(button)){
        if(WIDGET_MOUSE_BUTTON(SDL_BUTTON_LEFT)){ return SDL_BUTTON_LEFT; }
        if(WIDGET_MOUSE_BUTTON(SDL_BUTTON_RIGHT)){ return SDL_BUTTON_RIGHT; }
    }
    return STATE_IDLE;
}

int freeWidgetButton(widget_button* button){

    free(button);
    return 0;
}
