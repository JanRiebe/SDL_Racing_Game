#include "cPlayer.h"
#include "cCar.h"
#include "gameHeaders.h"

cPlayer::cPlayer()
{
	score = 0;
}


cPlayer::~cPlayer()
{
}

void cPlayer::setScoreSprite(cSpriteText * s)
{
	scoreSprite = s;
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

void cPlayer::OnDestroyedSomething(int s)
{
	score += s;
	scoreSprite->setText(score, "Score");
}
