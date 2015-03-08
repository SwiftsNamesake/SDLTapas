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

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <functional>



//-----------------------------------------------------------------------------------------------------------
// Forward declarations
//-----------------------------------------------------------------------------------------------------------
namespace Draw {
	
	// Types
	struct Model {
		// Represents a drawable object
		// Just a silly little experiment, should be replaced with something serious
		GLenum primitive;
		float a, b, c;
		std::function<void(const Model&)> draw;
	};

	struct GLColor { float r, g, b, a; };

	// Functions
	// TODO: Figure out a way to collapse these functions into one (?)
	void plane(GLenum, size_t, size_t, size_t, GLColor, float, float, float, float, float);
	void plane(GLenum, size_t, size_t, size_t, GLuint, float, float, float, float, float);
	
	// Convenience wrappers for the generic plane functions
	void planeXY(GLenum, GLColor, float, float);
	void planeXZ(GLenum, GLColor, float, float);
	void planeYZ(GLenum, GLColor, float, float);

	void planeXY(GLenum, GLuint, float, float);
	void planeXZ(GLenum, GLuint, float, float);
	void planeYZ(GLenum, GLuint, float, float);

	// 3D meshes
	// TODO: Textures
	void cube(GLenum, GLColor, GLColor, GLColor, GLColor, GLColor, GLColor, float, float, float);
	void cube(GLenum, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, float, float, float);

	void sphere(GLenum, float);
	void cylinder(GLenum, GLColor, float, float);
	void cone(GLenum, float, float);
	void pyramid(GLenum, float, float, float);

	//
	// spiral, dna, torus, molecules
	void spiral(GLenum, GLColor, float, float, float, float);

	//
	void grid(float);

	//void extrude(GLenum, float);

	// Colors
	//GLColor toGLColor(SDL_Color color) { return { static_cast<float>(color.r)/255.0f, static_cast<float>(color.g)/255.0f, static_cast<float>(color.b)/255.0f, static_cast<float>(color.a)/255.0f }; }

}