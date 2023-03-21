#pragma once
#include <string>
#include <iostream>

class Duration
{
private:
	int minutes, seconds;
public:
	Duration(int minutes, int seconds);
	Duration(std::string d);
	Duration();

	friend std::ostream& operator<<(std::ostream& out, const Duration& d)
	{
		out << d.minutes << ":";
		if (d.seconds < 10)
		{
			out << '0';
		}
		out << d.seconds;
		return out;
	}

	friend std::istream& operator>>(std::istream& in, Duration& d)
	{
		std::string s;
		in >> s;
		Duration d2{ s };
		d.setMinutes(d2.getMinutes());
		d.setSeconds(d2.getSeconds());
		return in;
	}

	int getMinutes() const;
	int getSeconds() const;
	void setMinutes(int minutes);
	void setSeconds(int seconds);
	
	std::string toString();
};

class Tutorial
{
private:
	std::string title, presenter, link;
	Duration duration;
	int likes;
public:
	Tutorial(const std::string& title, const std::string& presenter, const std::string& link, const int likes, const Duration& duration);
	Tutorial(const std::string& link);
	Tutorial();
	bool operator==(const Tutorial&);
	friend std::ostream& operator<<(std::ostream& out, const Tutorial& t)
	{
		out << "Title: " + t.title + ", Presenter: " + t.presenter + ", Link: " + t.link;
		out << ", Duration: " << t.duration;
		out << ", Likes: " << t.likes;
		return out;
	}
	friend std::istream& operator>>(std::istream& in, Tutorial& t)
	{
		std::string title, presenter, link, likes, duration;
		std::getline(in, title);
		std::getline(in, presenter);
		std::getline(in, link);
		std::getline(in, likes);
		std::getline(in, duration);
		t = Tutorial{ title, presenter, link, std::stoi(likes), Duration{duration} };
		return in;
	}

	std::string getTitle();
	std::string getPresenter();
	std::string getLink();
	void setLikes(int likes);
	Duration getDuration();
	int getLikes();
	std::string toString();
};

class DurationValidator
{
public:
	static bool isValid(Duration d);
};

class TutorialValidator
{
public:
	static bool isValid(Tutorial t);
};

class ValidatorException : public std::exception
{
};
