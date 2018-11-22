#include "cSpriteText.h"
#include "cFontMgr.h"


cSpriteText::cSpriteText(SDL_Renderer* renderer, cFont* f, LPCSTR txtN)
{
	theRenderer = renderer;
	font = f;
	textureName = txtN;
	// Setting standard color to white and background to transparent.
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	background = color;
	background.a = 0;

	cSprite::cSprite();

}


cSpriteText::~cSpriteText()
{
}

void cSpriteText::setFont(cFont * f)
{
	font = f;
}

void cSpriteText::setColor(SDL_Color c)
{
	color = c;
}

void cSpriteText::setText(LPCSTR text)
{
	// Giving an error if no font has been set for this.
	if (!font)
	{
		cout << "Could not set text " << text << ", because no font has been set for this cSpriteText.\n";
		return;
	}

	// Delete any old texture with the texture name.
	cTextureMgr::getInstance()->deleteTexture(textureName);

	// Add a new texture containing the text.
	cTextureMgr::getInstance()->addTexture( textureName,
		font->createTextTexture(theRenderer, text, textType::solid, color, background)
		);

	// Setting the new texture as the texture for this sprite
	cSprite::setTexture(cTextureMgr::getInstance()->getTexture(textureName));
	
}

void cSpriteText::setText(int x, string str)
{
	str += " "+ to_string(x);
	LPCSTR lpc_str = str.c_str();		// This basically just creates a pointer to the string, so I need to keep the string in memory while I use this.
	setText(lpc_str);
}