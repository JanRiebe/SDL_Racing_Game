#pragma once
#include "cSprite.h"

class cSpriteButton :
	public cSprite
{
public:
	cSpriteButton();
	~cSpriteButton();

	void OnClick();

	void OnSelect();
	void OnDeSelect();
};

