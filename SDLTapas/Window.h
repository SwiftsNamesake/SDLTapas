/*
 *
 * Window.h
 * Simulates the motion of a camera by moving the world around it. Isn't that the height of arrogance.
 *
 * Jonatan H Sundqvist
 * February 27 2015
 *
 */

/* TODO | -
 *        -
 *
 * SPEC | -
 *        -
 */



//-----------------------------------------------------------------------------------------------------------
// We'll need these
//-----------------------------------------------------------------------------------------------------------
#pragma once

#include <SDL/SDL.h>



//-----------------------------------------------------------------------------------------------------------
// Forward declarations
//-----------------------------------------------------------------------------------------------------------
namespace Window {

	//
	int InitSubsystems();                    // Initialises SDL, TTF and IMG
	void loadIcon(SDL_Window*, const char*); //

}