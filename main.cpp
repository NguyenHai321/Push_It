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
		PushObject* Object[2];
		if (!setObject(Object, "map/map_data.map"))
		{
			std::cout << "failed to load Object\n" << std::endl;
		}
		else if( !loadMedia( tileSet, "map/map.map" ) && !setObject(Object, "map/map_data.map") )
		{
			std::cout << "Failed to load media!\n" << std::endl;
		}
		else
		{
			bool quit = false;

			SDL_Event e;

			mainChar Rabbit;
            // chinh lai

			status move = NONE;

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
					Rabbit.handleEvent( e );
				}

				//Move the object
				Rabbit.move( tileSet, Object );

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render level
				for( int i = 0; i < TOTAL_TILES; ++i )
				{
					tileSet[ i ]->render();
				}

				Object[0]->render();
				Object[1]->render();

				//Render dot
				Rabbit.render();

				if (WinGame(2, Object))
				{
					std::cout << "Win" << std::endl;
				}

				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}

		//Free resources and close SDL
		close( tileSet, Object );
	}

	return 0;
}

