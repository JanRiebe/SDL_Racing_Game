#pragma once

#include "Association.h"
#include "InputChannel.h"
#include <SDL.h>

//Input management related constants
enum deviceID
{
	UNKNOWN_DEVICE,
	KEYBOARD_WASD,
	KEYBOARD_ARROWS,
	SDL_JOYSTICK_0,
	SDL_JOYSTICK_1,
	SDL_JOYSTICK_2,
	SDL_JOYSTICK_3
};

const int NUMBER_OF_CHANNELS = 4;



class Input
{
public:
	//Sets up the input manager so it can be used. Returns whether initialisation was successfull.
	static bool Initialise();
	
	//Cleans up the input manager, releasing the input manager object.
	static void Quit();
	
	//Gives the input manager an SLD event to process.
	static void SDLEventIn(SDL_Event e);
	
	//Registers a channel listener to the specified channel. Returns whether the registration was successfull.
	static bool RegisterChannelListener(IInputChannelListener* l, int channelIndex);
	
	//Registers a device to the first available channel. Returns whether the registration was successfull.
	static bool RegisterDevice(deviceID device, int channelIndex = 0);

private:
	//The constructor is private, because the input manager is a singleton.
	Input();

	//Singleton instance, reference to the only object of this class.
	static Input* instance;

	//The channels through which abstract events are being sent.
	InputChannel channels[NUMBER_OF_CHANNELS];
	
	//Association between device IDs and abstracted input channels.
	Association<deviceID, InputChannel*> connections;
	
	//Processes the SDL event and abstracts it into an AbstactEvent.
	void AbstractSDLEvent(SDL_Event e);
	
	//Registers a channel listener to the specified channel. Returns whether the registration was successfull.
	bool RegisterCL(IInputChannelListener* l, int channelIndex);
	
	//Registers a device to the first available channel. Returns whether the registration was successfull.
	bool RegisterD(deviceID device, int channelIndex = 0);
};


