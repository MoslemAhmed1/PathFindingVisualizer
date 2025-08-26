#include "App.h"
#include "Grid.h"

App::App()
{	
	// Spacing between buttons
	int spacing = 10;
	float x = 50;
	float y = 10;

	string btn_text[7] = { "BFS", "Dijkstra", "A*", "Set Wall", "Set Start", "Set End", "Clear Grid" };
	ButtonType type[7] = { BFS_BTN, DIJKSTRA_BTN, ASTAR_BTN, ADD_WALL_BTN, ADD_START_BTN, ADD_END_BTN, CLEAR_GRID_BTN };
	
	// Initialize buttons (Error)
	for (int i = 0; i < 7; i++)
	{
		Button* button = new Button(btn_text[i], { x, y }, type[i]);
		buttons.push_back(button);
		x += (UI.ButtonWidth + spacing);
	}

	// Create Input, Output and Grid
	pOut = new Output(buttons);
	pIn = pOut->CreateInput(buttons);
	pGrid = new Grid(pIn, pOut);
}

////////////////////////////////////////////////////////////////////////////////////

App::~App()
{
	delete pGrid;
	delete pIn;
	delete pOut;
	for (Button* btn : buttons) 
		delete btn;
}

////////////////////////////////////////////////////////////////////////////////////

void App::Run()
{
	while (!WindowShouldClose())
	{
		
		BeginDrawing();
		pGrid->UpdateInterface(); // Always redraw the grid
		EndDrawing();
		
		// Check for input without blocking
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
		{
			ActionType actType = pIn->GetUserAction();
			ExecuteAction(actType);
		}
	}

	CloseWindow();
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
		AddStart();
		break;

	case ADD_END:
		AddEnd();
		break;

	case ADD_WALL:
		AddWall();
		break;

	case CLEAR_GRID:
		ClearGrid();
		break;

	case RUN_BFS:
		Run_BFS();
		break;
	case RUN_DIJKSTRA:
		Run_Dijkstra();
		break;

	case RUN_ASTAR:
		Run_AStar();
		break;

	case STATUS:	// a click on the status bar ==> no action
		return;
	}
}

void App::AddStart()
{
	pGrid->PrintMessage("Click on a cell to add a start node");
	CellPosition position = pIn->GetCellClicked();
	if (position.IsValidCell()) 
	{
		if (!pGrid->SetStartCell(position.VCell(), position.HCell())) 
		{
			pGrid->PrintMessage("There's already a start node, click on it to remove it!");
		}
	}
	else 
	{
		pGrid->PrintMessage("Invalid cell clicked!");
	}
}

void App::AddEnd()
{
	pGrid->PrintMessage("Click on a cell to add an end node");
	CellPosition position = pIn->GetCellClicked();
	if (position.IsValidCell())
	{
		if (!pGrid->SetEndCell(position.VCell(), position.HCell()))
		{
			pGrid->PrintMessage("There's already an end node, click on it to remove it!");
		}
	}
	else
	{
		pGrid->PrintMessage("Invalid cell clicked!");
	}
}

void App::AddWall()
{
	pGrid->PrintMessage("Click on a cell to add a wall");
	CellPosition position = pIn->GetCellClicked();
	if (position.IsValidCell())
	{
		if (!pGrid->SetWallCell(position.VCell(), position.HCell()))
		{
			pGrid->PrintMessage("Can't select start/end nodes!");
		}
	}
	else
	{
		pGrid->PrintMessage("Invalid cell clicked!");
	}
}

void App::ClearGrid()
{
	pGrid->ClearGrid();
	pOut->ClearGridArea();
}

void App::Run_BFS()
{
	if (pGrid->GetStartCell() && pGrid->GetEndCell()) 
	{
		pGrid->PrintPath(BFS_ALGORITHM);
	}
	else 
	{
		pGrid->PrintMessage("Set start and end points first!");
	}
}

void App::Run_Dijkstra()
{
	if (pGrid->GetStartCell() && pGrid->GetEndCell())
	{
		pGrid->PrintPath(DIJKSTRA_ALGORITHM);
	}
	else 
	{
		pGrid->PrintMessage("Set start and end points first!");
	}
}

void App::Run_AStar()
{
	if (pGrid->GetStartCell() && pGrid->GetEndCell())
	{
		pGrid->PrintPath(ASTAR_ALGORITHM);
	}
	else 
	{
		pGrid->PrintMessage("Set start and end points first!");
	}
}