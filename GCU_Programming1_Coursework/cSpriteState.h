#pragma once
#include "cSpriteSheet.h"
class cSpriteState :
	public cSpriteSheet
{
private:
	int state;
public:
	cSpriteState();
	~cSpriteState();
	// Renders this sprite based on the internal variables spritePos_2D, spriteScale and spriteRotationAngle. This should be overwritten by subclasses and used in general for rendering. 
	virtual void render(SDL_Renderer* theRenderer, cCamera* theCamera);
	
	// Sets which sprite from the sprite sheet should be rendered.
	void setState(int s);
};

