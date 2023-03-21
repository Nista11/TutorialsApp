#include "Repository.h"
#include <fstream>
#include <sstream>
#include "Writer.h"

bool Repository::addTutorial(const Tutorial& t)
{
	if (this->find(t) != -1)
	{
		return false;
	}
	this->tutorials.push_back(t);
	return true;
}

bool Repository::updateTutorial(const std::string& currentLink, const Tutorial& t)
{
	int index = this->find(Tutorial{currentLink});
	if (index == -1)
	{
		return false;
	}

	this->tutorials[index] = t;
	return true;
}

bool Repository::deleteTutorial(const Tutorial& t)
{
	int index = this->find(t);
	if (index == -1)
	{
		return false;
	}
	this->tutorials.erase(this->tutorials.begin() + index);
	return true;
}

bool Repository::deleteTutorialWatchList(const Tutorial& t)
{
	int index = this->findWatchList(t);
	if (index == -1)
	{
		return false;
	}
	this->watchList.erase(this->watchList.begin() + index);
	return true;
}

bool Repository::seeTutorials(const std::string& presenter)
{
	bool found = false;
	for (auto& x : this->tutorials)
	{
		Tutorial t{ x };
		if (presenter == "" || presenter == t.getPresenter())
		{
			if (!found)
			{
				this->currentIndex = 0;
				found = true;
				this->currentList = std::vector<Tutorial>{};
			}
			this->currentList.push_back(t);
		}
	}
	return found;
}

Tutorial Repository::getCurrentTutorial()
{
	return this->currentList.at(this->currentIndex);
}

void Repository::nextTutorial()
{
	if (this->currentIndex + 1 >= this->currentList.size())
	{
		this->currentIndex = 0;
	}
	else
	{
		this->currentIndex++;
	}
}

bool Repository::addToWatchList()
{
	Tutorial t{ this->getCurrentTutorial() };
	if (this->findWatchList(t) != -1)
	{
		return false;
	}
	this->watchList.push_back(t);
	return true;
}

void Repository::likeTutorial(const std::string& link)
{
	int index = this->find(Tutorial{ link });
	if (index != -1)
	{
		Tutorial t{ this->tutorials.at(index) };
		t.setLikes(t.getLikes() + 1);
		this->tutorials[index] = t;
		index = this->findCurrentList(t);
		if (index != this->currentList.size())
		{
			this->currentList[index] = t;
		}
	}
}

int Repository::getSize() const
{
	return this->tutorials.size();
}

std::string Repository::watchListToString()
{
	std::string s{ "" };
	for (auto& x : this->watchList)
	{
		auto i = &x - &this->watchList[0];
		s += std::to_string(i + 1) + ": " + x.toString() + "\n";
	}
	return s;
}

std::string Repository::toString()
{
	std::string s{ "" };
	for (auto& x : this->tutorials)
	{
		auto i = &x - &this->tutorials[0];
		s += std::to_string(i + 1) + ": " + x.toString() + "\n";
	}
	return s;
}

int Repository::find(Tutorial t)
{
	int index = std::find(this->tutorials.begin(), this->tutorials.end(), t) - this->tutorials.begin();
	if (index == this->tutorials.size())
	{
		return -1;
	}
	return index;
}

int Repository::findWatchList(Tutorial t)
{
	int index = std::find(this->watchList.begin(), this->watchList.end(), t) - this->watchList.begin();
	if (index == this->watchList.size())
	{
		return -1;
	}
	return index;
}

int Repository::findCurrentList(Tutorial t)
{
	int index = std::find(this->currentList.begin(), this->currentList.end(), t) - this->currentList.begin();
	if (index == this->currentList.size())
	{
		return -1;
	}
	return index;
}

void Repository::readTutorialsFromFile()
{
	std::ifstream fin("tutorials.txt");
	std::string line{};
	char delimiter = ',';
	while (std::getline(fin, line))
	{
		int index = 0;
		std::string number = this->getToken(index, line, delimiter);
		std::string title = this->getToken(index, line, delimiter);
		std::string presenter = this->getToken(index, line, delimiter);
		std::string link = this->getToken(index, line, delimiter);
		std::string duration = this->getToken(index, line, delimiter);
		std::string likes = this->getToken(index, line, delimiter);
		this->removeDelimiter(title, " Title: ");
		this->removeDelimiter(presenter, " Presenter: ");
		this->removeDelimiter(link, " Link: ");
		this->removeDelimiter(duration, " Duration: ");
		this->removeDelimiter(likes, " Likes: ");
		std::stringstream stream{};
		stream << title << '\n' << presenter << '\n' << link << '\n' << std::stoi(likes) << '\n' << duration;
		Tutorial t{};
		stream >> t;
		this->addTutorial(t);
	}
	fin.close();
}

void Repository::saveTutorialsToFile()
{
	std::ofstream fout("tutorials.txt");
	fout << *this;
	fout.close();
}

void Repository::saveWatchList(bool csvFormat)
{
	if (csvFormat)
	{
		CSVWriter::write(this->watchList);
	}
	else
	{
		HTMLWriter::write(this->watchList);
	}
}

void Repository::openWatchList(bool csvFormat)
{
	if (csvFormat)
	{
		CSVWriter::open();
	}
	else
	{
		HTMLWriter::open();
	}
}

std::string Repository::getToken(int& index, std::string& source, char delimiter)
{
	std::string token = "";
	while (index < source.size() && source[index] != delimiter)
	{
		token += source[index];
		index++;
	}
	index++;
	return token;
}

void Repository::removeDelimiter(std::string& source, std::string delimiter)
{
	source.replace(source.find(delimiter), delimiter.length(), "");
}

std::vector<Tutorial> Repository::getTutorials()
{
	return this->tutorials;
}

std::vector<Tutorial> Repository::getWachListTutorials()
{
	return this->watchList;
}

