#include "Util.h"
#include "Global.h"
#include "MainChar.h"
#include "Push_Object.h"

int main( int argc, char* args[] )
{
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//The level tiles
		Tile* tileSet[TOTAL_TILES];

		if( !loadMedia( tileSet, "map/map.map" ) )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			bool quit = false;

			SDL_Event e;

			mainChar Push;
            // chinh lai
			PushObject Object;

			//Level camera
			SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					//Handle input for the dot
					Push.handleEvent( e );
				}

				setObject();

				Object.move( tileSet, &Push );
				Object.ReachGoal( tileSet );

				//Move the object
				Push.move( tileSet );

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render level
				for( int i = 0; i < TOTAL_TILES; ++i )
				{
					tileSet[ i ]->render( camera );
				}

				Object.render( camera );

				//Render dot
				Push.render( camera );

				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}

		//Free resources and close SDL
		close( tileSet );
	}

	return 0;
}

