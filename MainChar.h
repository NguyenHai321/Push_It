#ifndef MAINCHAR_H_INCLUDED
#define MAINCHAR_H_INCLUDED

#include "LTexture.h"
#include "Tile.h"
#include "Push_Object.h"

class mainChar
{
public:
    static const int WIDTH = 40;
    static const int HEIGHT = 40;

    static const int VEL = 1;

    mainChar();
    mainChar(int pos);

    SDL_Rect getBox();

    void handleEvent( SDL_Event& e );

    void move(Tile* tiles[], PushObject* push[], int num);

    void render();

    void updatePos(int pos);

    status getStatus();

    void resetStatus();

private:
    SDL_Rect mBox;

    int mVel;

    status CharStatus;

    int mPos;
};

#endif // MAINCHAR_H_INCLUDED
