#pragma once
#include <map>
#include "GameConstants.h"

using namespace std;

class cScoreMgr
{
private:
	static cScoreMgr* pInstance;
	int scores[NUMBER_OF_TEAMS];
	bool dirty[NUMBER_OF_TEAMS];		// Indicates whether the score has been updated since it has last been read.

public:
	cScoreMgr();
	~cScoreMgr();

	static cScoreMgr* getInstance();

	void setScore(Teams team, int value);
	int getScore(Teams team);
	void increment(Teams team);
	bool isDirty(Teams team);
};

