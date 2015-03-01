/*
 *
 * Audio.h
 * 
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



//-------------------------------------------------------------------------------------------------
// We'll need these
//-------------------------------------------------------------------------------------------------
# pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <map>

// My headers
#include "Utilities.h"
//#include "Globals.h"



//-------------------------------------------------------------------------------------------------
// Forward declarations
//-------------------------------------------------------------------------------------------------
namespace Audio {

	//
	typedef std::map<int, Mix_Music*> AudioMap;

	//
	int count = 0;                       // TODO: Better way to produce tokens (?)
	static AudioMap sounds = AudioMap(); // 

	// Functions
	int InitMixer();  // 
	int CloseMixer(); // 
	
	int loadSoundFile(const char* filename); // 
	int play(int token);                     // 

}

