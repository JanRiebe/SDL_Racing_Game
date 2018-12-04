#pragma once
#include "IInputChannelListener.h"
#include "GameConstants.h"

class cCar;
class cSpriteText;

class cPlayer :
	public IInputChannelListener
{
private:
	string name;

public:
	cPlayer(string name);
	~cPlayer();
	cCar* car;

	void OnEvent(AbstractEvent e);

	void OnReachedCheckpoint();

	string getName();
};

