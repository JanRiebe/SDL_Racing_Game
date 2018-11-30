#include "cHighScoreTable.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "GameConstants.h"


cHighScoreTable::cHighScoreTable()
{

}


bool cHighScoreTable::loadFromFile(string highScoreFile)
{
	ifstream file;
	string aName;
	int aScore;
	int item = 0;

	file.open(highScoreFile, ios::binary);
	if (!file.is_open())
	{ 
		cout << "Error opening file " << highScoreFile << endl;
		return false;
	}

	Item tableEntry;
	tableEntries.clear();

	while (!file.eof()) {
		tableEntries.push_back(new Item);
		file >> aName >> aScore;
		tableEntries[item]->Name = aName;
		tableEntries[item]->score = aScore;
		item++;
	}
	file.close();
	this->setTableSize(item);
	return true;
}

bool cHighScoreTable::saveToFile(string highScoreFile)
{
	ofstream file;
	file.open(highScoreFile, ios::binary | ios::out);

	if (!file.is_open())
	{ 
		cout << "Error opening file " << highScoreFile << " for saving to ..." << endl;
		return false;
	}

	for (int tblEntry = 0; tblEntry < (int)this->tableEntries.size(); tblEntry++)
	{
		file << tableEntries[tblEntry]->Name << " " << tableEntries[tblEntry]->score << endl;
	}

	file.close();
	return true;
}

int  cHighScoreTable::addItem(Item entry)
{
	int row = this->tableEntries.size();

	if (row == HIGHSCORE_LIST_ENTRIES)
	{
		cout << "Table full" << endl;
		this->tableSize = row;
		return row;
	}
	else
	{
		int index = row;
		this->tableEntries.push_back(new Item);
		this->tableEntries[index]->Name = entry.Name;
		this->tableEntries[index]->score = entry.score;
		sort(this->tableEntries.begin(), this->tableEntries.end());
		return this->tableEntries.size();
	}
}

int cHighScoreTable::addItem(string name, int score)
{
	Item item{ name, score };
	return addItem(item);
}

cHighScoreTable::Item cHighScoreTable::getItem(int row)
{
	Item tblItem;

	// Checking whether there are enough entries in the table.
	if (this->tableEntries.size() > row)
	{
		tblItem.Name = this->tableEntries[row]->Name;
		tblItem.score = this->tableEntries[row]->score;
	}
	else
	{
		tblItem.Name = "---";
		tblItem.score = 0;
	}
	return tblItem;
}

string cHighScoreTable::getEntry(int row)
{
	cout << "getEntry\n";
	Item item = getItem(row);
	return item.Name +" " + to_string(item.score);
}

void cHighScoreTable::clearTable()
{
	this->tableEntries.clear();
}

string cHighScoreTable::convertToString()
{
	string table = "";
	for (int tblEntry = 0; tblEntry < (int)this->tableEntries.size(); tblEntry++)
	{
		table += tableEntries[tblEntry]->Name + " " + std::to_string(tableEntries[tblEntry]->score) + "\n";
	}
	return table;
}

int cHighScoreTable::getTableSize()
{
	return this->tableSize;
}

void cHighScoreTable::setTableSize(int theSize)
{
	this->tableSize = theSize;
}

cHighScoreTable::~cHighScoreTable()
{
}
