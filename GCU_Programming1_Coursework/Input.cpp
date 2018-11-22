#include "Input.h"

//Initialising instance to nullptr
Input* Input::instance = nullptr;



void Input::AbstractSDLEvent(SDL_Event e)
{
	//The device ID to be set depending on the input.
	deviceID device = UNKNOWN_DEVICE;
	//The abstracted event that will be passed on.
	AbstractEvent abstract_e;

	//Handleing keyboard events
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		//Keyboard inputs for the right keyboard side
		case SDLK_UP:
			device = KEYBOARD_ARROWS;
			abstract_e.flag = DIRECTION;
			abstract_e.value_y = 1.0;
			break;
		case SDLK_DOWN:
			device = KEYBOARD_ARROWS;
			abstract_e.flag = DIRECTION;
			abstract_e.value_y = -1.0;
			break;
		case SDLK_LEFT:
			device = KEYBOARD_ARROWS;
			abstract_e.flag = DIRECTION;
			abstract_e.value_x = -1.0;			
			break;
		case SDLK_RIGHT:
			device = KEYBOARD_ARROWS;
			abstract_e.flag = DIRECTION;
			abstract_e.value_x = 1.0;
			break;
		case SDLK_RETURN:
			device = KEYBOARD_ARROWS;
			abstract_e.flag = CONFIRM;
			break;


		//Keyboard inputs for the left keyboard side
		case SDLK_w:
			device = KEYBOARD_WASD;
			abstract_e.flag = DIRECTION;
			abstract_e.value_y = 1.0;
			break;
		case SDLK_s:
			device = KEYBOARD_WASD;
			abstract_e.flag = DIRECTION;
			abstract_e.value_y = -1.0;
			break;
		case SDLK_a:
			device = KEYBOARD_WASD;
			abstract_e.flag = DIRECTION;
			abstract_e.value_x = -1.0;
			break;
		case SDLK_d:
			device = KEYBOARD_WASD;
			abstract_e.flag = DIRECTION;
			abstract_e.value_x = 1.0;
			break;
		case SDLK_e:
			device = KEYBOARD_WASD;
			abstract_e.flag = CONFIRM;
			break;
		}
	}

	

	

	//If the device is registered to a channel
	if (connections.contains(device))
		//Send the abstracted event to the channel
		connections[device]->RecieveEvent(abstract_e);
	

}




bool Input::Initialise()
{
	if (instance == nullptr)
	{
		instance = new Input();
		return true;
	}
	else
		return false;
}



void Input::Quit()
{
	delete instance;
	instance = nullptr;
}



void Input::SDLEventIn(SDL_Event e)
{
	//Passing the static function call to the singleton object.
	instance->AbstractSDLEvent(e);
}



bool Input::RegisterChannelListener(IInputChannelListener * l, int channelIndex)
{
	//Passing the static function call to the singleton object.
	return instance->RegisterCL(l, channelIndex);
}

void Input::UnRegisterChannelListener(IInputChannelListener * l)
{
	//Passing the static function call to the singleton object.
	instance->UnRegisterCL(l);
}




bool Input::RegisterCL(IInputChannelListener * l, int channelIndex)
{
	//Not registering if there is no channel with the given index.
	if (channelIndex >= NUMBER_OF_CHANNELS)
		return false;

	//Registering the listener to the channel.
	channels[channelIndex].Register(l);
	return true;
}

void Input::UnRegisterCL(IInputChannelListener * l)
{
	for (int i = 0; i < NUMBER_OF_CHANNELS; i++)
	{
		channels[i].UnRegister(l);
	}
}





bool Input::RegisterDevice(deviceID device, int channelIndex)
{
	//Passing the static function call to the singleton object.
	return instance->RegisterD(device, channelIndex);
}


bool Input::RegisterD(deviceID device, int channelIndex)
{
	//Not registering if there is no channel with the given index.
	if (channelIndex >= NUMBER_OF_CHANNELS)
		return false;

	//Removing old association between device and controller
	//so that only one device is associated with the channel
	connections.remove(&(channels[channelIndex]));

	//Adding the new device channel association.
	//This automatically removes all associations either element had before.
	connections.add(device, &(channels[channelIndex]));

	return true;
}




int Input::GetNumberOfPlayers()
{
	return instance->connections.getSize();
}








Input::Input()
{
}

