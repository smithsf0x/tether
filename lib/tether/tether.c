#include "tether.h"

TETHER* iniTether(SDL_Window* window){
  TETHER* newTether = malloc(sizeof(newTether));

  newTether->viewSurface = SDL_GetWindowSurface( window );

  return newTether;
}

int tetherSetupCamera(TETHER* tether){
	int	retval;
	tether->camera->context = sample_create_context();

	gp_camera_new(&tether->camera->camera);

  printf("Init camera\n");
	retval = gp_camera_init(tether->camera->camera, tether->camera->context);
	if (retval != GP_OK) {
		printf("  Retval: %d\n", retval);
		exit (1);
	}

  // canon_enable_capture only for cannon
  // canon_enable_capture(canon, TRUE, canoncontext);

  retval = camera_eosviewfinder(tether->camera->camera, tether->camera->context,1);
	if (retval != GP_OK) {
		fprintf(stderr,"camera_eosviewfinder(1): %d\n", retval);
		return 1;
	}

  return 0;
}

int tetherFetchData(TETHER* tether){

  static int i = 0;
  int retval = 0;

  fprintf(stderr,"preview %d\n", i);
  retval = gp_file_new(&tether->file);
  if (retval != GP_OK) {
    fprintf(stderr,"gp_file_new: %d\n", retval);
    return 1;
  }

  /* autofocus every 10 shots */
  if (i%10 == 9) {
    camera_auto_focus (tether->camera->camera, tether->camera->context, 1);
    /* FIXME: wait a bit and/or poll events ? */
    camera_auto_focus (tether->camera->camera, tether->camera->context, 0);
  } else {
    camera_manual_focus (tether->camera->camera, (i/10-5)/2, tether->camera->context);
  }

  retval = gp_camera_capture_preview(tether->camera->camera, tether->file, tether->camera->context);

  if (retval != GP_OK) {
    fprintf(stderr,"gp_camera_capture_preview(%d): %d\n", i, retval);
    return 2;
  }

  i = i + 1;

  return 0;
}
int tetherProcessData(TETHER* tether){

  gp_file_unref(tether->file);
  return 0;
}

int tetherFreeData(TETHER* tether){
  free(tether->data);
  return 0;
}
