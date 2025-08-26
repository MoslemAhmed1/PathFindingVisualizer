#include "App.h"
#include "Grid.h"

App::App()
{
	// Create Input, output and Grid
	pOut = new Output();
	pIn = pOut->CreateInput();
	pGrid = new Grid(pIn, pOut);

	running = true;
}

////////////////////////////////////////////////////////////////////////////////////

App::~App()
{
	delete pGrid;
	delete pIn;
	delete pOut;
}

////////////////////////////////////////////////////////////////////////////////////

void App::Run()
{
	while (running && !WindowShouldClose())
	{
		// 1. Draw current UI
		BeginDrawing();
		ClearBackground(RAYWHITE);

		pGrid->PrintGrid();   // later: real drawing, now just console debug

		EndDrawing();

		// 2. Get action from Input
		ActionType actType = pIn->GetUserAction();

		// 3. Handle the action
		ExecuteAction(actType);
	}
}

//==================================================================================//
//								Interface Management Functions						//
//==================================================================================//

Grid* App::GetGrid() const
{
	return pGrid;
}

void App::UpdateInterface() const
{
	pGrid->UpdateInterface();
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//

// Creates an action and executes it
void App::ExecuteAction(ActionType ActType)
{

	// According to Action Type, create the corresponding action object
	switch (ActType)
	{
	case ADD_START:
		//
		break;

	case ADD_END:
		//
		break;

	case ADD_WALL:
		//
		break;

	case CLEAR_GRID:
		//
		break;

	case RUN_BFS:
		//
		break;
	case RUN_DIJKSTRA:
		//
		break;

	case RUN_ASTAR:
		//
		break;

	case STATUS:	// a click on the status bar ==> no action
		return;
	}
}
