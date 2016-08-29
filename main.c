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
	STATE mainState;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		printfError(TERRO, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		return doCleanExit(EC_SDL_INIT);
	}
	mainWindow = SDL_CreateWindow(
		"tether",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);
	if( mainWindow == NULL ) {
		printfError(TERRO, "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		return doCleanExit(EC_WIN_CREATE);
	}

	renderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
	tether = iniTether(mainWindow);
	int tetherWorking = 0;
	if(tether == NULL){
		tetherWorking = 0;
		printfError(TERRO, "iniTether returned");
		return doCleanExit(EC_TET_INIT);
	}

	tetherWorking = 1;
	int retsetup = tetherSetupCamera(tether);
	if(retsetup < 0){
		printfError(TWARN, "No Camera found\n");
	}
	tether->renderer = renderer;

	tetherWorking = 0;

	printfError(TINFO, "set rendererrr\n");

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

	printfError(TINFO, "tether working %d\n", tetherWorking);

	const uint8_t *keys = SDL_GetKeyboardState(NULL);
	SDL_Event e;
	int quit = 0;

	do{
		while( SDL_PollEvent( &e ) != 0 ){
			if( e.type == SDL_QUIT ){
                quit = 1;
            }
			if (keys[SDL_SCANCODE_ESCAPE]){
				quit = 1;
			}
        }

		if(tetherWorking){
			tetherFetchData(tether);
			tetherProcessData(tether);
		}


		SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
		SDL_RenderClear(renderer); //clears the renderer
		if(tetherWorking){
			SDL_RenderCopy(renderer, tether->viewTexture, NULL, &textureLiveView);
		}

		SDL_SetRenderDrawColor(renderer, 255, 128, 128, 255);
		SDL_RenderFillRect(renderer,&textureBarLeft);

		SDL_SetRenderDrawColor(renderer, 128, 0, 128, 255);
		SDL_RenderFillRect(renderer,&textureBarRight);

		SDL_SetRenderDrawColor(renderer, 128, 128, 0, 255);
		SDL_RenderFillRect(renderer,&textureBarBottom);


		SDL_RenderPresent(renderer); //updates the renderer


		tetherFreeData(tether);




		//i++;
		SDL_UpdateWindowSurface( mainWindow );
	}while(!quit);


	SDL_UpdateWindowSurface( mainWindow );
	printf("after loop\n");

	SDL_Delay(500);
	SDL_DestroyWindow( mainWindow );
	SDL_Quit();

	return 0;
}
