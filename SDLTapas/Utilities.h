/*
 *
 * Utilities.h
 * Various assorted helper functions and definitions, including math and matrices
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

#include <SDL/SDL.h>
#include <math.h>



//-----------------------------------------------------------------------------------------------------------
// Forward declarations
//-----------------------------------------------------------------------------------------------------------
namespace Utilities {

	// Constants
	const double pi = M_PI;

	// TODO: Optimise conversions or only use doubles (truncating as the final step) (?)
	template<class Num> Num rad(Num deg) { return static_cast<Num>(deg*pi/180.0); } // Degrees to radians
	template<class Num> Num deg(Num rad) { return static_cast<Num>(deg*180.0/pi); } // Radians to degrees

	template<class Num> Num   sine(Num deg) { return static_cast<Num>(sin(rad(deg))); }
	template<class Num> Num cosine(Num deg) { return static_cast<Num>(cos(rad(deg))); }

	//
	int cycle(int*, int, int, int); // Cycles a value in the given range (modular arithmetic increment)

}
