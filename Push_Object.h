#ifndef PUSH_OBJECT_H_INCLUDED
#define PUSH_OBJECT_H_INCLUDED

#include "Tile.h"
#include "Constant.h"


class PushObject
{
public:
    static const int WIDTH = 48;
    static const int HEIGHT = 48;

    PushObject( int pos );

    bool move(Tile* tile[], status Move);

    void render(SDL_Rect& camera);

    void ReachGoal(Tile* tile[]);

    int getFacing(int i);

    void gettingFacingVal(Tile* tile[]);

    SDL_Rect getBox();
private:
    SDL_Rect mBox;

    int mVel, mPos;

    GoalStatus ObjectStatus;

    facing* ObjectFacing;
};

#endif // PUSH_OBJECT_H_INCLUDED