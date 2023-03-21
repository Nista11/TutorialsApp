#include "ActionRemove.h"

ActionRemove::ActionRemove(Tutorial removedTutorial, Repository& repo) : removedTutorial(removedTutorial), repo(repo)
{
}

void ActionRemove::executeUndo()
{
	repo.addTutorial(removedTutorial);
}

void ActionRemove::executeRedo()
{
	repo.deleteTutorial(removedTutorial);
}
