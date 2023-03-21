#include "Service.h"
#include "ActionAdd.h"
#include "ActionRemove.h"
#include "ActionUpdate.h"
#include <memory>

Service::Service(Repository& repository) : repo{repository}, undoRedoIndex(-1)
{}

bool Service::addTutorial(const std::string& title, const std::string& presenter, const std::string& link, const int likes, const Duration& duration)
{
	Tutorial t{ title, presenter, link, likes, duration };
	if (TutorialValidator::isValid(t))
	{
		bool retVal = this->repo.addTutorial(t);
		if (retVal)
		{
			if (this->undoRedoIndex + 1 < this->actions.size() && this->undoRedoIndex + 1 >= 0)
				this->actions.erase(this->actions.begin() + (this->undoRedoIndex + 1), this->actions.end());
			this->actions.push_back(std::make_unique<ActionAdd>(t, this->repo));
			this->undoRedoIndex++;
		}
		return retVal;
	}
	else
		return false;
}

bool Service::updateTutorial(const std::string& currentLink, const std::string& title, const std::string& presenter, const std::string& link, const int likes, const Duration& duration)
{
	Tutorial t{ title, presenter, link, likes, duration };

	int originalIndex = this->repo.find(currentLink);
	Tutorial tutorial{};
	if (originalIndex >= 0)
		tutorial = this->repo.getTutorials().at(originalIndex);
	bool retVal = this->repo.updateTutorial(currentLink, t);
	if (retVal && originalIndex >= 0)
	{
		if (this->undoRedoIndex + 1 < this->actions.size() && this->undoRedoIndex + 1 >= 0)
			this->actions.erase(this->actions.begin() + (this->undoRedoIndex + 1), this->actions.end());
		this->actions.push_back(std::make_unique<ActionUpdate>(tutorial, t, this->repo));
		this->undoRedoIndex++;
	}
	return retVal;
}

bool Service::deleteTutorial(const std::string& link)
{
	Tutorial t{ link };
	int tutorialIndex = this->repo.find(link);
	if (tutorialIndex >= 0)
		t = this->repo.getTutorials().at(tutorialIndex);
	bool retVal = this->repo.deleteTutorial(t);
	if (retVal)
	{
		if (this->undoRedoIndex + 1 < this->actions.size() && this->undoRedoIndex + 1 >= 0)
			this->actions.erase(this->actions.begin() + (this->undoRedoIndex + 1), this->actions.end());
		this->actions.push_back(std::make_unique<ActionRemove>(t, this->repo));
		this->undoRedoIndex++;
	}
	return retVal;
}

bool Service::deleteTutorialWatchList(const std::string& link)
{
	Tutorial t{ link };
	return	this->repo.deleteTutorialWatchList(t);
}

bool Service::seeTutorials(const std::string& presenter)
{
	return this->repo.seeTutorials(presenter);
}

Tutorial Service::getCurrentTutorial()
{
	return this->repo.getCurrentTutorial();
}

void Service::nextTutorial()
{
	this->repo.nextTutorial();
}

bool Service::addToWatchList()
{
	return this->repo.addToWatchList();
}

void Service::likeTutorial(const std::string& link)
{
	this->repo.likeTutorial(link);
}

int Service::getSize() const
{
	return this->repo.getSize();
}

int Service::find(Tutorial t)
{
	return this->repo.find(t);
}

std::string Service::watchListToString()
{
	return this->repo.watchListToString();
}

std::string Service::toString()
{
	return this->repo.toString();
}

void Service::readTutorialsFromFile()
{
	this->repo.readTutorialsFromFile();
}

void Service::saveTutorialsToFile()
{
	this->repo.saveTutorialsToFile();
}

void Service::saveWatchList(bool csvFormat)
{
	this->repo.saveWatchList(csvFormat);
}

void Service::openWatchList(bool csvFormat)
{
	this->repo.openWatchList(csvFormat);
}

std::vector<Tutorial> Service::getTutorials()
{
	return this->repo.getTutorials();
}

std::vector<Tutorial> Service::getFilteredTutorials(std::string filter)
{
	std::vector<Tutorial> tutorials = this->getTutorials();
	std::vector<Tutorial> filteredTutorials;
	for (Tutorial& t : tutorials)
	{
		if (t.toString().find(filter) != std::string::npos)
		{
			filteredTutorials.push_back(t);
		}
	}
	return filteredTutorials;
}

std::vector<Tutorial> Service::getWatchListTutorials()
{
	return this->repo.getWachListTutorials();
}

bool Service::undo()
{
	if (this->undoRedoIndex >= 0)
	{
		(*this->actions[this->undoRedoIndex]).executeUndo();
		this->undoRedoIndex--;
		return true;
	}
	else return false;
}

bool Service::redo()
{
	if (this->undoRedoIndex + 1 < this->actions.size())
	{
		(*this->actions[this->undoRedoIndex + 1]).executeRedo();
		this->undoRedoIndex++;
		return true;
	}
	else return false;
}
