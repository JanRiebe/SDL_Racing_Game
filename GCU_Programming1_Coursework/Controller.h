/***************************************************************
Controllers use input from input channels to control
in game behaviour, such as the movement of player characters
or the interaction with buttons.

This controller is currently written for testing.
****************************************************************/

#pragma once
#include "IInputChannelListener.h"

class cCamera;

class Controller :
	public IInputChannelListener
{
public:
	int testControllerID;
	Controller(int);
	void OnEvent(AbstractEvent e);
	cCamera* cam;

};

