#include "cSpriteButton.h"
#include "gameHeaders.h"


cSpriteButton::cSpriteButton()
{
}


cSpriteButton::~cSpriteButton()
{
}

void cSpriteButton::OnClick()
{
	cout << "Button clicked\n";
}

void cSpriteButton::OnSelect()
{
	tint.g = 100;
}

void cSpriteButton::OnDeSelect()
{
	tint.g = 255;
}
