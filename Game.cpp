#include "Game.h"
#include "Constant.h"
#include "Tile.h"
#include "Push_Object.h"
#include "LTexture.h"
#include "Global.h"
#include "MainChar.h"
#include "Util.h"
#include "LButton.h"

#include <string.h>

Game::Game()
{
	currentLevel = 1;
	
	gamestate = menu;

	Rabbit_pos = 0;

	numOfBox = 0;
}

bool Game::Level(Tile* tiles[], PushObject* Boxes[], const char* map_data)
{
	int x = 252, y = 72;

	std::ifstream map(map_data);

	if (map.fail())
	{
		std::cout << "map failed to load" << std::endl;
		return false;
	}
	else
	{
		map >> numOfBox;
		for (int i = 0; i < numOfBox; i++)
		{
			int pos = -1;

			map >> pos;
			Boxes[i] = new PushObject(pos);
		}
		gObjectClips[GOAL].x = 48;
		gObjectClips[GOAL].y = 0;
		gObjectClips[GOAL].h = TILE_HEIGHT;
		gObjectClips[GOAL].w = TILE_WIDTH;

		gObjectClips[GOAL_NOT].x = 0;
		gObjectClips[GOAL_NOT].y = 0;
		gObjectClips[GOAL_NOT].h = TILE_HEIGHT;
		gObjectClips[GOAL_NOT].w = TILE_WIDTH;

		map >> Rabbit_pos;

		for (int i = 0; i < TOTAL_TILES; ++i)
		{
			int tileType = -1;

			map >> tileType;

			if (map.fail())
			{
				printf("Error loading map: Unexpected end of file!\n");
				return false;
			}

			if ((tileType >= 0) && (tileType < TOTAL_TILE_SPRITES))
			{
				tiles[i] = new Tile(x, y, tileType);
				if (tileType == 03 || tileType == 04)
				{
					tiles[i]->setOccupied();
				}
			}
			else
			{
				printf("Error loading map: Invalid tile type at %d!\n", i);
				return false;
			}

			x += TILE_WIDTH;

			if (x >= 828)
			{
				x = 252;

				y += TILE_HEIGHT;
			}
		}
			// chinh lay tileType
		gTileClips[TILE_GRASS].x = 0;
		gTileClips[TILE_GRASS].y = 0;
		gTileClips[TILE_GRASS].w = TILE_WIDTH;
		gTileClips[TILE_GRASS].h = TILE_HEIGHT;

		gTileClips[TILE_FLOWER].x = 0;
		gTileClips[TILE_FLOWER].y = 48;
		gTileClips[TILE_FLOWER].w = TILE_WIDTH;
		gTileClips[TILE_FLOWER].h = TILE_HEIGHT;

		gTileClips[TILE_DEATH].x = 0;
		gTileClips[TILE_DEATH].y = 96;
		gTileClips[TILE_DEATH].w = TILE_WIDTH;
		gTileClips[TILE_DEATH].h = TILE_HEIGHT;

		gTileClips[TILE_PLANK].x = 48;
		gTileClips[TILE_PLANK].y = 0;
		gTileClips[TILE_PLANK].w = TILE_WIDTH;
		gTileClips[TILE_PLANK].h = TILE_HEIGHT;

		gTileClips[TILE_BRICK].x = 96;
		gTileClips[TILE_BRICK].y = 0;
		gTileClips[TILE_BRICK].w = TILE_WIDTH;
		gTileClips[TILE_BRICK].h = TILE_HEIGHT;

		gTileClips[TILE_FLOOR].x = 48;
		gTileClips[TILE_FLOOR].y = 48;
		gTileClips[TILE_FLOOR].w = TILE_WIDTH;
		gTileClips[TILE_FLOOR].h = TILE_HEIGHT;

		gTileClips[TILE_GOAL].x = 96;
		gTileClips[TILE_GOAL].y = 48;
		gTileClips[TILE_GOAL].w = TILE_WIDTH;
		gTileClips[TILE_GOAL].h = TILE_HEIGHT;

		gTileClips[TILE_VOID].x = 96;
		gTileClips[TILE_VOID].y = 96;
		gTileClips[TILE_VOID].w = TILE_WIDTH;
		gTileClips[TILE_VOID].h = TILE_HEIGHT;

		gTileClips[TILE_SAND].x = 48;
		gTileClips[TILE_SAND].y = 96;
		gTileClips[TILE_SAND].w = TILE_WIDTH;
		gTileClips[TILE_SAND].h = TILE_HEIGHT;
	}
	map.close();
	return true;
}

