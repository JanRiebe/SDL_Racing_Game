#pragma once
#include "IInputChannelListener.h"

class cCar;
class cSpriteText;

class cPlayer :
	public IInputChannelListener
{
private:
	//cCar* car;
	int score;
	cSpriteText* scoreSprite;

public:
	cPlayer();
	~cPlayer();
	cCar* car;
	void setScoreSprite(cSpriteText* s);

	void OnEvent(AbstractEvent e);

	void OnReachedSafeHouse();
};

