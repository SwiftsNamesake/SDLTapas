/*
 *
 * Camera.h
 * Simulates the motion of a camera by moving the world around it. Isn't that the height of arrogance.
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



//-----------------------------------------------------------------------------------------------------------
// Forward declarations
//-----------------------------------------------------------------------------------------------------------
namespace Camera {

	//
	// Bad idea to use the same name (?)
	struct Camera {
		// TODO: Rename fields, use vectors (?)
		float rX = 0.0f, rY = 0.0f, rZ = 0.0f; // Rotation
		float X = 0.0f, Y = 0.0f, Z = 0.0f;    // Translation
	};

	//
	enum View {
		FRONT, BACK, DOWN, UP, LEFT, RIGHT
	};

	//
	void aim(const Camera&); //
	void look(Camera&, View, float);  //

}