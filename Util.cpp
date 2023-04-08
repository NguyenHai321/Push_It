#include "Util.h"
#include "Tile.h"

bool init()
{
    bool success = true;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "failed to initialized %s/n", SDL_GetError() );
    }
    else
    {
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf("linear texture has error /n" );
        }
        gWindow = SDL_CreateWindow ( "Push The Box", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf("Window can not be created: %s/n", SDL_GetError() );
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            if( gRenderer == NULL )
            {
                printf("Renderer can not be created: %s/n", SDL_GetError() );
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf("SDL_Image could not be initialized %s/n", SDL_GetError() );
                    success = false;
                }
            }
        }
    }
    return success;
}

bool loadMedia( Tile* tiles[], const char* map_path )
{
    bool success = true;

    if( !gMainChar.loadFromFile( "Texture/The_thing.png" ) )
    {
        printf( "failed to load mainChar texture /n" );
        success = false;
    }

    if( !gTileTexture.loadFromFile( "Texture/TileTexture.png" ) )
    {
        printf( "failed to load tile texture /n" );
        success = false;
    }

    if( !setTiles( tiles, map_path ) )
    {
        printf( "failed to load tile map /n");
        success = false;
    }

    if( !gPushObject.loadFromFile( "Texture/PushObject.png" ) )
    {
        printf( "failed to load object texture /n");
    }

    return success;
}

void close( Tile* tiles[] )
{
    for( int i = 0; i < TOTAL_TILES; i++ )
    {
        if( tiles[ i ] != NULL )
        {
            delete tiles[ i ];
            tiles[ i ] = NULL;
        }
    }


    gPushObject.free();
    gMainChar.free();
    gTileTexture.free();

    SDL_DestroyWindow( gWindow );
    SDL_DestroyRenderer( gRenderer );
    gWindow = NULL;
    gRenderer = NULL;

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


bool setTiles( Tile* tiles[], const char* map_path )
{
	bool tilesLoaded = true;

    //The tile offsets
    int x = 252, y = 72;

    //Open the map
    std::ifstream map( map_path );

    //If the map couldn't be loaded
    if( map.fail() )
    {
		printf( "Unable to load map file!\n" );
		tilesLoaded = false;
    }
	else
	{
		for( int i = 0; i < TOTAL_TILES; ++i )
		{
			int tileType = -1;

			map >> tileType;

			if( map.fail() )
			{
				printf( "Error loading map: Unexpected end of file!\n" );
				tilesLoaded = false;
				break;
			}

			if( ( tileType >= 0 ) && ( tileType < TOTAL_TILE_SPRITES ) )
			{
				tiles[ i ] = new Tile( x, y, tileType );
			}
			else
			{
				printf( "Error loading map: Invalid tile type at %d!\n", i );
				tilesLoaded = false;
				break;
			}

			x += TILE_WIDTH;

			if( x >= 828 )
			{
				x = 252;

				y += TILE_HEIGHT;
			}
		}

		if( tilesLoaded )
		{
            // chinh lay tileType
			gTileClips[ TILE_GRASS ].x = 0;
			gTileClips[ TILE_GRASS ].y = 0;
			gTileClips[ TILE_GRASS ].w = TILE_WIDTH;
			gTileClips[ TILE_GRASS ].h = TILE_HEIGHT;

			gTileClips[ TILE_FLOWER ].x = 0;
			gTileClips[ TILE_FLOWER ].y = 48;
			gTileClips[ TILE_FLOWER ].w = TILE_WIDTH;
			gTileClips[ TILE_FLOWER ].h = TILE_HEIGHT;

			gTileClips[ TILE_DEATH ].x = 0;
			gTileClips[ TILE_DEATH ].y = 96;
			gTileClips[ TILE_DEATH ].w = TILE_WIDTH;
			gTileClips[ TILE_DEATH ].h = TILE_HEIGHT;

			gTileClips[ TILE_PLANK ].x = 48;
			gTileClips[ TILE_PLANK ].y = 0;
			gTileClips[ TILE_PLANK ].w = TILE_WIDTH;
			gTileClips[ TILE_PLANK ].h = TILE_HEIGHT;

			gTileClips[ TILE_BRICK ].x = 96;
			gTileClips[ TILE_BRICK ].y = 0;
			gTileClips[ TILE_BRICK ].w = TILE_WIDTH;
			gTileClips[ TILE_BRICK ].h = TILE_HEIGHT;

			gTileClips[ TILE_FLOOR ].x = 48;
			gTileClips[ TILE_FLOOR ].y = 48;
			gTileClips[ TILE_FLOOR ].w = TILE_WIDTH;
			gTileClips[ TILE_FLOOR ].h = TILE_HEIGHT;

			gTileClips[ TILE_GOAL ].x = 96;
			gTileClips[ TILE_GOAL ].y = 48;
			gTileClips[ TILE_GOAL ].w = TILE_WIDTH;
			gTileClips[ TILE_GOAL ].h = TILE_HEIGHT;

			gTileClips[ TILE_VOID ].x = 96;
			gTileClips[ TILE_VOID ].y = 96;
			gTileClips[ TILE_VOID ].w = TILE_WIDTH;
			gTileClips[ TILE_VOID ].h = TILE_HEIGHT;

			gTileClips[ TILE_SAND ].x = 48;
			gTileClips[ TILE_SAND ].y = 96;
			gTileClips[ TILE_SAND ].w = TILE_WIDTH;
			gTileClips[ TILE_SAND ].h = TILE_HEIGHT;
		}
	}

    map.close();

    return tilesLoaded;
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

void setObject()
{
    gObjectClips[ GOAL ].x = 48;
    gObjectClips[ GOAL ].y = 0;
    gObjectClips[ GOAL ].h = TILE_HEIGHT;
    gObjectClips[ GOAL ].w = TILE_WIDTH;

    gObjectClips[ GOAL_NOT ].x = 0;
    gObjectClips[ GOAL_NOT ].y = 0;
    gObjectClips[ GOAL_NOT ].h = TILE_HEIGHT;
    gObjectClips[ GOAL_NOT ].w = TILE_WIDTH;
}

bool getToGoal( SDL_Rect a, SDL_Rect b )
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

    if( ( bottomA != bottomB ) || ( topA != topB ) || ( leftA != leftB ) || ( rightA != rightB ) )
    {
        return false;
    }
    return true;
}
