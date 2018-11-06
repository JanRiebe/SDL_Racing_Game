#pragma once
#include "gameHeaders.h"


struct Animation
{
	int start;
	int length;
};


class cTextureAnimated : public cTexture
{
public:
	cTextureAnimated();
	void renderAnimated(SDL_Renderer* theRenderer, SDL_Rect* theDestRect, FPoint theScaling);
	void renderAnimated(SDL_Renderer* theRenderer, SDL_Rect* theDestRect, double rotAngle, SDL_Point* spriteCentre, FPoint theScaling);
	void play(bool p = true);
	void update(double deltaTime);
	bool loadTexture(LPCSTR theFilename, SDL_Renderer *theRenderer, int rows, int collumns, int startFrame = 0, int length = 0);
	bool isPlaying();

private:
	double speed;
	double timer;
	bool playing;
	int collumns;
	int rows;
	int startFrame;
	int length;
	SDL_Rect sourceRect;
	//Updates sourceRect to fit the current frame of the animation
	SDL_Rect* findSourceRect();
};


