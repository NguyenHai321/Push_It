#include "MainChar.h"
#include "LTexture.h"
#include "Util.h"
#include "Constant.h"
#include "Global.h"

mainChar::mainChar()
{
    mPos = 41;
    mVel = 0;

    mBox.w = WIDTH;
    mBox.h = HEIGHT;

    CharStatus = GOAL_NOT;
}

// sua lai movement
void mainChar::handleEvent( SDL_Event& e )
{
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_UP:
                mVel -= EDGE_TILES;
                CharStatus = UP;
                break;
            case SDLK_DOWN:
                mVel += EDGE_TILES;
                CharStatus = DOWN;
                break;
            case SDLK_LEFT:
                mVel -= 1;
                CharStatus = LEFT;
                break;
            case SDLK_RIGHT:
                mVel += 1;
                CharStatus = RIGHT;
                break;
        }
    }
}

void mainChar::move( Tile* tiles[] )
{
    mPos += mVel;
    if ( touchesWall( tiles[ mPos ]->getBox(), tiles ) ||
         mPos < EDGE_TILES                             ||
         mPos % EDGE_TILES == 0                        ||
         mPos % EDGE_TILES  == EDGE_TILES - 1          ||
         mPos > EDGE_TILES * EDGE_TILES - EDGE_TILES - 1 )
    {
        //Move back
        mPos -= mVel;
    }
    mBox = tiles[ mPos ]->getBox();
    mVel = 0;
}

void mainChar::render( SDL_Rect& camera )
{
    gMainChar.render( mBox.x + 4, mBox.y + 4 , NULL, 90*CharStatus );
}

SDL_Rect mainChar::getBox()
{
    return mBox;
}

status mainChar::getStatus()
{
    return CharStatus;
}