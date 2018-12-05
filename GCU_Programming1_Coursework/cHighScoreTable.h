#pragma once
#include <string>
#include <vector>

using namespace std;

class cHighScoreTable
{
private:
	struct Item {
		string Name;
		int score;

		bool operator < ( const Item& rhs) const
		{
			// Inversed comparison to sort in inverse order.
			return rhs.score > score;
		}
	};

	int tableSize;

	Item tableEntry;

	vector<Item> tableEntries;
	//vector<Item*>::iterator row;


public:
	cHighScoreTable();

	bool loadFromFile(string highScoreFile);
	bool saveToFile(string highScoreFile);

	int  addItem(Item entry);
	int  addItem(string name, int score);
	Item getItem(int row);
	string getEntry(int row);
	void clearTable();
	string convertToString();
	int getTableSize();
	void setTableSize(int theSize);

	virtual ~cHighScoreTable();
};

