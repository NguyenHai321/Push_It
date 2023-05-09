#ifndef BUTTON_H_
#define BUTTON_H_

#include "LTexture.h"

class LButton
{
public:
	//Initializes internal variables
	LButton();

	//Sets top left position
	void setPosition(int x, int y);

	//Handles mouse event
	bool handleEvent(SDL_Event* e, SDL_Rect Buttons);

	//Shows button sprite
	void render();

private:
	//Top left position
	SDL_Point mPosition;

};

#endif // !BUTTON_H_

