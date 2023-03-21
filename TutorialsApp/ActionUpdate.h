#pragma once
#include "Tutorial.h"
#include "Repository.h"
#include "Action.h"

class ActionUpdate : public Action
{
private:
	Tutorial originalTutorial;
	Tutorial updatedTutorial;
	Repository& repo;
public:
	ActionUpdate(Tutorial originalTutorial, Tutorial updatedTutorial, Repository& repo);
	// Inherited via Action
	virtual void executeUndo() override;
	virtual void executeRedo() override;
};