void Game::deLevel(Tile* tiles[], PushObject* Boxes[], int num)
{
	for (int i = 0; i < TOTAL_TILES; i++)
	{
		if (tiles[i] != NULL)
		{
			delete tiles[i];
			tiles[i] = NULL;
		}
	}

	for (int i = 0; i < num; ++i)
	{
		if (Boxes[i] != NULL)
		{
			delete Boxes[i];
			Boxes[i] = NULL;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		gTextTexture[i].free();
	}

	gPushObject.free();
	gMainChar.free();
	gTileTexture.free();
	gRetry[0].free();
	gRetry[1].free();
	gLevelText.free();
}

bool Game::Menu(SDL_Color Color)
{
	return true;
}

void Game::Button()
{

}

bool Game::Music()
{
	gMusic = Mix_LoadMUS("assets/background_music.wav");
	if (gMusic == NULL)
	{
		std::cout << "gMusic can not be loaded " << std::endl;
		return false;
	}

	MoveSound = Mix_LoadWAV("assets/move_sound.wav");
	if (MoveSound == NULL)
	{
		std::cout << "Move sound can not be loaded" << std::endl;
		return false;
	}

	CompleteSound = Mix_LoadWAV("assets/complete_music.wav");
	if(CompleteSound == NULL)
	{
		std::cout << "Complete sound can not be loaded" << std::endl;
		return false;
	}
	Clicking = Mix_LoadWAV("assets/click.wav");
	if (Clicking == NULL)
	{
		std::cout << "Clicking sound can not be loaded" << std::endl;
		return false;
	}
	return true;
}

bool Game::visualize()
{
	if (!init())
	{
		std::cout << "failed to initialized" << std::endl;
		return false;
	}
	else if (!loadMedia())
	{
		std::cout << "Failed to load media!" << std::endl;
		return false;
	}
	else
	{
		Music();

		SDL_Color textColor0 = { 0, 0, 0 };
		SDL_Color textColor1 = { 0, 0, 0 };
		SDL_Color textColor2 = { 0, 0, 0 };
		SDL_Color WinText1 = { 0, 0, 0 };
		SDL_Color WinText2 = { 0, 0, 0 };
		SDL_Color WinText3 = { 0, 0, 0 };
		SDL_Color LevelText = { 0, 0, 0 };
		bool quit = false;
		SDL_Event e;

		Tile* tileSet[TOTAL_TILES];
		PushObject* Boxes[5];
		mainChar Rabbit;
		LButton gButton;

		status move = NONE;

		std::string level;

		SDL_Rect Background = { 0, 0, 1080, 720 };

		Level(tileSet, Boxes, "map/map1.map");

		while (!quit)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
				if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					Mix_PlayChannel(-1, Clicking, 0);
				}
				if (e.type == SDL_KEYDOWN && e.key.repeat == 0 && gamestate == playing)
				{
					switch (e.key.keysym.sym)
					{
					case SDLK_UP:
						Mix_PlayChannel(-1, MoveSound, 0);
						break;
					case SDLK_DOWN:
						Mix_PlayChannel(-1, MoveSound, 0);
						break;
					case SDLK_LEFT:
						Mix_PlayChannel(-1, MoveSound, 0);
						break;
					case SDLK_RIGHT:
						Mix_PlayChannel(-1, MoveSound, 0);
						break;
					}
				}
// Menu Button 
				if (gButton.handleEvent(&e, gTextTexture[0].getBox()))
				{
					if (e.type == SDL_MOUSEMOTION)
					{
						textColor0 = { 255, 0, 0 };
					}
					else if (e.type == SDL_MOUSEBUTTONDOWN)
					{
						textColor0 = { 0, 255, 0 };
					}
					else if (e.type == SDL_MOUSEBUTTONUP)
					{
						textColor0 = { 0, 0, 255 };
						currentLevel = 1;
						gamestate = loading;
					}
				}
				else
				{
					textColor0 = { 255, 255, 255 };
				}

				if (gButton.handleEvent(&e, gTextTexture[1].getBox()))
				{
					if (e.type == SDL_MOUSEMOTION)
					{
						textColor1 = { 255, 0, 0 };
					}
					else if (e.type == SDL_MOUSEBUTTONDOWN)
					{
						textColor1 = { 0, 255, 0 };
					}
					else if (e.type == SDL_MOUSEBUTTONUP)
					{
						textColor1 = { 0, 0, 255 };
					}
				}
				else
				{
					textColor1 = { 255, 255, 255 };
				}

				if (gButton.handleEvent(&e, gTextTexture[2].getBox()))
				{
					if (e.type == SDL_MOUSEMOTION)
					{
						textColor2 = { 255, 0, 0 };
					}
					else if (e.type == SDL_MOUSEBUTTONDOWN)
					{
						textColor2 = { 0, 255, 0 };
					}
					else if (e.type == SDL_MOUSEBUTTONUP)
					{
						textColor2 = { 0, 0, 255 };
						quit = true;
					}
				}
				else
				{
					textColor2 = { 255, 255, 255 };
				}
// After Wingame
				if (gButton.handleEvent(&e, gWinText[0].getBox()))
				{
					if (e.type == SDL_MOUSEMOTION)
					{
						WinText1 = { 255, 0, 0 };
					}
					else if (e.type == SDL_MOUSEBUTTONDOWN)
					{
						WinText1 = { 0, 255, 0 };
					}
					else if (e.type == SDL_MOUSEBUTTONUP)
					{
						WinText1 = { 0, 0, 255 };
						currentLevel++;
						TTF_CloseFont(WinFont);
						WinFont = NULL;
						gamestate = loading;
						deLevel(tileSet, Boxes, numOfBox);
					}
				}
				else
				{
					WinText1 = { 0, 0, 0 };
				}

				if (gButton.handleEvent(&e, gWinText[1].getBox()))
				{
					if (e.type == SDL_MOUSEMOTION)
					{
						WinText2 = { 255, 0, 0 };
					}
					else if (e.type == SDL_MOUSEBUTTONDOWN)
					{
						WinText2 = { 0, 255, 0 };
					}
					else if (e.type == SDL_MOUSEBUTTONUP)
					{
						WinText2 = { 0, 0, 255 };
						TTF_CloseFont(WinFont);
						WinFont = NULL;
						gamestate = loading;
						deLevel(tileSet, Boxes, numOfBox);
					}
				}
				else
				{
					WinText2 = { 0, 0, 0 };
				}

				if (gButton.handleEvent(&e, gWinText[2].getBox()))
				{
					if (e.type == SDL_MOUSEMOTION)
					{
						WinText3 = { 255, 0, 0 };
					}
					else if (e.type == SDL_MOUSEBUTTONDOWN)
					{
						WinText3 = { 0, 255, 0 };
					}
					else if (e.type == SDL_MOUSEBUTTONUP)
					{
						WinText3 = { 0, 0, 255 };
						TTF_CloseFont(WinFont);
						WinFont = NULL;
						gamestate = menu;
						deLevel(tileSet, Boxes, numOfBox);
					}
				}
				else
				{
					WinText3 = { 0, 0, 0 };
				}
// Retry level
				if (gButton.handleEvent(&e, gRetry[0].getBox()))
				{
					if (e.type == SDL_MOUSEBUTTONUP)
					{
						gamestate = loading;
						deLevel(tileSet, Boxes, numOfBox);
					}
				}
				if (gButton.handleEvent(&e, gRetry[1].getBox()))
				{
					if (e.type == SDL_MOUSEBUTTONUP)
					{
						gamestate = menu;
						deLevel(tileSet, Boxes, numOfBox);
					}
				}
				Rabbit.handleEvent(e);
			}

// IN GAME

			if (Mix_PlayingMusic() == 0)
			{
				Mix_PlayMusic(gMusic, -1);
			}
			if (gamestate == loading)
			{
				loadMedia();
				level = std::to_string(currentLevel);
				gLevelText.loadFromRenderedText(level, LevelText, WinFont);
				switch (currentLevel)
				{
				case 1:
					gamestate = playing;
					Level(tileSet, Boxes, "map/map1.map");
					Rabbit.updatePos(Rabbit_pos);
					Rabbit.resetStatus();
					break;
				case 2:	
					gamestate = playing;
					Level(tileSet, Boxes, "map/map2.map");
					Rabbit.updatePos(Rabbit_pos);
					Rabbit.resetStatus();
					break;
				case 3:
					gamestate = playing;
					Level(tileSet, Boxes, "map/map3.map");
					Rabbit.updatePos(Rabbit_pos);
					Rabbit.resetStatus();
					break;
				case 4:
					gamestate = playing;
					Level(tileSet, Boxes, "map/map4.map");
					Rabbit.updatePos(Rabbit_pos);
					Rabbit.resetStatus();
					break;
				case 5:
					gamestate = playing;
					Level(tileSet, Boxes, "map/map5.map");
					Rabbit.updatePos(Rabbit_pos);
					Rabbit.resetStatus();
					break;
				case 6:
					gamestate = playing;
					Level(tileSet, Boxes, "map/map6.map");
					Rabbit.updatePos(Rabbit_pos);
					Rabbit.resetStatus();
					break;
				case 7:
					gamestate = playing;
					Level(tileSet, Boxes, "map/map7.map");
					Rabbit.updatePos(Rabbit_pos);
					Rabbit.resetStatus();
					break;
				case 8:
					gamestate = playing;
					Level(tileSet, Boxes, "map/map8.map");
					Rabbit.updatePos(Rabbit_pos);
					Rabbit.resetStatus();
					break;
				case 9:
					gamestate = playing;
					Level(tileSet, Boxes, "map/map9.map");
					Rabbit.updatePos(Rabbit_pos);
					Rabbit.resetStatus();
					break;
				case 10:
					gamestate = playing;
					Level(tileSet, Boxes, "map/map10.map");
					Rabbit.updatePos(Rabbit_pos);
					Rabbit.resetStatus();
					break;
				}
			}
			else if (gamestate == menu)
			{	
				gTextTexture[0].loadFromRenderedText("Start", textColor0, gFont);

				gTextTexture[1].loadFromRenderedText("Continue", textColor1, gFont);

				gTextTexture[2].loadFromRenderedText("Quit", textColor2, gFont);

				SDL_RenderClear(gRenderer);

				gBackground.render(0, 0, &Background);

				gTextTexture[0].render(790, 300);
				gTextTexture[1].render(790, 400);
				gTextTexture[2].render(790, 500);

				SDL_RenderPresent(gRenderer);
			}
			else if (gamestate == playing)
			{
				Rabbit.move(tileSet, Boxes, numOfBox);

				SDL_RenderClear(gRenderer);
				//Render level
				gRetry[0].render(952, 0);
				gRetry[1].render(1016, 0);
				gLevelText.render(10, 10);
				for (int i = 0; i < TOTAL_TILES; ++i)
				{
					tileSet[i]->render();
				}
				for (int i = 0; i < numOfBox; i++)
				{
					Boxes[i]->render();
				}
				Rabbit.render();
				if (WinGame(numOfBox, Boxes))
				{
					gamestate = win;
				}

				SDL_RenderPresent(gRenderer);
			}
			else if (gamestate == win)
			{
				gWinText[0].loadFromRenderedText("Continue", WinText1, WinFont);
				gWinText[1].loadFromRenderedText("Retry", WinText2, WinFont);
				gWinText[2].loadFromRenderedText("Menu", WinText3, WinFont);

				SDL_RenderClear(gRenderer);
				gWinText[0].render(260, 260);
				gWinText[1].render(650, 260);
				gWinText[2].render(450, 360);
				SDL_RenderPresent(gRenderer);

			}
		}
		close(tileSet, Boxes, numOfBox);
	}
	return true;
}


int Game::getCurrentLevel()
{
	return currentLevel;
}

void Game::updateLevel(int i)
{
	currentLevel = i;
}

gameState Game::getGameState()
{
	return gameState();
}

