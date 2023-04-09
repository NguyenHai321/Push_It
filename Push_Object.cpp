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

    ObjectFacing = new facing[4];
    ObjectFacing[0] = notFacing;
    ObjectFacing[1] = notFacing;
    ObjectFacing[2] = notFacing;
    ObjectFacing[3] = notFacing;
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

    if( touchesWall(tiles[mPos]->getBox(), tiles ) )
    {
        mPos -= mVel;
        mVel = 0;
        return false;
    }
    mBox = tiles[mPos]->getBox();
    mVel = 0;

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

int PushObject::getFacing(int i)
{
    return ObjectFacing[i];
}

void PushObject::gettingFacingVal(Tile* tiles[])
{
    if (touchesWall(tiles[mPos - EDGE_TILES]->getBox(), tiles)) ObjectFacing[0] = frontFacing;
    else ObjectFacing[0] = notFacing;

    if (touchesWall(tiles[mPos + EDGE_TILES]->getBox(), tiles)) ObjectFacing[1] = backFacing;
    else ObjectFacing[1] = notFacing;

    if (touchesWall(tiles[mPos - 1]->getBox(), tiles)) ObjectFacing[2] = leftFacing;
    else ObjectFacing[2] = notFacing;

    if (touchesWall(tiles[mPos + 1]->getBox(), tiles)) ObjectFacing[3] = rightFacing;
    else ObjectFacing[3] = notFacing;
}

SDL_Rect PushObject::getBox()
{
    return mBox;
}

void PushObject::render( SDL_Rect& camera )
{
        gPushObject.render( mBox.x, mBox.y, &gObjectClips[ ObjectStatus ] );
}
