/*
 * Textures.cpp
 *
 * See header for more information
 *
 */



//-----------------------------------------------------------------------------------------------------------
// We'll need these
//-----------------------------------------------------------------------------------------------------------
#include "Textures.h"



//-----------------------------------------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------------------------------------
SDL_Surface* Textures::normalise(SDL_Surface* surface) {

		// Normalises a surface by converting it to an OpenGL-compatible format
		// TODO: Lock surface, free one of them (?)
		// TODO: Cache pixel format (?)

		GLenum format = Textures::pixelFormat(surface->format); //

		/*if (format != (-1)) {
			//
			// TODO: Unwise to return the same surface (?)
			SDL_Log("The surface is already in a valid format");
			return surface;
		}*/

		SDL_PixelFormat pxFormat;
		pxFormat.format = SDL_PIXELFORMAT_RGBA8888;
		pxFormat.BitsPerPixel = 32;
		pxFormat.BytesPerPixel = 4;
		pxFormat.Rmask = 0x000000ff;
		pxFormat.Gmask = 0x0000ff00;
		pxFormat.Bmask = 0x00ff0000;
		pxFormat.Amask = 0xff000000;
		pxFormat.palette = NULL;

		SDL_Surface* corrected = SDL_ConvertSurface(surface, &pxFormat, NULL);

		if (corrected == NULL) {
			//SDL_Log("%s\n", SDL_GetError());
			OutputDebugStringA("Failed to normalise surface.\n");
			return NULL;
		} else {
			return corrected;
		}

	}


int Textures::queueTexture(const char* filename, GLint minfiltering, GLint maxfiltering) {

		//

		// TODO: Coupling between this function and loadTexture
		// TODO: Handle errors (indirectly, since we can't detect errors until we invoke Texture::loadTexture)
		// TODO: Rename (?)

		// This function is necessary if we want to declare a namespace of texture indeces and initialize it statically. The alternative (which I resorted to originally)
		// is to create a separate function or constructor (incuring a lot of duplication) which initializes each member once OpenGL is ready for business.

		// TODO: Vector of structs? Move semantics? Is this the best way to do it?
		SDL_Log("Queueing texture: %s\n", filename);

		Textures::queuedTextures.push_back({
			filename,
			minfiltering,
			maxfiltering
		});

		return Textures::count++;

	}


int Textures::loadQueuedTextures() {

		//
		// TODO: Flag indicating whether queued textures have been processed (?)
		// TODO: Deal with overloads of Texture::loadTexture (?)
		for (Textures::TextureArgs& args : Textures::queuedTextures) {
			Textures::loadTexture(args.filename, args.minfiltering, args.maxfiltering);
		}

		return 0;

	}


int Textures::deleteQueuedTextures() {

	//
	glDeleteTextures(Textures::count, Textures::textureIDs);
	return 0;

}


int Textures::loadTexture(const char* filename, GLint minfiltering, GLint maxfiltering) {

		//
		//
		SDL_Log("Loading texture: %s", filename);
		SDL_Surface* data = IMG_Load(filename);

		if (data == NULL) {
			SDL_Log("Failed to load image %s: ", filename, SDL_GetError());
			SDL_FreeSurface(data);
			return (-1);
		}

		return Textures::loadTexture(data, minfiltering, maxfiltering);

	}


int Textures::loadTexture(SDL_Surface* data, GLint minfiltering, GLint maxfiltering) {

	//
	// Returns index for the created index (or a negative number for errors)
	// TODO: Detect if OpenGL hasn't been initialised yet.
	// TODO: Retrieve format data directly from the SDL surface

	OutputDebugStringA("Loading texture\n");

	SDL_Log("Texture error before: %d\n", glGetError());

	if (data == NULL) {
		OutputDebugStringA("Data is null. Bailing out.\n");
		return (-1);
	}

	// TODO: Should I really be generating the texture IDs in this function?
	if (Textures::count == 0) {
		//OutputDebugStringA("Generating textures.\n");
		//glGenTextures(Textures::texCount, Textures::textureIDs);
		//SDL_Log("glGenTextures error: %d\n", glGetError());
	} else if (Textures::count >= Textures::texCount) {
		OutputDebugStringA("No more textures can be created.\n");
		return (-1);
	}

	OutputDebugStringA("Loading texture number %d.\n"); //, Textures::count);

	data->refcount += 1;
	SDL_LockSurface(data);

	/*
	//
	// Refine the formatting check below and use it for all textures
	GLenum gpuFormat = Textures::pixelFormat(data->format); //
	GLenum type      = GL_UNSIGNED_BYTE;                    //

	if (gpuFormat == (-1)) {
		OutputDebugStringA("Invalid texture format.\n");
		//SDL_Log();
		return (-1);
	}*/

	GLuint gpuFormat; //
	//GLuint srcFormat; //
	GLenum type = GL_UNSIGNED_BYTE;
	Uint8 colours = data->format->BytesPerPixel;


	if (colours == 4) {     // contains an alpha channel

		if (data->format->Rmask == 0x000000ff) {
			//OutputDebugStringA("Rmask=0x%08x, Gmask=0x%08x, Bmask=0x%08x, Amask=0x%08x", data->format->Rmask, data->format->Gmask, data->format->Bmask, data->format->Amask);
			gpuFormat = GL_RGBA;
		} else {
			gpuFormat = GL_BGRA;
		}
	} else if (colours == 3) {    // no alpha channel

		if (data->format->Rmask == 0x000000ff)
			gpuFormat = GL_RGB;
		else
			gpuFormat = GL_BGR;
	} else {
		//OutputDebugStringA("warning: the image is not truecolor..  this will probably break\n");
		// this error should not go unhandled
	}
	
	//SDL_Log("%d\n\n", data->format->BitsPerPixel);
	//SDL_Log("%d|%d\n", data->w, data->h);
	//glEnable(GL_TEXTURE_2D);

	SDL_Log("Loading texture #%d.\n", Textures::count + 1);
	SDL_Log("Texture error before: %d\n", glGetError());
	
	glGenTextures(1, &Textures::textureIDs[count]);
	SDL_Log("Gen one texture error : %d\n", glGetError());
	glBindTexture(GL_TEXTURE_2D, Textures::textureIDs[Textures::count]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, data->w, data->h, 0, gpuFormat, type, data->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minfiltering);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, maxfiltering);
	SDL_Log("Texture error after: %d\n", glGetError());
	
	//
	SDL_UnlockSurface(data);
	SDL_FreeSurface(data);

	Textures::count++;

	return Textures::count - 1;
	//return 0;

}


int Textures::deleteTextures() {

	//
	glDeleteTextures(texCount, textureIDs);
	return 0;

}


GLenum Textures::pixelFormat(SDL_PixelFormat* format) {

	// 
	// TODO: Make sure this is correct
	// TODO: Rename (?)

	if (format->BytesPerPixel == 4) {
		
		// Alpha channel included

		if (format->Rmask == 0x000000ff) {
			SDL_Log("Rmask is 0x000000ff\n");
			//SDL_Log("Rmask=0x%08x, Gmask=0x%08x, Bmask=0x%08x, Amask=0x%08x\n", data->format->Rmask, data->format->Gmask, data->format->Bmask, data->format->Amask);
			return GL_RGBA;
		} else {
			return GL_BGRA;
		}

	} else if (format->BytesPerPixel == 3) {
		
		// Alpha channel not included
		
		if (format->Rmask == 0x000000ff) {
			return GL_RGB;
		}  else {
			return GL_BGR;
		}

	} else {
		SDL_Log("Invalid pixel format.\n");
		return (-1); // 
	}

}