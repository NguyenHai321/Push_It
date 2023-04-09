#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

#include "LTexture.h"

class Tile
{
public:
    Tile (int x, int y, int tileType );

    void render ();

    int getType();

    void setOccupied();
    void deOccupied();

    int getStat();

    SDL_Rect getBox();

private:
    SDL_Rect mBox;

    int mType;

    Occupied occupiedTile;
};

#endif // TILE_H_INCLUDED
