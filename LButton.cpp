#include "LButton.h"
#include "Constant.h"

LButton::LButton()
{
	mPosition.x = 0;
	mPosition.y = 0;
}

void LButton::setPosition(int x, int y)
{
	mPosition.x = x;
	mPosition.y = y;
}

bool LButton::handleEvent(SDL_Event* e, SDL_Rect Button)
{
	//If mouse event happened
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if (x < Button.x)
		{
			inside = false;
		}
		//Mouse is right of the button
		else if (x > Button.x + Button.w)
		{
			inside = false;
		}
		//Mouse above the button
		else if (y < Button.y)
		{
			inside = false;
		}
		//Mouse below the button
		else if (y > Button.y + Button.h)
		{
			inside = false;
		}

		//Mouse is outside button
		if (!inside)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	return false;
}

void LButton::render()
{

}