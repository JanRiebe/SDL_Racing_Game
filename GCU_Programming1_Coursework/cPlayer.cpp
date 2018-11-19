#include "cPlayer.h"
#include "cCar.h"
#include "gameHeaders.h"

cPlayer::cPlayer()
{
}


cPlayer::~cPlayer()
{
}

void cPlayer::OnEvent(AbstractEvent e)
{
	if (e.flag == DIRECTION)
	{
		car->accelerate(e.value_y);
		car->steer(e.value_x);
	}
	else if (e.flag == CONFIRM)
	{
		//TODO leave the car or enter the car
	}
}
