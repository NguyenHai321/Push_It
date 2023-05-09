#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include "Tile.h"
#include "LTexture.h"
#include "Global.h"
#include "Constant.h"
#include "Push_Object.h"
#include "MainChar.h"

bool init();

bool loadMedia();

void close( Tile* tiles[], PushObject* push[], int index);

bool checkCollision( SDL_Rect a, SDL_Rect b );

bool touchesWall( SDL_Rect box, Tile* tiles[] );

bool WinGame(int goalNum, PushObject* box[]);

bool setObject(PushObject* push[], const char* map_data);

#endif // UTIL_H_INCLUDED
