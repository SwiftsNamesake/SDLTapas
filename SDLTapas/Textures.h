/*
 *
 * Textures.h
 * Loading, validating, accessing, uploading, and related present-participling of textures
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
#include <SDL/SDL_image.h>
#include <vector>

#include "Utilities.h"



//-----------------------------------------------------------------------------------------------------------
// Forward declarations
//-----------------------------------------------------------------------------------------------------------
namespace Textures {

	// Classes
	struct TextureArgs {
		const char* filename;
		GLint minfiltering;
		GLint maxfiltering;
	};

	// Variables
	// TODO: Rename texCount (?)
	static const int texCount = 32;		// Maximum number of textures
	static GLuint textureIDs[texCount];	// Stores texture IDs

	//int texIndex = 0; // 
	//int texNum   = 2; // What's this for? (cf. event loop; I think I'm using it for 'flicking' through textures)

	static int count = 0; // Number of currently loaded textures

	static std::vector<Textures::TextureArgs> queuedTextures; // Contains the arguments

	// Functions
	SDL_Surface* normalise(SDL_Surface* surface);

	GLenum pixelFormat(SDL_PixelFormat* format);

	int queueTexture(const char* filename, GLint minfiltering, GLint maxfiltering);

	int loadQueuedTextures();

	int deleteQueuedTextures();

	int loadTexture(const char* filename, GLint minfiltering, GLint maxfiltering);

	int loadTexture(SDL_Surface* data, GLint minfiltering, GLint maxfiltering);

	int deleteTextures();

}