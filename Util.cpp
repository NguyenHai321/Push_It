#include "Util.h"
#include "Tile.h"
#include "Constant.h"
#include "Push_Object.h"
#include "Global.h"
#include "LTexture.h"

bool init()
{
    bool success = true;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        std::cout << "failed to initialized: " << SDL_GetError() << std::endl;
    }
    else
    {
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            std::cout << "linear texture has error: " << std::endl;
        }
        gWindow = SDL_CreateWindow ( "Push The Box", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            std::cout << "Window can not be created: " << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            if( gRenderer == NULL )
            {
                std::cout << "Renderer can not be created: " << SDL_GetError() << std::endl;
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0x00 );

                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    std::cout << "SDL_Image could not be initialized: " <<  SDL_GetError() << std::endl;
                    success = false;
                }
                if (TTF_Init() == -1)
                {
                    std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " <<  TTF_GetError() << std::endl;
                    success = false;
                }

                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                {
                    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
                    success = false;
                }
            }
        }
    }
    return success;
}

bool loadMedia()
{
    bool success = true;

    if( !gMainChar.loadFromFile( "Texture/The_thing.png" ) )
    {
        std::cout <<  "failed to load mainChar texture" << std::endl;
        success = false;
    }

    if( !gTileTexture.loadFromFile( "Texture/TileTexture.png" ) )
    {
        std::cout << "failed to load tile texture" << std::endl;
        success = false;
    }

    if( !gPushObject.loadFromFile( "Texture/PushObject.png" ) )
    {
        std::cout << "failed to load object texture" << std::endl;
    }

    if (!gBackground.loadFromFile("Texture/Menu_background.png"))
    {
        std::cout << "failed to load object texture" << std::endl;
    }

    WinFont = TTF_OpenFont("Texture/QuinqueFive.ttf", 32);

    gFont = TTF_OpenFont("Texture/QuinqueFive.ttf", 24);
    if (gFont == NULL)
    {
        std::cout << "Failed to load lazy font!SDL_ttf Error :"  <<  TTF_GetError() << std::endl;
        success = false;
    }
    if (!gRetry[0].loadFromFile("Texture/Retry.png"))
    {
        std::cout << "failed to load retry texture" << std::endl;
    }
    if (!gRetry[1].loadFromFile("Texture/menu.png"))
    {
        std::cout << "failed to load menu texture" << std::endl;
    }
    return success;
}

void close( Tile* tiles[], PushObject* push[], int index)
{
    for( int i = 0; i < TOTAL_TILES; i++ )
    {
        if( tiles[ i ] != NULL )
        {
            delete tiles[ i ];
            tiles[ i ] = NULL;
        }
    }

    for (int i = 0; i < index; ++i)
    {
        if (push[i] != NULL)
        {
            delete push[i];
            push[i] = NULL;
        }
    }

    Mix_FreeChunk(MoveSound);
    Mix_FreeChunk(CompleteSound);
    Mix_FreeChunk(Clicking);
    MoveSound = NULL;
    CompleteSound = NULL;
    Clicking = NULL;

    Mix_FreeMusic(gMusic);
    gMusic = NULL;

    TTF_CloseFont(gFont);
    gFont = NULL;

    gPushObject.free();
    gMainChar.free();
    gTileTexture.free();
    gBackground.free();

    for (int i = 0; i < 3; i++)
    {
        gTextTexture[i].free();
    }

    SDL_DestroyWindow( gWindow );
    SDL_DestroyRenderer( gRenderer );
    gWindow = NULL;
    gRenderer = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

bool checkCollision( SDL_Rect a, SDL_Rect b )
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    return true;
}

bool touchesWall( SDL_Rect box, Tile* tiles[] )
{
    for( int i = 0; i < TOTAL_TILES; ++i )
    {
        if( ( tiles[ i ]->getType() >= TILE_PLANK ) && ( tiles[ i ]->getType() <= TILE_BRICK ) )
        {
            if( checkCollision( box, tiles[ i ]->getBox() ) )
            {
                return true;
            }
        }
    }

    return false;
}

bool WinGame(int goalNum, PushObject* box[])
{
    int count = 0;
    for (int i = 0; i < goalNum; ++i )
    {
        if (box[i]->getObjectStatus() == GOAL)
        {
            count++;
        }
    }
    if (count == goalNum) return true;
    else return false;
}

