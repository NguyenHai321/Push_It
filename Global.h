#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>

#include "Constant.h"
#include "LTexture.h"

extern TTF_Font* gFont;
extern TTF_Font* WinFont;
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

extern Mix_Music* gMusic;
extern Mix_Chunk* MoveSound;
extern Mix_Chunk* CompleteSound;
extern Mix_Chunk* Clicking;

extern LTexture gMainChar;
extern LTexture gTileTexture;
extern LTexture gPushObject;
extern LTexture gBackground;
extern LTexture gTextTexture[3];
extern LTexture gWinText[3];
extern LTexture gRetry[2];
extern LTexture gLevelText;

extern SDL_Rect gObjectClips[ 2 ];
extern SDL_Rect gTileClips[ TOTAL_TILE_SPRITES ] ;

#endif // GLOBAL_H_INCLUDED
