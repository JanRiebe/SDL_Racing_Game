#include "cScoreMgr.h"


cScoreMgr* cScoreMgr::pInstance = NULL;



cScoreMgr::cScoreMgr()
{
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


void cScoreMgr::setScore(string name, int value)
{
	scores[name] = value;
	dirty[name] = true;
}

int cScoreMgr::getScore(string name)
{
	// If no score with this name is stored, return 0.
	if (scores.count(name) <= 0)
		return 0;

	cout << "get score " << name << scores[name]<<endl;

	dirty[name] = false;

	return scores[name];
}

void cScoreMgr::increment(string name)
{
	// If a score with this name exists, increase it.
	if (scores.count(name) > 0)
	{
		scores[name]++;

		dirty[name] = true;
	}
}

bool cScoreMgr::isDirty(string name)
{
	if (dirty.count(name) > 0)
		return dirty[name];

	// Returning that the score is not dirty if no score with this name exists.
	return false;
}

void cScoreMgr::clear()
{
	scores.clear();
	dirty.clear();
}

void cScoreMgr::SaveScores()
{
	map<string, int>::iterator it = scores.begin();
	for (it; it!=scores.end(); it++)
	{
		highscores.addItem(it->first, it->second);
	}
	highscores.saveToFile(PATH_HIGHSCORES);
}

void cScoreMgr::LoadScores()
{
	highscores.loadFromFile(PATH_HIGHSCORES);
}

string cScoreMgr::getHighscoreEntry(int entryIndex)
{
	// If the entry index is higher than the maximum number of entries.
	// Just for safety. Should not happen.
	if(entryIndex >= HIGHSCORE_LIST_ENTRIES)
		return "---";

	return highscores.getEntry(entryIndex);
}
