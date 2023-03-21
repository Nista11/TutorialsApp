#pragma once
#include <vector>
#include "Tutorial.h"
#include <fstream>

class Writer
{
public:
	virtual void write(std::vector<Tutorial> tutorials) = 0;
	virtual void open() = 0;
};

class CSVWriter : Writer
{
public:
	static void write(std::vector<Tutorial> tutorials);
	static void open();
};

class HTMLWriter : Writer
{
public:
	static void write(std::vector<Tutorial> tutorials);
	static void open();
};
