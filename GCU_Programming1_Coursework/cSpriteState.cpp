#include "cSpriteState.h"



cSpriteState::cSpriteState(): cSpriteSheet()
{
	state = 0;
}


cSpriteState::~cSpriteState()
{
}

void cSpriteState::render(SDL_Renderer * theRenderer, cCamera * theCamera)
{
	// Using the state as an index for cSpriteSheet to find the target rect.
	cSpriteSheet::render(theRenderer, state, &theCamera->WorldToScreen(transform), (double)spriteRotationAngle, &spriteCentre, spriteScale);


	//TODO remove debugging
	SDL_Rect bBox = getBoundingBox();
	bBox = theCamera->WorldToScreen(bBox);
	SDL_RenderDrawRect(theRenderer, &bBox);
}

void cSpriteState::setState(int s)
{
	// Checking s within range of the tile sheet grid.
	if(s < getSheetRows()*getSheetColumns() && s >= 0)
		// Set the state.
		state = s;
}
