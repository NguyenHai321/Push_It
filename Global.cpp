#include "Global.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font* gFont = NULL;
TTF_Font* WinFont = NULL;

Mix_Music* gMusic = NULL;
Mix_Chunk* MoveSound = NULL;
Mix_Chunk* CompleteSound = NULL;
Mix_Chunk* Clicking = NULL;

LTexture gMainChar;
LTexture gTileTexture;
LTexture gPushObject;
LTexture gBackground;
LTexture gTextTexture[3];
LTexture gWinText[3];
LTexture gRetry[2];
LTexture gLevelText;

SDL_Rect gObjectClips[ 2 ];
SDL_Rect gTileClips[ TOTAL_TILE_SPRITES ] ;
