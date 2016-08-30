#define PRINT_ERR 1

#include "test.h"

int doCleanExit(int exitCode){
	if(mainWindow != NULL){
		SDL_DestroyWindow(mainWindow);
	}
	SDL_Quit();
	return exitCode;
}

int main(int argc, char const *argv[]) {

    printfError(TINFO, "Starting...\n");
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
			printfError(TERRO, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
			return doCleanExit(EC_SDL_INIT);
		}
    printfError(TINFO, "Initiated\n");
		mainWindow = SDL_CreateWindow(
			"tether",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN
		);
    printfError(TINFO, "Window is there...\n");
		if( mainWindow == NULL ) {
			printfError(TERRO, "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			return doCleanExit(EC_WIN_CREATE);
		}

		renderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
    printfError(TINFO, "renderer is there...\n");
    const uint8_t *keys = SDL_GetKeyboardState(NULL);
    printfError(TINFO, "got keyboard state...\n");
    SDL_Event e;
		int quit = 0;
    quit = 0;

    widget_style testStyle;

    widgetSetColor(&testStyle.background, 0, 20, 20, 255);
    widgetSetColor(&testStyle.active, 255, 20, 20, 255);

		_widget* testWidget = createWidget(wtButton, &testStyle, 80, 30);

    printfError(TINFO, "before first round...\n");
		do{
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
				while( SDL_PollEvent( &e ) != 0 ){
					if( e.type == SDL_QUIT ){
		                quit = 1;
		            }
					if (keys[SDL_SCANCODE_ESCAPE]){
						quit = 1;
					}
        }
        getMousePosition( );

        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);

        // Clear the entire screen to our selected color.
        if(getWidgetState(testWidget) == STATE_LMB){
            quit = 1;
        }

        SDL_RenderClear(renderer);
				drawWidget(renderer, testWidget, 50, 50);

        SDL_RenderPresent(renderer);

    }while(!quit);

    return 0;
}
