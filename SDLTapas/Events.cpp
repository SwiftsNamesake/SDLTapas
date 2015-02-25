/*
 * Events.cpp
 *
 * See header for more information
 *
 */



#include "Events.h"



//-----------------------------------------------------------------------------------------------------------
// Event framework
//-----------------------------------------------------------------------------------------------------------
int Events::addListener(SDL_EventType type, Events::Listener listener) {

	//
	auto iter = Events::listeners.find(type);

	if (iter == Events::listeners.end()) {
		// Create vector of listeners for the event type if necessary
		Events::listeners[type] = std::vector<Events::Listener>();
	}

	// Add the new listener to the vector
	Events::listeners.find(type)->second.push_back(listener);

	return 0;

}


int Events::invokeListeners(SDL_EventType type, SDL_Event& ev) {

	//
	// Ugh. There really ought to be a better way of doing map lookups
	auto iter = Events::listeners.find(type);

	if (iter != Events::listeners.end()) {
		for (Events::Listener callback : iter->second) {
			callback(ev);
		}
	}

	return 0;

}


int Events::mainloop() {

	//
	//
	SDL_Event ev;

	SDL_Log("Entering main loop...\n");

	while (Events::running) {
		while (SDL_PollEvent(&ev) > 0) {
			Events::invokeListeners((SDL_EventType)ev.type, ev);
			SDL_Log("Polling event...\n");
		}

		//Animation::tick();
		Events::tick(ev);

	}

	// TODO: Use atexit (?)
	//SDL_Quit();
	//TTF_Quit();
	//IMG_Quit();

	return 0;

}
