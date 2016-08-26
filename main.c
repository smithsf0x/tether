#include "main.h"

const int SCREEN_WIDTH = 1400;
const int SCREEN_HEIGHT = 850;

int main( int argc, char* args[] ){
	SDL_Window* window = NULL;
	SDL_Renderer* renderer;
	TETHER* tether;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		SDL_Quit();
		return EC_SDL_INIT;
	}
	window = SDL_CreateWindow( "tether", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if( window == NULL ) {
		printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EC_WIN_CREATE;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	tether = iniTether(window);

	tetherSetupCamera(tether);

	SDL_Rect texture_rect;
	texture_rect.x = 0;  //the x coordinate
	texture_rect.y = 0; // the y coordinate
	texture_rect.w = 1024; //the width of the texture
	texture_rect.h = 1024; //the height of the texture

	tether->renderer = renderer;
	int asdf = 0;
	do{
		tetherFetchData(tether);
		tetherProcessData(tether);

		SDL_RenderClear(tether->renderer); //clears the renderer
		SDL_RenderCopy(tether->renderer, tether->viewTexture, NULL, &texture_rect);
		SDL_RenderPresent(tether->renderer); //updates the renderer


		tetherFreeData(tether);
		asdf++;
	}while(asdf < 200);

	SDL_FillRect( tether->viewSurface, NULL, SDL_MapRGB( tether->viewSurface->format, 0xFF, 0xFF, 0xFF ) );
	SDL_UpdateWindowSurface( window );
	SDL_Delay( 2000 );

	SDL_DestroyWindow( window );
	SDL_Quit();

	return 0;
}
