#include "Tutorial.h"

Duration::Duration(int minutes, int seconds) : minutes{ minutes }, seconds{seconds}
{}

Duration::Duration(std::string d)
{
	std::string minutes = "";
	int index = 0;
	while (index < d.size() && d[index] != ':')
	{
		minutes += d[index];
		index++;
	}
	index++;
	std::string seconds = "";
	if (index < d.size() && d[index] == '0')
	{
		index++;
	}
	while (index < d.size())
	{
		seconds += d[index];
		index++;
	}
	this->minutes = std::stoi(minutes);
	this->seconds = std::stoi(seconds);
}

Duration::Duration() : minutes{ 0 }, seconds{ 0 }
{}

int Duration::getMinutes() const
{
	return this->minutes;
}

int Duration::getSeconds() const
{
	return this->seconds;
}

void Duration::setMinutes(int minutes)
{
	this->minutes = minutes;
}

void Duration::setSeconds(int seconds)
{
	this->seconds = seconds;
}

std::string Duration::toString()
{
	std::string s{ "" };
	s += std::to_string(this->minutes) + ":";
	if (this->seconds < 10)
	{
		s += "0";
	}
	s += std::to_string(this->seconds);
	return s;
}

Tutorial::Tutorial(const std::string& title, const std::string& presenter, const std::string& link, const int likes, const Duration& duration) : title{ title }, presenter{ presenter }, link{ link }, likes{ likes }, duration{duration}
{}

Tutorial::Tutorial(const std::string& link) : title{ "" }, presenter{ "" }, link{ link }, likes{ 0 }, duration{ Duration{0, 0} }
{}

Tutorial::Tutorial() : title{ "" }, presenter{ "" }, link{ "" }, likes{ 0 }, duration{Duration{0, 0}}
{}

bool Tutorial::operator==(const Tutorial& t)
{
	return this->link == t.link;
}

std::string Tutorial::getTitle()
{
	return this->title;
}

std::string Tutorial::getPresenter()
{
	return this->presenter;
}

std::string Tutorial::getLink()
{
	return this->link;
}

void Tutorial::setLikes(int likes)
{
	this->likes = likes;
}

Duration Tutorial::getDuration()
{
	return this->duration;
}

int Tutorial::getLikes()
{
	return this->likes;
}

std::string Tutorial::toString()
{
	std::string s{ "" };
	s += "Title: " + this->title + ", Presenter: " + this->presenter + ", Link: " + this->link;
	s += ", Duration: " + this->duration.toString();
	s += ", Likes: " + std::to_string(this->likes);
	return s;
}

bool DurationValidator::isValid(Duration d)
{
	try
	{
		if (d.getSeconds() >= 0 && d.getSeconds() <= 59)
		{
			return true;
		}
		else
		{
			throw ValidatorException();
		}
	}
	catch (ValidatorException& e)
	{
		return false;
	}
}

bool TutorialValidator::isValid(Tutorial t)
{
	try
	{
		if (DurationValidator::isValid(t.getDuration()))
		{
			return true;
		}
		else
		{
			throw ValidatorException();
		}
	}
	catch (ValidatorException& e)
	{
		return false;
	}
}
