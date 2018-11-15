/***************************************************************
Abstracts user input into actions that are more directly
related to the game and independent of the input device
and the input library used.
****************************************************************/

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