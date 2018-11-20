#pragma once
#include <SDL.h>

class cSprite;

class cCamera
{
private:
	SDL_Point pos;
	SDL_Rect viewport;			// Specifies the area in the window that this camera is rendered to.
	cSprite* target;			// A target which the camera will follow.
	SDL_Point offset;
public:
	cCamera();
	~cCamera();
	void SetViewport(SDL_Rect v);
	void SetPosition(SDL_Point position);
	SDL_Point GetPosition();
	SDL_Rect GetViewport();
	// Translates from world position to screen position using the camera position.
	SDL_Rect WorldToScreen(SDL_Rect worldPosition);
	SDL_Point WorldToScreen(SDL_Point worldPosition);
	void update(double deltaTime);
	// Define a target the camera will follow.
	void setTarget(cSprite* t);
};

