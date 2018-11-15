#include "InputChannel.h"
#include "IInputChannelListener.h"
#include <algorithm>


void InputChannel::Register(IInputChannelListener * addThis)
{
	listeners.push_back(addThis);
}



void InputChannel::UnRegister(IInputChannelListener * removeThis)
{
	//Removing the pointer "removeThis" from the vector of listeners.
	//Using erase-remove idiom.
	//Research: https://stackoverflow.com/questions/3385229/c-erase-vector-element-by-value-rather-than-by-position#3385251
	listeners.erase(std::remove(listeners.begin(), listeners.end(), removeThis), listeners.end());
}



void InputChannel::RecieveEvent(AbstractEvent e)
{
	std::vector<IInputChannelListener*>::iterator iter = listeners.begin();
	for (iter; iter != listeners.end(); ++iter) {
		(*iter)->OnEvent(e);
	}
}
