#include "ActionAdd.h"

ActionAdd::ActionAdd(Tutorial addedTutorial, Repository& repo) : addedTutorial(addedTutorial), repo(repo)
{
}

void ActionAdd::executeUndo()
{
	repo.deleteTutorial(addedTutorial);
}

void ActionAdd::executeRedo()
{
	repo.addTutorial(addedTutorial);
}

