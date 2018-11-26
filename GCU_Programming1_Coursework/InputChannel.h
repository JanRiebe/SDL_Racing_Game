/***************************************************************
User input is put through channel objects.

The input manager associates input from different devices
with channels so that the events in one channel represent
the input of one user.

The channel then passes on the events to all objects that
listen to it.
****************************************************************/

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
	// Indicates whether the listeners have been changed during an event update.
	// This might happen for example when a new scene is loaded.
	// Used by RecieveEvent to immediately stop the sending of events to listeners,
	// because listeners might have changed too much to continue iterating over it.
	bool noChangeToListenersSinceEvent;
};

