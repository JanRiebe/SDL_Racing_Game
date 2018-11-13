#pragma once
#include <SDL.h>
class cCamera
{
private:
	SDL_Point pos;
public:
	cCamera();
	~cCamera();
	void SetPosition(SDL_Point position);
	SDL_Point GetPosition();
	// Translates from world position to screen position using the camera position.
	SDL_Rect WorldToScreen(SDL_Rect worldPosition);
};

