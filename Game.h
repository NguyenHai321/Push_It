#ifndef GAME_H_
#define GAME_H_

#include "Tile.h"
#include "Constant.h"
#include "Push_Object.h"
#include "MainChar.h"

class Game
{
public:
	Game();

	bool Level(Tile* tiles[], PushObject* Boxes[], const char* map_data);
	void deLevel(Tile* tiles[], PushObject* Boxes[], int num);

	bool Menu(SDL_Color textColor);
	void Button();
	bool Music();

	bool visualize();

	int getCurrentLevel();
	void updateLevel(int i);

	gameState getGameState();

private:
	gameState gamestate;
	int currentLevel;
	int numOfBox;
	int Rabbit_pos;
};

#endif // GAME_H_

