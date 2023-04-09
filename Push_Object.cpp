#include "Push_Object.h"
#include "Global.h"
#include "Tile.h"
#include "Util.h"
#include "Constant.h"
#include "LTexture.h"

PushObject::PushObject( int pos )
{
    mPos = pos ;
    mVel = 0;

    mBox = { 0, 0, WIDTH, HEIGHT };

    ObjectStatus = GOAL_NOT;
}

bool PushObject::move( Tile * tiles[], status Move )
{   
    switch (Move) 
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
        mVel = 0;
        break;
    }
    //Object 
    mPos += mVel;
    if( touchesWall(tiles[mPos]->getBox(), tiles ))
    {
        mPos -= mVel;
        mVel = 0;
        return false;
    }
    mBox = tiles[mPos]->getBox();
    mVel = 0;
    if ((tiles[mPos]->getType() == TILE_GOAL) )
    {
        ObjectStatus = GOAL;
    }
    else
    {
        ObjectStatus = GOAL_NOT;
    }

    return true;
}

int PushObject::getObjectStatus()
{
    return ObjectStatus;
}

SDL_Rect PushObject::getBox()
{
    return mBox;
}

void PushObject::render()
{
        gPushObject.render( mBox.x, mBox.y, &gObjectClips[ ObjectStatus ] );
}
