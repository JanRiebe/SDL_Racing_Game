#pragma once
#include <map>
#include "GameConstants.h"
#include "cHighScoreTable.h"

using namespace std;

class cScoreMgr
{
private:
	static cScoreMgr* pInstance;
	map<string, int> scores;
	map<string, bool> dirty;		// Indicates whether the score has been updated since it has last been read.

	cHighScoreTable highscores;


public:
	cScoreMgr();
	~cScoreMgr();

	static cScoreMgr* getInstance();

	map<string, int> getAllScores();
	void setScore(string, int value);
	int getScore(string);
	void increment(string);
	bool isDirty(string);

	void SaveScores();
	void LoadScores();
	string getHighscoreEntry(int entryIndex);
};

