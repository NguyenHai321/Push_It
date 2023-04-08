#ifndef PUSH_OBJECT_H_INCLUDED
#define PUSH_OBJECT_H_INCLUDED

#include "Tile.h"
#include "Constant.h"
#include "MainChar.h"


class PushObject
{
public:
    static const int WIDTH = 48;
    static const int HEIGHT = 48;

    PushObject();

    bool move ( Tile* tile[], mainChar* mainChar );

    void render( SDL_Rect& camera );

    void ReachGoal( Tile *tile[] );
private:
    SDL_Rect mBox;

    int mVel, mPos;

    status ObjectStatus;
};

#endif // PUSH_OBJECT_H_INCLUDED
