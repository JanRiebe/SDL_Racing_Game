#include "AnimatedTexture.h"



AnimatedTexture::AnimatedTexture() : LTexture()
{
	timer = 0;
	speed = 3;
}


void AnimatedTexture::renderAnimated(int x, int y)
{
	// Calculating the frame from the timer value.
	// Looping the frame number from the available tiles.
	int frame = startFrame + ((int)timer) % (length);

	// Calculating the position of the sprite clip using the frame number,
	// the amount of tiles and the fixed width and height of a tile.
	spriteClip.x = spriteClip.w * (frame % collumns);
	spriteClip.y = spriteClip.h * (frame / rows);
	render(x, y, &spriteClip);
}

void AnimatedTexture::play(bool p)
{
	playing = p;
}

void AnimatedTexture::update(double deltaTime)
{
	if (playing)
		timer += deltaTime * speed;
}

bool AnimatedTexture::loadFromFile(std::string path, int collumns, int rows, int startFrame, int length)
{
	bool success = LTexture::loadFromFile(path);

	// Setting the tile rows and collumns.
	this->collumns = collumns;
	this->rows = rows;
	// Setting which of these tiles belong to the animation.
	this->startFrame = startFrame;
	this->length = length;

	// Correcting the animation length, if it's longer than tiles available.
	// Also, setting the length to full length if it wasn't specified.
	if (startFrame + length > collumns*rows || length == 0)
		length = collumns*rows - startFrame;


	// Setting the width of the tiles.
	spriteClip.w = getWidth() / collumns;
	spriteClip.h = getHeight() / rows;

	return success;
}

bool AnimatedTexture::isPlaying()
{
	return playing;
}
