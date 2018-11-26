#pragma once
#include "cSprite.h"

class cSpriteButton :
	public cSprite
{
private:
	// The function that will be called when this button is clicked.
	void(*callbackFunction)();

public:
	cSpriteButton();
	~cSpriteButton();

	void OnClick();

	void OnSelect();
	void OnDeSelect();

	void setCallbackFunction(void(*functionPointer)());

};

