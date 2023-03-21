#include "ActionUpdate.h"

ActionUpdate::ActionUpdate(Tutorial originalTutorial, Tutorial updatedTutorial, Repository& repo) : originalTutorial(originalTutorial), updatedTutorial(updatedTutorial), repo(repo)
{
}

void ActionUpdate::executeUndo()
{
	repo.updateTutorial(updatedTutorial.getLink(), originalTutorial);
}

void ActionUpdate::executeRedo()
{
	repo.updateTutorial(originalTutorial.getLink(), updatedTutorial);
}
