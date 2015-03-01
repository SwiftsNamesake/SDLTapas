/*
 * Window.cpp
 *
 * See header for more information
 *
 */



//-----------------------------------------------------------------------------------------------------------
// We'll need these
//-----------------------------------------------------------------------------------------------------------
#include "Window.h"

#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>



//-----------------------------------------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------------------------------------
int Window::InitSubsystems() {

	// Initialise SDL and its subsystems (SDL_TTF for fonts and text, SDL_IMG for loading images)
	int errSDL, errTTF, errIMG;

	if (((errSDL = SDL_Init(SDL_INIT_EVERYTHING)) == -1) ||  // Negative one indicates failure
		((errTTF = TTF_Init())                    == -1) ||  // Negative one indicates failure
		((errIMG = IMG_Init(IMG_INIT_PNG))        ==  0)) {  // Zero indicates failure
		// Atleast one of the systems failed to initialise.
		// TODO: More elaborate logging.
		// TODO: Significant return values (eg. a mask of success flags).
		SDL_Log("Failed to initialise subsystems.\n");
		SDL_Log("SDL: %d\nTTF: %d\nIMG: %d\n", errSDL, errTTF, errIMG);
		return 0;
	} else {
		SDL_Log("Successfully initialised subsystems.\n");
		return 1;
	}

}


void Window::loadIcon(SDL_Window* window, const char* filename) {

	//
	// TODO: Error handling (?)
	SDL_Surface* icon = IMG_Load(filename);
	SDL_SetWindowIcon(window, icon);
	SDL_FreeSurface(icon);

}