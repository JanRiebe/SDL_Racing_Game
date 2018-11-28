#include "cScoreMgr.h"


cScoreMgr* cScoreMgr::pInstance = NULL;



int cScoreMgr::calculateScore(int points, int timeInSeconds)
{
	return (points*1000)/timeInSeconds;
}

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

void cScoreMgr::SaveScores()
{
	for (int i = 0; i < NUMBER_OF_TEAMS; i++)
	{
		highscores.addItem(""+i, calculateScore(scores[i], 1));		//TODO add time taken to get the score
	}
	highscores.saveToFile(PATH_HIGHSCORES);
}

void cScoreMgr::LoadScores()
{
	highscores.saveToFile(PATH_HIGHSCORES);
}
