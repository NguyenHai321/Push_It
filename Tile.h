#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

#include "LTexture.h"

class Tile
{
public:
    Tile (int x, int y, int tileType );

    void render ( SDL_Rect& camera );

    int getType();

    SDL_Rect getBox();

private:
    SDL_Rect mBox;

    int mType;
};

#endif // TILE_H_INCLUDED
