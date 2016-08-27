#include "main.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 768;

int doCleanExit(int exitCode){
	if(mainWindow != NULL){
		SDL_DestroyWindow(mainWindow);
	}
	SDL_Quit();
	return exitCode;
}

int main( int argc, char* args[] ){
	mainWindow = NULL;
	renderer = NULL;
	tether = NULL;

	SDL_Surface* mainSurface = NULL;


	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		return doCleanExit(EC_SDL_INIT);
	}
	mainWindow = SDL_CreateWindow(
		"tether",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS | SDL_WINDOW_OPENGL
	);
	if( mainWindow == NULL ) {
		printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		return doCleanExit(EC_WIN_CREATE);
	}
	mainSurface = SDL_GetWindowSurface(mainWindow);
	renderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
	tether = iniTether(mainWindow);

	if(tether == NULL){
		printf("iniTether returned NULL\n");
		//return doCleanExit(EC_TET_INIT);
	}

	tetherSetupCamera(tether);
	tether->renderer = renderer;
	printf("set renderer\n");

	SDL_Rect textureTitleBar;
	textureTitleBar.x = 0;
	textureTitleBar.y = 0;
	textureTitleBar.w = SCREEN_WIDTH;
	textureTitleBar.h = 32;

	SDL_Rect textureBarLeft;
	textureBarLeft.x = 0;
	textureBarLeft.y = 32;
	textureBarLeft.w = 256;
	textureBarLeft.h = 768 - 32;

	SDL_Rect textureLiveView;
	textureLiveView.x = 256 + 64;  //the x coordinate
	textureLiveView.y = 32 + 64; // the y coordinate
	textureLiveView.w = 640; //the width of the texture
	textureLiveView.h = 426; //the height of the texture

	textureLiveView.x = 0;  //the x coordinate
	textureLiveView.y = 0; // the y coordinate
	textureLiveView.w = 1024; //the width of the texture
	textureLiveView.h = 1024; //the height of the texture

	SDL_Rect textureBarRight;
	textureBarRight.x = 256 + 64 + 64 + 640;
	textureBarRight.y = 32;
	textureBarRight.w = 256;
	textureBarRight.h = 768 - 32;

	SDL_Rect textureBarBottom;
	textureBarBottom.x = 256;
	textureBarBottom.y = 512 + 32 + 32;
	textureBarBottom.w = 768;
	textureBarBottom.h = 224 - 32;


	mainState.code = STATE_OK;
	int i = 0;

	do{

		/*
		SDL_FillRect( mainSurface, NULL, SDL_MapRGB( mainSurface->format, 0xFF, 0xFF, 0xFF ) );
		SDL_FillRect( mainSurface, &textureBarLeft, SDL_MapRGB( mainSurface->format, 255, 128, 128 ) );
		//SDL_FillRect( mainSurface, &textureLiveView   , SDL_MapRGB( mainSurface->format, 200, 0, 0 ) );
		SDL_FillRect( mainSurface, &textureBarRight, SDL_MapRGB( mainSurface->format, 64, 128, 64 ) );
		SDL_FillRect( mainSurface, &textureBarBottom, SDL_MapRGB( mainSurface->format, 64, 64, 64 ) );
		SDL_FillRect( mainSurface, &textureTitleBar, SDL_MapRGB( mainSurface->format, 0, 0, 0 ) );
	    //Update the surface
		SDL_UpdateWindowSurface( mainWindow );
		*/

		tetherFetchData(tether);
		tetherProcessData(tether);

		SDL_RenderClear(tether->renderer); //clears the renderer
		SDL_RenderCopy(tether->renderer, tether->viewTexture, NULL, &textureLiveView);
		SDL_RenderPresent(tether->renderer); //updates the renderer

		//tetherFreeData(tether);
		i++;
	}while(i < 100);


	SDL_UpdateWindowSurface( mainWindow );
	printf("after loop\n");

	SDL_Delay(500);
	SDL_DestroyWindow( mainWindow );
	SDL_Quit();

	return 0;
}
