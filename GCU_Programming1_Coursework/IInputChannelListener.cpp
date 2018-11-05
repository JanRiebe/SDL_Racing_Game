#include "IInputChannelListener.h"
#include "InputChannel.h"



IInputChannelListener::~IInputChannelListener()
{
	channel->UnRegister(this);
}

void IInputChannelListener::Register(InputChannel * c)
{
	c->Register(this);
	channel = c;
}
