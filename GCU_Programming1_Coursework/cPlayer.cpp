#include "cPlayer.h"
#include "cCar.h"
#include "gameHeaders.h"

cPlayer::cPlayer(Teams team) : team(team)
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

void cPlayer::OnReachedSafeHouse()
{
	// Increment the score.
	cScoreMgr::getInstance()->increment(team);

	// Resetting the player's car to the start position.
	car->setSpritePos({ 0, 0 });
}
