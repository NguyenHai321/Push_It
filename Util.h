#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include "Tile.h"
#include "LTexture.h"
#include "Global.h"
#include "Constant.h"
#include "Push_Object.h"
#include "MainChar.h"

bool init();

bool loadMedia( Tile* tiles[], const char* map_path );

void close( Tile* tiles[] );

bool checkCollision( SDL_Rect a, SDL_Rect b );

bool setTiles( Tile* tiles[], const char* map_path );

bool touchesWall( SDL_Rect box, Tile* tiles[] );

void setObject();

bool getToGoal( SDL_Rect a, SDL_Rect b );

#endif // UTIL_H_INCLUDED
