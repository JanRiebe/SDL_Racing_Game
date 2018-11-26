#include "cSpriteButton.h"
#include "gameHeaders.h"
#include <iostream>


cSpriteButton::cSpriteButton()
{
	callbackFunction = NULL;
}


cSpriteButton::~cSpriteButton()
{
}

void cSpriteButton::OnClick()
{
	cout << "Button clicked\n";

	// Evoking function pointer
	if (callbackFunction)
		callbackFunction();
}

void cSpriteButton::OnSelect()
{
	tint.g = 100;
}

void cSpriteButton::OnDeSelect()
{
	tint.g = 255;
}

// My research on function pointers: https://www.cprogramming.com/tutorial/function-pointers.html
void cSpriteButton::setCallbackFunction(void (* functionPointer)())
{
	callbackFunction = functionPointer;
}
