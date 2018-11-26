#include "InputChannel.h"
#include "IInputChannelListener.h"
#include <algorithm>


void InputChannel::Register(IInputChannelListener * addThis)
{
	listeners.push_back(addThis);

	// Setting flag that the listeners have been updated.
	noChangeToListenersSinceEvent = false;
}



void InputChannel::UnRegister(IInputChannelListener * removeThis)
{
	//Removing the pointer "removeThis" from the vector of listeners.
	//Using erase-remove idiom.
	//Research: https://stackoverflow.com/questions/3385229/c-erase-vector-element-by-value-rather-than-by-position#3385251
	listeners.erase(std::remove(listeners.begin(), listeners.end(), removeThis), listeners.end());
	
	// Setting flag that the listeners have been updated.
	noChangeToListenersSinceEvent = false;
}



void InputChannel::RecieveEvent(AbstractEvent e)
{
	// Setting flag that the listeners have not been updated, since the event has been recieved.
	noChangeToListenersSinceEvent = true;

	// Iterating through all listeners,
	// sending them the event.
	std::vector<IInputChannelListener*>::iterator iter = listeners.begin();
	// Using a while loop, because elements might get deleted
	// during the call to OnEvent,
	// in which case the flag noChangeToListenersSinceEvent becomes false,
	// and the sending of events to the listeners is stopped.
	while (noChangeToListenersSinceEvent && iter != listeners.end()) {
		// Sending the event to the listener.
		(*iter)->OnEvent(e);
		// If there was a change to listeners,
		// iter might be invalid and can't be incremented anymore.
		if (noChangeToListenersSinceEvent)
			++iter;
	}
}
