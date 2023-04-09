#include "Tile.h"
#include "Util.h"

Tile::Tile( int x, int y, int tileType )
{
    mBox.x = x;
    mBox.y = y;

    mBox.w = TILE_WIDTH;
    mBox.h = TILE_HEIGHT;

    mType = tileType;
}

void Tile::render()
{
    gTileTexture.render( mBox.x, mBox.y, &gTileClips[ mType ] );
}

SDL_Rect Tile::getBox()
{
    return mBox;
}

int Tile::getType()
{
    return mType;
}

void Tile::setOccupied()
{
    occupiedTile = yes;
}

void Tile::deOccupied()
{
    occupiedTile = no;
}

int Tile::getStat()
{
    return occupiedTile;
}