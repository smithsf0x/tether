#include "tether.h"



TETHER* iniTether(SDL_Window* window){
  TETHER* newTether = malloc(sizeof(newTether));
  if(newTether == NULL){ return NULL; }
  newTether->camera = malloc(sizeof(newTether->camera));
  if(newTether->camera == NULL){ return NULL; }
  newTether->camera->camera = malloc(sizeof(newTether->camera->camera ));
  if(newTether->camera->camera == NULL){ return NULL; }
  //newTether->viewSurface = SDL_GetWindowSurface( window );
  //if(newTether->viewSurface == NULL){ return NULL; }

  return newTether;
}

int tetherSetupCamera(TETHER* tether){
	int	retval;
	tether->camera->context = malloc(sizeof(tether->camera->context));
    tether->camera->context = gp_context_new();

	gp_camera_new(&tether->camera->camera);

    printf("Init camera\n");
	retval = gp_camera_init(tether->camera->camera, tether->camera->context);
    printf("finished\n");
	if (retval != GP_OK) {
		printf("  Retval: %d\n", retval);
		return -1;
	}

    retval = camera_eosviewfinder(tether->camera->camera, tether->camera->context,1);
	if (retval != GP_OK) {
		fprintf(stderr,"camera_eosviewfinder(1): %d\n", retval);
		return -2;
	}

  return 0;
}

int tetherFetchData(TETHER* tether){

  static int i = 0;
  int retval = 0;

  retval = gp_file_new(&tether->file);
  if (retval != GP_OK) {
    fprintf(stderr,"gp_file_new: %d\n", retval);
    return 1;
  }

  /* autofocus every 10 shots */
  /*
  if (i%10 == 9) {
    camera_auto_focus (tether->camera->camera, tether->camera->context, 1);
    // FIXME: wait a bit and/or poll events ?
    camera_auto_focus (tether->camera->camera, tether->camera->context, 0);
  } else {
    camera_manual_focus (tether->camera->camera,0, tether->camera->context);
  }
  */

  camera_manual_focus (tether->camera->camera,0, tether->camera->context);

  retval = gp_camera_capture_preview(tether->camera->camera, tether->file, tether->camera->context);

  if (retval != GP_OK) {
    fprintf(stderr,"gp_camera_capture_preview(%d): %d\n", i, retval);
    return 2;
  }

  i = i + 1;

  return 0;
}

int tetherProcessData(TETHER* tether){
  SDL_Surface *image;
  SDL_Texture* texture;
  char *data;
  unsigned long int size;
  gp_file_get_data_and_size (tether->file, (const char **) &data, &size);
  image=IMG_Load_RW(SDL_RWFromMem(data, size), 1);
  if(!image) {
      printf("IMG_Load_RW: %s\n", IMG_GetError());
      return -1;
  }

  texture = SDL_CreateTextureFromSurface(tether->renderer, image);
  tether->viewTexture = texture;
  tether->viewSurface = image;

  gp_file_unref(tether->file);

  return 0;
}

int tetherFreeData(TETHER* tether){
  //printf("Freeing viewTexture..." );
  //SDL_DestroyTexture(tether->viewTexture);
  //printf("OK\n");
  //printf("Freeing viewSurface..." );
  //SDL_FreeSurface(tether->viewSurface);
  //printf("OK\n");
  //printf("Freeing file..." );
  //gp_file_free(tether->file);
  //printf("OK\n");
  return 0;
}
