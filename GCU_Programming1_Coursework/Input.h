/***************************************************************
A class that manages all the user input and passes it on
to the game.

Input can be recieved from different devices.
It is then translated into abstract input events,
which the rest of the engine can deal with.

The input manager object is hidden in a singleton and
access is provided through static functions.

Together with channels, this class decouples input from
different sources from the rest of the engine and allows
for multiplayer play on one device. 

****************************************************************/

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

//The number of channels that are created.
//The maximum number of players that can play.
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

	//Unregisters a channel listener from all channels it is registered to.
	static void UnRegisterChannelListener(IInputChannelListener* l);

	//Registers a device to the first available channel. Returns whether the registration was successfull.
	static bool RegisterDevice(deviceID device, int channelIndex = 0);

	//Returns the number of players that have registered via a device.
	static int GetNumberOfPlayers();

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
	//Unregisters a channel listener from all channels it is registered to.
	void UnRegisterCL(IInputChannelListener* l);

	//Registers a device to the first available channel. Returns whether the registration was successfull.
	bool RegisterD(deviceID device, int channelIndex = 0);
};


