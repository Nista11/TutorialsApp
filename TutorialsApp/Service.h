#pragma once
#include "Repository.h"
#include "Action.h"
#include <memory>
#include <iostream>

class Service
{
private:
	Repository& repo;
	int undoRedoIndex; 
	std::vector<std::unique_ptr<Action>> actions;
public:	
	Service(Repository& repository);
	friend std::ostream& operator<<(std::ostream& out, const Service& s)
	{
		out << s.repo;
		return out;
	}

	/*
	adds a tutorial to the current repository
	returns true if the tutorial was added, false otherwise
	*/
	bool addTutorial(const std::string& title, const std::string& presenter, const std::string& link, const int likes, const Duration& duration);
	/*
	updates a tutorial from the current repository
	returns true if the tutorial was updated, false otherwise
	*/
	bool updateTutorial(const std::string& currentLink, const std::string& title, const std::string& presenter, const std::string& link, const int likes, const Duration& duration);
	/*
	deletes a tutorial
	*/
	bool deleteTutorial(const std::string& link);
	/*
	deletes a tutorial from the watch list
	*/
	bool deleteTutorialWatchList(const std::string& link);

	/*
	adds all tutorials containing a given presenter to the current list of tutorials 
	return true if there is at least one tutorial with the given presenter, false otherwise
	*/
	bool seeTutorials(const std::string& presenter);
	/*
	gets current tutorial from currentList
	*/
	Tutorial getCurrentTutorial();
	/*
	changes the index of the current tutorial to +1 or back to 0 if end is reached
	*/
	void nextTutorial();

	/*
	adds the current tutorial to the watch list
	return true if the tutorial was added, false if the tutorial already exists in the watch list
	*/
	bool addToWatchList();

	/*
	adds 1 to the given tutorial's likes
	*/
	void likeTutorial(const std::string& link);

	int getSize() const;
	
	/*
	returns index of given tutorials if found in repository, -1 otherwise
	*/
	int find(Tutorial);
	std::string watchListToString();
	std::string toString();
	/*
	reads tutorials from a file and stores them into the current repo
	*/
	void readTutorialsFromFile();
	/*
	saves tutorials from the current repo to a file
	*/
	void saveTutorialsToFile();
	/*
	saves the watch list to a file 
	parameters:
	bool csvFormat: if true, the list will be saved into a csv file, otherwise into a html one
	*/
	void saveWatchList(bool csvFormat);
	/*
	opens the saved watch list
	bool csvFormat: format of the file to be opened: if true: csv, html otherwise
	*/
	void openWatchList(bool csvFormat);

	std::vector<Tutorial> getTutorials();
	std::vector<Tutorial> getFilteredTutorials(std::string filter);
	std::vector<Tutorial> getWatchListTutorials();

	bool undo();
	bool redo();
};

