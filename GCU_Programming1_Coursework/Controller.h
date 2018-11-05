#pragma once
#include "IInputChannelListener.h"


class Controller :
	public IInputChannelListener
{
public:
	int testControllerID;
	Controller(int);
	void OnEvent(AbstractEvent e);

};

