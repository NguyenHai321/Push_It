#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>

#include "Constant.h"
#include "LTexture.h"


extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

extern LTexture gMainChar;
extern LTexture gTileTexture;
extern LTexture gPushObject;

extern SDL_Rect gObjectClips[ 2 ];
extern SDL_Rect gTileClips[ TOTAL_TILE_SPRITES ] ;

#endif // GLOBAL_H_INCLUDED
