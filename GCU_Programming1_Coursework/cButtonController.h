#pragma once
#include "IInputChannelListener.h"
#include <stack>

using namespace std;

class cSpriteButton;

class cButtonController :
	public IInputChannelListener
{
private:
	cSpriteButton* test;
	stack<cSpriteButton*> buttonsAbove;
	cSpriteButton* cursor;	// the currently selected button
	stack<cSpriteButton*> buttonsBelow;

public:
	cButtonController(cSpriteButton* b);
	~cButtonController();

	void addButton(cSpriteButton* b);

	void OnEvent(AbstractEvent e);
};

