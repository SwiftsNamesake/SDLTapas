/*
 *
 * Events.h
 * Wraps the dreadfully primitive SDL event queue in tender slices of prosciutto
 *
 * Jonatan H Sundqvist
 * February 25 2015
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

#include <functional> // Closures and callbacks
#include <map>        //
#include <vector>     //

#include <SDL/SDL.h>  //



//-----------------------------------------------------------------------------------------------------------
// Forward declarations
//-----------------------------------------------------------------------------------------------------------
namespace Events {

	// TODO: Find out how to use static, extern, etc.
	// Does static storage play well with dynamic linking?
	// TODO: Change default (?)
	static bool running = true; // Not sure where to put this

	typedef std::function<int(SDL_Event)> Listener;
	static std::map<SDL_EventType, std::vector<Listener>> listeners;

	int mainloop(); //
	int quit(int);  //

	int addListener(SDL_EventType, Listener);
	int invokeListeners(SDL_EventType, SDL_Event&);

	int addTick(Listener); // Unique callback

	// TODO: How to handle parameter (use another function type?)
	static Listener tick; // = [](SDL_Event& e) { return 0; }; // Runs one each iteration

}