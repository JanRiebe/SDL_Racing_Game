#pragma once
#include "LTexture.h"


struct Animation
{
	int start;
	int length;
};


class AnimatedTexture : public LTexture
{
public:
	AnimatedTexture();
	void renderAnimated(int x, int y);
	void play(bool p = true);
	void update(double deltaTime);
	bool loadFromFile(std::string path, int rows, int collumns, int startFrame = 0, int length = 0);
	bool isPlaying();

private:
	double speed;
	double timer;
	bool playing;
	int collumns;
	int rows;
	int startFrame;
	int length;
	SDL_Rect spriteClip;
};




