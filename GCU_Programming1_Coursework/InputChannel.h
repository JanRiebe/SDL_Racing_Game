#pragma once

#include <vector>
#include "AbstractEvent.h"

class IInputChannelListener;

class InputChannel
{
public:
	//Register a listener to this channel
	void Register(IInputChannelListener* listener);
	void UnRegister(IInputChannelListener* listener);
	//Passes the event on to all listeners.
	void RecieveEvent(AbstractEvent e);
private:
	std::vector<IInputChannelListener*> listeners;
};

