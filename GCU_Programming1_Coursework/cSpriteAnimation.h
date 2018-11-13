#pragma once
#include "cSpriteSheet.h"

class cSpriteAnimation :
	public cSpriteSheet
{
private:
	double speed;
	double timer;
	int startFrame;
	int length;
	bool isPlaying;
	//Calculates the current frame based on the timer and the animation start frame and length.
	int getCurrentFrame();

public:
	cSpriteAnimation();
	~cSpriteAnimation();
	// Renders this sprite based on the internal variables spritePos_2D, spriteScale and spriteRotationAngle. This should be overwritten by subclasses and used in general for rendering. 
	virtual void render(SDL_Renderer* theRenderer, cCamera* theCamera);
	//Renders the current frame of the animation.
	void render(SDL_Renderer* theRenderer, SDL_Rect* theDestRect, FPoint theScaling);
	//Renders the current frame of the animation. Allows rotating.
	void render(SDL_Renderer* theRenderer, SDL_Rect* theDestRect, double rotAngle, SDL_Point* spriteCentre, FPoint theScaling);
	//Starts the animation.
	void play();
	//Pauses the animation.
	void pause();
	//Resets the animation timer to the start. Does not pause playback.
	void reset();
	//Updates the animation timer.
	virtual void update(double deltaTime);
	//Trims the animation to show only a range of tiles from the sprite sheet.
	void trim(int animStartFrame, int animLength);
	//Set the playbackspeed in frames per second.
	void setSpeed(float framesPerSecond);
};

