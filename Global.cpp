#include "Global.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

LTexture gMainChar;
LTexture gTileTexture;
LTexture gPushObject;
SDL_Rect gObjectClips[ 2 ];
SDL_Rect gTileClips[ TOTAL_TILE_SPRITES ] ;
