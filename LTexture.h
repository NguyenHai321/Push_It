#ifndef LTEXTURE_H_INCLUDED
#define LTEXTURE_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include "SDL_ttf.h"
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <SDL_mixer.h>
#include "Constant.h"


class LTexture
{
public:
    LTexture();

    ~LTexture();

    bool loadFromFile( std::string path );

    bool loadFromRenderedText( std::string textureText, SDL_Color textColor, TTF_Font* gFont);

    void free();

    void setcolor( Uint8 red, Uint8 green, Uint8 blue );

    void setBlendMode ( SDL_BlendMode blending );

    void setAlpha ( Uint8 alpha );

    void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

    int getWidth();
    int getHeight();

    SDL_Rect getBox();

private:
    SDL_Texture* mTexture;

    SDL_Rect mBox;

    int mWidth;
    int mHeight;
};

#endif // LTEXTURE_H_INCLUDED
