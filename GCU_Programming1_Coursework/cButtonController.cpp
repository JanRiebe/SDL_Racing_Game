#include "cButtonController.h"



cButtonController::cButtonController()
{
	// Marking that no button is associated with the cursor yet.
	// buttons.end() points outside buttons, so it is not associated with an actual button.
	cursor = buttons.end();
}


cButtonController::~cButtonController()
{
}

void cButtonController::addButton(cSpriteButton* b)
{
	buttons.push_back(b);

	// If this was the first button added, set the cursor to it.
	if (cursor == buttons.end())
		cursor = buttons.begin();
}

void cButtonController::OnEvent(AbstractEvent e)
{
	if (e.flag == AbstractEventFlag::CONFIRM)
	{
		// If there is a button selected,
		// evoke it's OnClick.
		if (cursor != buttons.end())
			(*cursor)->OnClick();
	}
	else if (e.flag == AbstractEventFlag::DIRECTION)
	{
		// Changing selected button
		if (e.value_y > 0)
		{
			cursor++;
			if (cursor != buttons.end())
				cursor = buttons.begin();
		}
		else if (e.value_y < 0 && cursor != buttons.begin())
		{
			cursor--;
		}
	}
}
