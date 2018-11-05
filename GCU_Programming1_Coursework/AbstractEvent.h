#pragma once

enum AbstractEventFlag
{
	NONE,
	DIRECTION,
	CONFIRM,
	MOUSE_MOVE
};


struct AbstractEvent
{
	AbstractEventFlag flag = NONE;
	double value_x = 0.0;
	double value_y = 0.0;
};