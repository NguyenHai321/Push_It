#include "MainChar.h"
#include "LTexture.h"
#include "Util.h"
#include "Constant.h"
#include "Global.h"
#include "Push_Object.h"

mainChar::mainChar()
{
    mPos = 0;
    mVel = 0;

    mBox.w = WIDTH;
    mBox.h = HEIGHT;

    CharStatus = UP;
}

mainChar::mainChar(int pos)
{
    mPos = pos;
    mVel = 0;

    mBox.w = WIDTH;
    mBox.h = HEIGHT;

    CharStatus = UP;
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

void mainChar::move( Tile* tiles[] , PushObject* push[], int num)
{
    mPos += mVel;
    for (int i = 0; i < num; ++i)
    {
        if (checkCollision(tiles[mPos]->getBox(), push[i]->getBox()))
        {
            if (!push[i]->move(tiles, CharStatus))
            {
                mPos -= mVel;
                mVel = 0;
                return;
            }
        }
        else
        {
            push[i]->move(tiles, NONE);
        }
        if (touchesWall(tiles[mPos]->getBox(), tiles))
        {
            mPos -= mVel;
            mVel = 0;
            return;
        }
    }
    mBox = tiles[ mPos ]->getBox();
    mVel = 0;
    return ;
}

void mainChar::render()
{
    gMainChar.render( mBox.x + 4, mBox.y + 4 , NULL, 90*CharStatus );
}

SDL_Rect mainChar::getBox()
{
    return mBox;
}

void mainChar::updatePos(int pos)
{
    mPos = pos;
}

status mainChar::getStatus()
{
    return CharStatus;
}

void mainChar::resetStatus()
{
    CharStatus = UP;
}
