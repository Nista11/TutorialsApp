#pragma once
#include "Tutorial.h"
#include "Repository.h"
#include "Action.h"

class ActionRemove : public Action
{
private:
	Tutorial removedTutorial;
	Repository& repo;
public:
	ActionRemove(Tutorial removedTutorial, Repository& repo);
	// Inherited via Action
	virtual void executeUndo() override;
	virtual void executeRedo() override;
};

