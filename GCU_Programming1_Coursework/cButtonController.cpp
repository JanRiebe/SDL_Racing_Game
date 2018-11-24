#include "cButtonController.h"
#include "cSpriteButton.h"

/*
Research on stacks
https://en.cppreference.com/w/cpp/container/stack
https://www.sitesbay.com/cpp-datastructure/cpp-stack-example
*/


cButtonController::cButtonController(cSpriteButton* b)
{	
	// Setting the cursor to the initial button.
	cursor = b;
	cursor->OnSelect();
}


cButtonController::~cButtonController()
{
}

void cButtonController::addButton(cSpriteButton* b)
{	
	buttonsBelow.push(b);
}

void cButtonController::OnEvent(AbstractEvent e)
{
	
	if (e.flag == AbstractEventFlag::CONFIRM)
	{
		// If there is a button selected,
		// evoke it's OnClick.
		if (cursor)
			cursor->OnClick();
	}
	else if (e.flag == AbstractEventFlag::DIRECTION)
	{
		// Changing selected button
		// Moving cursor down, if there is a button left above.
		if (e.value_y > 0 && buttonsAbove.size())
		{
			// Unhighlighting the old cursor.
			cursor->OnDeSelect();

			// Push the button that was selected to the buttons below.
			buttonsBelow.push(cursor);

			// Select the top button from the buttons above as the new cursor.
			cursor = buttonsAbove.top();
			// Remove the button from the buttons above, because it is now the cursor.
			buttonsAbove.pop();

			// Highlighting the new cursor.
			cursor->OnSelect();				
		}
		// Moving cursor down, if there is a button left below..
		else if (e.value_y < 0 && buttonsBelow.size())
		{
			// Unhighlighting the old cursor.
			cursor->OnDeSelect();

			// Push the button that was selected to the buttons above.
			buttonsAbove.push(cursor);

			// Select the top button from the buttons below as the new cursor.
			cursor = buttonsBelow.top();
			// Remove the button from the buttons below, because it is now the cursor.
			buttonsBelow.pop();

			// Highlighting the new cursor.
			cursor->OnSelect();
		}
	}
	
}
