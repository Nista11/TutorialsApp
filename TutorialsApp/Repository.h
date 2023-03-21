#pragma once
#include <vector>
#include "Tutorial.h"
#include <iostream>

class Repository
{
private:
	std::vector<Tutorial> tutorials;
	std::vector<Tutorial> currentList;
	std::vector<Tutorial> watchList;
	int currentIndex = 0;
public:
	friend std::ostream& operator<<(std::ostream& out, const Repository& r)
	{
		for (int index = 0; index < r.tutorials.size(); index++)
		{
			out << index + 1 << ", " << r.tutorials[index];
			out << "\n";
		}
		return out;
	}
	bool addTutorial(const Tutorial&);
	bool updateTutorial(const std::string& currentLink, const Tutorial&);
	bool deleteTutorial(const Tutorial&);
	bool deleteTutorialWatchList(const Tutorial&);
	bool seeTutorials(const std::string& presenter);
	Tutorial getCurrentTutorial();
	void nextTutorial();
	bool addToWatchList();
	void likeTutorial(const std::string& link);
	int getSize() const;
	std::string watchListToString();
	std::string toString();
	/*
	returns index of given tutorials if found in repository, -1 otherwise
	*/
	int find(Tutorial);
	int findWatchList(Tutorial t);
	int findCurrentList(Tutorial t);

	void readTutorialsFromFile();
	void saveTutorialsToFile();
	void saveWatchList(bool csvFormat);
	void openWatchList(bool csvFormat);
	/*
	returns the next token from source delimited by the delimiter string and updates current index
	*/
	std::string getToken(int& index, std::string& source, char delimiter);
	/*
	removes first apperance of delimiter in source
	*/
	void removeDelimiter(std::string& source, std::string delimiter);
	std::vector<Tutorial> getTutorials();
	std::vector<Tutorial> getWachListTutorials();
};

