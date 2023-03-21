#pragma once
#include "Tutorial.h"
#include "Repository.h"
#include "Action.h"

class ActionAdd : public Action
{
private:
	Tutorial addedTutorial;
	Repository& repo;
public:
	ActionAdd(Tutorial addedTutorial, Repository& repo);
	// Inherited via Action
	virtual void executeUndo() override;
	virtual void executeRedo() override;
};

