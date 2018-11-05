#pragma once

#include "AbstractEvent.h"

class InputChannel;

class IInputChannelListener
{
private:
	//The channel this listener has registered to. Saved so that the destructor can unregister.
	InputChannel* channel;
public:
	virtual ~IInputChannelListener();
	//Call this to register this listener to a channel.
	void Register(InputChannel* channel);
	//Overwrite this to recieve events.
	virtual void OnEvent(AbstractEvent e) = 0;

};

