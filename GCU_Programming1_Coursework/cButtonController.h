#pragma once
#include "IInputChannelListener.h"
#include "gameHeaders.h"

class cButtonController :
	public IInputChannelListener
{
private:
	vector<cSpriteButton*> buttons;
	vector<cSpriteButton*>::iterator cursor;	// the currently selected button

public:
	cButtonController();
	~cButtonController();

	void addButton(cSpriteButton* b);

	void OnEvent(AbstractEvent e);
};

