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

void Tile::render( SDL_Rect& camera )
{
    if( checkCollision( camera, mBox ) )
    {
        gTileTexture.render( mBox.x - camera.x, mBox.y - camera.y, &gTileClips[ mType ] );
    }
}

SDL_Rect Tile::getBox()
{
    return mBox;
}

int Tile::getType()
{
    return mType;
}