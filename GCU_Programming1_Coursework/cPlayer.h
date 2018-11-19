#pragma once
#include "IInputChannelListener.h"

class cCar;

class cPlayer :
	public IInputChannelListener
{
//private:
	//cCar* car;
public:
	cPlayer();
	~cPlayer();
	void OnEvent(AbstractEvent e);
	cCar* car;
};

