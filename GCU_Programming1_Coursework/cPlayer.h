#pragma once
#include "IInputChannelListener.h"
#include "GameConstants.h"

class cCar;
class cSceneRacing;

class cPlayer :
	public IInputChannelListener
{
private:
	string name;
	cSceneRacing* scene;

public:
	cPlayer(string name, cSceneRacing* scene);
	~cPlayer();
	cCar* car;

	void OnEvent(AbstractEvent e);

	void OnReachedCheckpoint();

	string getName();
};

