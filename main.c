#include "main.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main( int argc, char* args[] ){
	SDL_Window* window = NULL;
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

	tether = iniTether(window);

	do{
		tetherFetchData(tether);
		tetherProcessData(tether);
		// draw data


		tetherFreeData(tether);

	}while(0);

	SDL_FillRect( tether->viewSurface, NULL, SDL_MapRGB( tether->viewSurface->format, 0xFF, 0xFF, 0xFF ) );
	SDL_UpdateWindowSurface( window );
	SDL_Delay( 2000 );

	SDL_DestroyWindow( window );
	SDL_Quit();

	return 0;
}
