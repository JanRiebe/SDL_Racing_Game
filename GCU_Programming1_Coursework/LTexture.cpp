#include "LTexture.h"
#include <SDL.h>
#include <SDL_image.h>


LTexture::LTexture()
{
	//Initialize 
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}


LTexture::~LTexture()
{
	//Deallocate 
	free();
}






void LTexture::free() {
	//Free texture if it exists 
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}



int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}
