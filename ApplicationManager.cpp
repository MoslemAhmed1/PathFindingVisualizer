/*

#include "ApplicationManager.h"

#include "Grid.h"
#include "Action.h"
///TODO: Add #include for all action types

ApplicationManager::ApplicationManager()
{
	// Create Input, output and Grid
	pOut = new Output();
	// pIn = pOut->CreateInput();
	pGrid = new Grid(pIn, pOut);
}

////////////////////////////////////////////////////////////////////////////////////

ApplicationManager::~ApplicationManager()
{
	delete pGrid;
}

//==================================================================================//
//								Interface Management Functions						//
//==================================================================================//

Grid* ApplicationManager::GetGrid() const
{
	return pGrid;
}

void ApplicationManager::UpdateInterface() const
{
	pGrid->UpdateInterface();
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//

ActionType ApplicationManager::GetUserAction() const
{
	// Ask the input to get the action from the user.
	return pIn->GetUserAction();
}

////////////////////////////////////////////////////////////////////////////////////

// Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;

	// According to Action Type, create the corresponding action object
	switch (ActType)
	{
	case ADD_START:
		// pAct = new AddStartAction(this);
		break;

	case ADD_END:
		// pAct = new AddEndAction(this);
		break;

	case ADD_WALL:
		// pAct = new AddWallAction(this);
		break;

	case CLEAR_GRID:
		// pAct = new ClearGridAction(this);
		break;

	case BFS:
		// pAct = new BFSAction(this);
		break;

	case DIJKSTRA:
		// pAct = new DijkstraAction(this);
		break;

	case ASTAR:
		// pAct = new AStarAction(this);
		break;

	case STATUS:	// a click on the status bar ==> no action
		return;
	}

	// Execute the created action
	if (pAct != NULL)
	{
		pAct->Execute(); // Execute
		delete pAct;	 // Action is not needed any more after executing ==> delete it
		pAct = NULL;
	}
}

*/