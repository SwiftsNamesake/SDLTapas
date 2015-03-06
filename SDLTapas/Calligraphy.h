/*
 *
 * Calligraphy.h
 * SDL text handling
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
#include <SDL/SDL_ttf.h>

#include "Calligraphy.h"
#include "Textures.h"



//-----------------------------------------------------------------------------------------------------------
// Forward declarations
//-----------------------------------------------------------------------------------------------------------
namespace Calligraphy {

	//
	TTF_Font* loadFont(const char* fontname, int size, int outline, int styles, int hinting, int kerning) {

		//
		TTF_Font* font = TTF_OpenFont(fontname, size);

		if (font == NULL) {
			OutputDebugStringA("Couldn't initialise font (%s).\n");//, fontname);
			return NULL;
		}

		return font;

		// Addional font attributes
		TTF_SetFontOutline(font, outline);
		TTF_SetFontHinting(font, hinting);
		TTF_SetFontStyle(font, styles);
		TTF_SetFontKerning(font, kerning);
		//TTF_GlyphIsProvided();

		return font;

	}

	int renderText(TTF_Font* font, SDL_Color fill, const char* text) {

		// Generates a texture with the desired text
		SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text, fill);

		if (surface == NULL) {
			//SDL_Log("Unable to render text.\n");
			OutputDebugStringA("Unable to render text.\n");
			return (-1);
		}

		//SDL_Surface* corrected = (Textures::pixelFormat(surface->format) == -1) ? Textures::normalise(surface) : surface; //
		SDL_Surface* corrected = Textures::normalise(surface);
		IMG_SavePNG(corrected, "text.png");
		int index = Textures::loadTexture(corrected, GL_LINEAR, GL_LINEAR);
		
		return index;

	}

}