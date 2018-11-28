#include "cScoreMgr.h"


cScoreMgr* cScoreMgr::pInstance = NULL;



cScoreMgr::cScoreMgr()
{
	for (int i = 0; i < NUMBER_OF_TEAMS; i++)
	{
		scores[i] = 0;
		dirty[i] = true;
	}
}


cScoreMgr::~cScoreMgr()
{
}




/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
cScoreMgr* cScoreMgr::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cScoreMgr();
	}
	return cScoreMgr::pInstance;
}

void cScoreMgr::setScore(Teams team, int value)
{
	scores[team] = value;
	dirty[team] = true;
}

int cScoreMgr::getScore(Teams team)
{
	cout << "get score team " << team << scores[team]<<endl;

	dirty[team] = false;

	return scores[team];
}

void cScoreMgr::increment(Teams team)
{
	scores[team]++;
	
	dirty[team] = true;
}

bool cScoreMgr::isDirty(Teams team)
{
	return dirty[team];
}
