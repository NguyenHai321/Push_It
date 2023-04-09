#ifndef MAINCHAR_H_INCLUDED
#define MAINCHAR_H_INCLUDED

#include "LTexture.h"
#include "Tile.h"
#include "Push_Object.h"

class mainChar
{
public:
    static const int WIDTH = 48;
    static const int HEIGHT = 48;

    static const int VEL = 1;

    mainChar();

    SDL_Rect getBox();

    void handleEvent( SDL_Event& e );

    void move(Tile* tiles[], PushObject* push);

    void render(SDL_Rect& camera);

    status getStatus();

private:
    SDL_Rect mBox;

    int mVel;

    status CharStatus;

    int mPos;
};

#endif // MAINCHAR_H_INCLUDED
