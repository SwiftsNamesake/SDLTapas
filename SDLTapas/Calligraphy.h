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
			SDL_Log("Couldn't initialise font (%s).\n", fontname);
			return NULL;
		}

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
			SDL_Log("Unable to render text.\n");
		}

		//SDL_Surface* corrected = 
		
		int index = Textures::loadTexture(surface, GL_LINEAR, GL_LINEAR);
		
		return index;

	}

}