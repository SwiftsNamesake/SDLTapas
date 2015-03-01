/*
* Events.cpp
*
* See header for more information
*
*/



//-----------------------------------------------------------------------------------------------------------
// We'll need these
//-----------------------------------------------------------------------------------------------------------
#include "Audio.h"



//-----------------------------------------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------------------------------------
int Audio::InitMixer() {

	//
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		SDL_Log("Failed to initialize mixer.\n");
		return 1;
	}

	return 0;

}


int Audio::CloseMixer() {

	//
	Mix_CloseAudio();
	return 0;

}


int Audio::loadSoundFile(const char* filename) {

	//
	Mix_Music* sound = Mix_LoadMUS(filename); // 

	if (sound == NULL) {
		// 
		SDL_Log("I couldn't find the sheets for the piece you requested (file not found).\n");
		return 0;
	} else {
		// 
		Audio::sounds[Audio::count] = sound;
		return Audio::count++;
	}

}


int Audio::play(int token) {

	//
	auto iter = Audio::sounds.find(token);

	if ((iter != Audio::sounds.end()) && (Mix_PlayMusic(iter->second, -1) != -1)) {
		// 
		return 1;
	} else if (iter == Audio::sounds.end()) {
		// 
		SDL_Log("I'm afraid I haven't memorised that one, Sir (invalid token).\n");
		return 0;
	} else {
		// 
		SDL_Log("The conductor has fractured his baton fingers (Mix_PlayMusic failed).\n");
		return 0;
	}

}