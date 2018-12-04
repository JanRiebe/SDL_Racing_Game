#include "cPlayer.h"
#include "cCar.h"
#include "gameHeaders.h"

cPlayer::cPlayer(string name) : name(name)
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
		car->accelerate(e.value_y);
		car->steer(e.value_x);
	}
	else if (e.flag == CONFIRM)
	{
		//TODO leave the car or enter the car
	}
}

void cPlayer::OnReachedCheckpoint()
{
	// Increment the score.
	cScoreMgr::getInstance()->setScore(name + "_finish", 1);

	car = NULL;
}

string cPlayer::getName()
{
	return name;
}
