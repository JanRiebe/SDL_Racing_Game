#pragma once
#include "gameHeaders.h"
class IScene
{
private:
	vector<cSprite> sprites;
	cCamera camera;
public:
	IScene();
	virtual ~IScene();
	virtual void update(double deltaTime) = 0;
	virtual void render(SDL_Renderer* theRenderer) = 0;
};

