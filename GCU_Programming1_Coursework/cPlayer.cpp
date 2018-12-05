#include "cPlayer.h"
#include "cCar.h"
#include "gameHeaders.h"

cPlayer::cPlayer(string name, cSceneRacing* scene) : name(name), scene(scene)
{
	car = NULL;
}


cPlayer::~cPlayer()
{
}

void cPlayer::OnEvent(AbstractEvent e)
{
	if (e.flag == DIRECTION && car)
	{
		if(e.value_y!=0)
			car->accelerate(e.value_y);

		if (e.value_x != 0)
			car->steer(e.value_x);
	}
	else if (e.flag == CONFIRM)
	{
		//TODO leave the car or enter the car
	}
}

void cPlayer::OnReachedCheckpoint()
{
	scene->playerFinished(this);

	car = NULL;
}

string cPlayer::getName()
{
	return name;
}
