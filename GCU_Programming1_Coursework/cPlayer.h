#pragma once
#include "IInputChannelListener.h"
#include "GameConstants.h"

class cCar;
class cSpriteText;

class cPlayer :
	public IInputChannelListener
{
private:
	Teams team;

public:
	cPlayer(Teams team);
	~cPlayer();
	cCar* car;

	void OnEvent(AbstractEvent e);

	void OnReachedSafeHouse();
};

