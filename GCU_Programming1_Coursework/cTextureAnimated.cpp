
#include "cTextureAnimated.h"


cTextureAnimated::cTextureAnimated() : cTexture()
{
	cout << "cteating animated texture "<<endl;
	timer = 1;
	speed = 3;
	playing = true;
}

void cTextureAnimated::renderAnimated(SDL_Renderer * theRenderer, SDL_Rect * theDestRect, FPoint theScaling)
{
	renderTexture(theRenderer, getTexture(), findSourceRect(), theDestRect, theScaling);
}

void cTextureAnimated::renderAnimated(SDL_Renderer * theRenderer, SDL_Rect * theDestRect, double rotAngle, SDL_Point * spriteCentre, FPoint theScaling)
{
	renderTexture(theRenderer, getTexture(), findSourceRect(), theDestRect, rotAngle, spriteCentre, theScaling);
}


void cTextureAnimated::play(bool p)
{
	playing = p;
}

void cTextureAnimated::update(double deltaTime)
{
	if (playing)
		timer += deltaTime * speed;
}

bool cTextureAnimated::loadTexture(LPCSTR theFilename, SDL_Renderer * theRenderer, int rows, int collumns/*, int startFrame, int length*/)
{
	bool success = cTexture::loadTexture(theFilename, theRenderer);

	// Setting the tile rows and collumns.
	this->collumns = collumns;
	this->rows = rows;
	// Setting which of these tiles belong to the animation.
	//this->startFrame = startFrame;
	//this->length = length;

	// Correcting the animation length, if it's longer than tiles available.
	// Also, setting the length to full length if it wasn't specified.
	//if (startFrame + length > collumns*rows || length == 0)
	length = collumns*rows;// -startFrame;
	

	// Setting the width of the tiles.
	sourceRect.w = getTWidth() / collumns;
	sourceRect.h = getTHeight() / rows;

	return success;
}

bool cTextureAnimated::isPlaying()
{
	return playing;
}

SDL_Rect* cTextureAnimated::findSourceRect()
{
	// Calculating the frame from the timer value.
	// Looping the frame number from the available tiles.
	//int frame = 0;
	//if (length != 0)
	//{
	int frame =/* startFrame*/ +((int)timer) % (length);

	//}
	// If the length set for the animation clip is 0.
	// Frame zero is used an an error message printed.
	//cout << "Error: Animation clip with length 0.\n";

	// Calculating the position of the sprite clip using the frame number,
	// the amount of tiles and the fixed width and height of a tile.
	sourceRect.x = sourceRect.w * (frame % collumns);
	sourceRect.y = sourceRect.h * (frame / rows);

	return &sourceRect;
}
