#include "Push_Object.h"
#include "Global.h"
#include "Tile.h"
#include "Util.h"
#include "Constant.h"
#include "LTexture.h"

PushObject::PushObject()
{
    mPos = 54;
    mVel = 0;

    ObjectStatus = GOAL_NOT;
}

bool PushObject::move( Tile* tiles[], mainChar* mainChar )
{
    if (checkCollision(mainChar->getBox(), mBox))
    {
        switch (mainChar->getStatus() )
        {
        case UP:
            mVel -= EDGE_TILES;
            break;
        case DOWN:
            mVel += EDGE_TILES;
            break;
        case LEFT:
            mVel -= 1;
            break;
        case RIGHT:
            mVel += 1;
            break;
        default:
            break;
        }
    }

    mPos += mVel;

    if( touchesWall(tiles[mPos]->getBox(), tiles) ||
        mPos < EDGE_TILES ||
        mPos % EDGE_TILES == 0 ||
        mPos % EDGE_TILES == EDGE_TILES - 1 ||
        mPos > EDGE_TILES * EDGE_TILES - EDGE_TILES - 1)
    {
        mPos -= mVel;
           return false;
    }
    mBox = tiles[mPos]->getBox();

    return true;
}

void PushObject::ReachGoal( Tile *tile[] )
{
    for( int i = 0; i < TOTAL_TILES; ++i )
    {
        if( ( tile[ i ]->getType() == TILE_GOAL ) && ( getToGoal( mBox, tile[ i ]->getBox() ) ) )
        {
            ObjectStatus = GOAL;
        }
        else
        {
            ObjectStatus = GOAL_NOT;
        }
    }
}

void PushObject::render( SDL_Rect& camera )
{
        gPushObject.render( mBox.x, mBox.y, &gObjectClips[ ObjectStatus ] );
}
