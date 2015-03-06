/*
 *
 * Meshes.h
 * Or blobs of vertex data, if you prefer
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

#include <SDL/SDL_opengl.h>
#include <functional>


//-----------------------------------------------------------------------------------------------------------
// Forward declarations
//-----------------------------------------------------------------------------------------------------------
namespace Draw {
	
	// Classes
	struct Model {
		// Represents a drawable object
		// Just a silly little experiment, should be replaced with something serious
		GLenum primitive;
		float a, b, c;
		std::function<void(const Model&)> draw;
	};

	// Functions
	void cube(GLenum, float, float, float);
	void sphere(GLenum, float);
	void cylinder(GLenum, float, float);
	void cone(GLenum, float, float);
	void pyramid(GLenum, float, float, float);
	// spiral, dna, torus
	void spiral(GLenum, float, float, float);

	void grid(float);

	//void extrude(GLenum, float);

}